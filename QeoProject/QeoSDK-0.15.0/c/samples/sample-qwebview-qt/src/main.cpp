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
#include <QUrl>
#include <QApplication>
#include <QWebFrame>
#include <QGraphicsWebView>

#ifdef DEBUG
#include <QWebInspector>
#endif

#include "html5applicationviewer.h"
#include "qeowebviewjavascriptinterface.h"

#ifdef TEST
#include "testjavascriptinterface.h"
#endif


int main(int argc, char* argv[])
{

    QApplication app(argc, argv);

    Html5ApplicationViewer viewer;
    viewer.webView()->setResizesToContents(true);


#ifdef DEBUG
    viewer.webView()->page()->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    QWebInspector inspector;
    inspector.setPage(viewer.webView()->page());
    inspector.setVisible(true);
#endif

    QeoWebViewJavascriptInterface* mQeoJS = new QeoWebViewJavascriptInterface(viewer.webView());
    viewer.webView()->page()->mainFrame()->addToJavaScriptWindowObject(QString("QeoJS"), mQeoJS);

#ifdef TEST
    TestJavascriptInterface* mTestJS = new TestJavascriptInterface(viewer.webView());
    viewer.webView()->page()->mainFrame()->addToJavaScriptWindowObject(QString("TestReporter"), mTestJS);
#endif


    viewer.loadFile(QLatin1String(argv[1]));
    viewer.setOrientation(Html5ApplicationViewer::ScreenOrientationAuto);
    viewer.showExpanded();

    return app.exec();

}
