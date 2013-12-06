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
#include "src/otcdialog.h"
#include "ui_otcdialog.h"
#include <QDebug>

OtcDialog::OtcDialog(qeo_platform_security_context_t _sec_context, QWidget *parent) :
    QDialog(parent),
    sec_context(_sec_context),
    ui(new Ui::OtcDialog)
{
    ui->setupUi(this);
}

OtcDialog::~OtcDialog()
{
    delete ui;
}

void OtcDialog::on_validateButton_clicked()
{
    qDebug() << "WebView: " << __func__ ;

    // grab the content of both edit boxes
    QString otc = findChild<QLineEdit*>("otcEditBox")->text().trimmed();
    QString url = findChild<QLineEdit*>("urlEditBox")->text().trimmed();

    qDebug() << "WebView: " << __func__ << ", otc: " << otc << ", url" << url;

    QByteArray otcBuffer = otc.toUtf8();
    QByteArray urlBuffer = url.toUtf8();

    // call qeo-c-util verification method !!
    qeo_platform_set_otc_url(sec_context,otcBuffer.data(),urlBuffer.data());

    close();
}

void OtcDialog::on_cancelButton_clicked()
{
    qDebug() << "WebView: " << __func__ ;

    // call qeo-c-util cancel method !!
    qeo_platform_cancel_registration(sec_context);

    close();
}
