/************* COPYRIGHT AND CONFIDENTIALITY INFORMATION *********************
 **                                                                          **
 ** Copyright (c) 2012 Technicolor                                           **
 ** All Rights Reserved                                                      **
 **                                                                          **
 ** This program contains proprietary information which is a trade           **
 ** secret of TECHNICOLOR and/or its affiliates and also is protected as     **
 ** an unpublished work under applicable Copyright laws. Recipient is        **
 ** to retain this program in confidence and is not permitted to use or      **
 ** make copies thereof other than as permitted in a written agreement       **
 ** with TECHNICOLOR, UNLESS OTHERWISE EXPRESSLY ALLOWED BY APPLICABLE LAWS. **
 **                                                                          **
 ******************************************************************************/
#include "qeowebviewjavascriptinterface.h"
#include "otcdialog.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QGraphicsWebView>
#include <QWebFrame>
#include <QMessageBox>
#include <QStyle>
#include <QThread>


// Declare a custom type for usage in signals
Q_DECLARE_METATYPE(qeo_platform_security_context_t)

//---------------------------------------------
// Callbacks from qeo-c-utils library
//---------------------------------------------
qeo_util_retcode_t QeoWebViewJavascriptInterface::on_registration_params_needed(uintptr_t app_context, qeo_platform_security_context_t sec_context){

    qDebug() << "WebView [" << QThread::currentThreadId() << "]: " << __func__;

    /* Get your instance by casting it */
    QeoWebViewJavascriptInterface* webBridgeObj = (QeoWebViewJavascriptInterface*)app_context;

    /* Put task on Main thread queue */
    emit webBridgeObj->invokeRegistrationDialog(sec_context);

    return QEO_UTIL_OK;
}

void QeoWebViewJavascriptInterface::on_security_status_update_cb(uintptr_t app_context, qeo_platform_security_context_t sec_context, qeo_platform_security_state state, qeo_platform_security_state_reason reason){

    /* Nothing special done here */
    (void)app_context;
    (void)sec_context;
    (void)state;
    (void)reason;

    qDebug() << __func__;

}

//---------------------------------------------
// Callback from qeo library
//---------------------------------------------
void QeoWebViewJavascriptInterface::on_json_async_event(const qeo_json_async_ctx_t *ctx, uintptr_t userdata, const char *id, const char *event, const char *json_data){

    /* Convert UTF-8 to UTF-16 for QString */
    QString idstr = QString::fromLocal8Bit(id);
    QString eventstr = QString::fromLocal8Bit(event);
    QString jsonstr = QString::fromLocal8Bit(json_data);
  
    /* Get your instance by casting it */
    QeoWebViewJavascriptInterface* webBridgeObj = (QeoWebViewJavascriptInterface*)userdata;

    qDebug() << "WebView [" << QThread::currentThreadId() << "]: " << __func__ << ", JS object Id: " << idstr << ", Event: " << eventstr << ", json Data: " << jsonstr;

    /* Put task on Main thread queue */
    emit webBridgeObj->invokeJavaScriptCall(idstr,eventstr,jsonstr);
}

QeoWebViewJavascriptInterface::QeoWebViewJavascriptInterface(QGraphicsWebView *webView, QObject *parent) :
    QObject(parent),mWebView(webView)
{
    qDebug() << "WebView[" << QThread::currentThreadId() << "]: C'tor" << __func__ ;

    /* Initialize callbacks */
    qeo_platform_callbacks_t platform_callbacks;
    platform_callbacks.on_reg_params_needed = on_registration_params_needed;
    platform_callbacks.on_sec_update = on_security_status_update_cb;

    qeo_json_async_listener_t ajson_callbacks;
    ajson_callbacks.on_qeo_json_event = on_json_async_event;

    /* Registr your custom meta type for usage in signals */
    qRegisterMetaType<qeo_platform_security_context_t>("qeo_platform_security_context_t");

    /* initialize qeo-c-util here */
    /* Setup platform security */
    if (qeo_platform_init((uintptr_t)this, &platform_callbacks) != QEO_UTIL_OK){
        qDebug() << "Could not init platform layer";
        /* this does not need to be a fatal error */ 
    }

    /* Setup Qeo interfacing context (store it) */
    if ((this->ajson_ctx = qeo_json_async_create(&ajson_callbacks, (uintptr_t)this)) == NULL){
        qDebug() << "Could not create json async ctx";
        throw "Could not create json async ctx";
    }

    /* setup signal-slot connections:*/
    connect(this,SIGNAL(invokeJavaScriptCall(QString, QString, QString)),this,SLOT(slot_JavaScriptCall(QString, QString, QString)),Qt::QueuedConnection);                               
    connect(this,SIGNAL(invokeRegistrationDialog(qeo_platform_security_context_t)),this,SLOT(slot_ShowRegistrationDialog(qeo_platform_security_context_t)),Qt::QueuedConnection);
    connect(this,SIGNAL(invokeMessageBox(QString,bool)),this,SLOT(slot_ShowMessageBox(QString,bool)),Qt::QueuedConnection);

}

