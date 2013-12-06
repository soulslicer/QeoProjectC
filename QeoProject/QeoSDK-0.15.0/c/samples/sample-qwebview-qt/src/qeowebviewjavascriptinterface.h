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
#ifndef QEOWEBVIEWJAVASCRIPTINTERFACE_H
#define QEOWEBVIEWJAVASCRIPTINTERFACE_H

#include <QObject>

extern "C" {
    #include "qeo/jsonasync.h"
    #include "platform_api/platform_api.h"
}

class QGraphicsWebView;

class QeoWebViewJavascriptInterface : public QObject
{
    Q_OBJECT
public:
    explicit QeoWebViewJavascriptInterface(QGraphicsWebView *webView,QObject *parent = 0);
    virtual ~QeoWebViewJavascriptInterface();

//-----------------------------------------
// Signals: put task on Main thread queue
//-----------------------------------------
signals:
    void invokeJavaScriptCall(QString jsObjId, QString event, QString jsonData);              
    void invokeRegistrationDialog(qeo_platform_security_context_t sec_context);
    void invokeMessageBox(QString message,bool shutdown);

//-----------------------------------------
// Methods available in JavaScript (as QeoJS)
//-----------------------------------------
public slots:
    void notify(QString event, QString options);

private slots:
    void slot_JavaScriptCall(QString jsObjId, QString event, QString jsonData);         
    void slot_ShowRegistrationDialog(qeo_platform_security_context_t sec_context);
    void slot_ShowMessageBox(QString message, bool shutdown);

private:
    static qeo_util_retcode_t on_registration_params_needed(uintptr_t app_context, qeo_platform_security_context_t sec_context);
    static void on_security_status_update_cb(uintptr_t app_context, qeo_platform_security_context_t sec_context, qeo_platform_security_state state, qeo_platform_security_state_reason reason);
    static void on_json_async_event(const qeo_json_async_ctx_t *ctx, uintptr_t userdata, const char *id, const char *event, const char *jsonData);

private:
    QGraphicsWebView*  mWebView;
    qeo_json_async_ctx_t *ajson_ctx;
};

#endif // QEOWEBVIEWJAVASCRIPTINTERFACE_H