QeoWebViewJavascriptInterface::~QeoWebViewJavascriptInterface() {
    qDebug() << "WebView: " << __func__ ;

    // Close the Qeo interfacing context
    qeo_json_async_close(this->ajson_ctx);

    // Remove all signal-slot connections
    disconnect();
}

void QeoWebViewJavascriptInterface::slot_JavaScriptCall(QString jsObjId, QString event, QString jsonData) {
    qDebug() << "WebView [" << QThread::currentThreadId() << "]: " << __func__ << ", JS object Id: " << jsObjId << ", Event: " << event << ", json Data: " << jsonData;
 
    // Assign \\ to backslash 
    QString backSlash = QString(QChar(0x5c)).append(QChar(0x5c));
    // Escape backslashes  
    jsonData = jsonData.replace('\\', backSlash);
    // Assing \" to quote.  
    QString quote = QString(QChar(0x5c)).append(QChar(0x22));
    // Escape double quote
    jsonData = jsonData.replace('"', quote);
    // Assing \" to single quote. */
    QString squote = QString(QChar(0x5c)).append(QChar(0x27));
    // Escape single quote  
    jsonData = jsonData.replace("'", squote);
    // Escape regular newline and carage returns
    jsonData = jsonData.replace( "\n", "\\n" );
    jsonData = jsonData.replace( "\r", "\\r" );
    // Escape unicode line separators
    QString lineSeparator = QString(QChar(0x5c)).append("\u2028");
    QString paragraphSeparator = QString(QChar(0x5c)).append("\u2029");
    jsonData = jsonData.replace("\u2028", lineSeparator);
    jsonData = jsonData.replace("\u2029", paragraphSeparator);
    // Escape NULL
    QString nullChar = QString(QChar(0x5c)).append("\u0000");
    jsonData = jsonData.replace("\u0000", nullChar);

    // Execute JavaScript  
    mWebView->page()->mainFrame()->evaluateJavaScript(QString("Qeo.notify('%1','%2','%3'); null").arg(jsObjId).arg(event).arg(jsonData));
}


void QeoWebViewJavascriptInterface::slot_ShowRegistrationDialog(qeo_platform_security_context_t sec_context) {
    qDebug() << "WebView[" << QThread::currentThreadId() << "]: " << __func__ ;

    // Setup dialg for security credentials
    OtcDialog *otcDialog = new OtcDialog(sec_context, NULL);
    otcDialog->setAttribute(Qt::WA_ShowModal,true);
    otcDialog->setAttribute(Qt::WA_DeleteOnClose,true);
    otcDialog->show();
}

void QeoWebViewJavascriptInterface::slot_ShowMessageBox(QString message,bool shutdown) {
    qDebug() << "WebView: " << __func__ ;

    QMessageBox msgBox;
    msgBox.setWindowTitle("Error Notification");
    QString msg = QString("<p align='center'>%1</p>").arg(message);
    msgBox.setText(msg);
    QStyle* style = msgBox.style();
    QIcon tmpIcon = style->standardIcon(QStyle::SP_MessageBoxCritical,0,&msgBox);
    msgBox.setWindowIcon(tmpIcon);
    msgBox.addButton(trUtf8("Close"), QMessageBox::YesRole);
    msgBox.show();
    msgBox.exec();

    if (true == shutdown){
        // exit application
        exit(0);
    }
}

void QeoWebViewJavascriptInterface::notify(QString event, QString options) {

    // Convert UTF-16 to UTF-8
    QByteArray eventBytes = event.toUtf8();
    QByteArray optionsBytes = options.toUtf8();

    // forward call to Qeo library
    if (qeo_json_async_call(this->ajson_ctx, eventBytes.data(), optionsBytes.data()) != QEO_OK){
        qDebug() << "Error: Could not queue cmd";
        
        QJsonDocument doc = QJsonDocument::fromJson(options.toUtf8());
        if (false == doc.isNull()) {
            QJsonObject jsonObj = doc.object();
            if ((false == jsonObj.isEmpty()) && (false == jsonObj.value(QString("id")).isUndefined())) {
                emit invokeJavaScriptCall(jsonObj.value(QString("id")).toString(),"error","{\"error\":\"Could not queue cmd\"}");
            }
            else {
                qDebug() << "options (JSON): id missing or invalid";
            }
        }
        else {
                qDebug() << "options: invalid JSON format";
        }
    }
}


