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
#ifndef OTCDIALOG_H
#define OTCDIALOG_H

#include <QDialog>
extern "C" {
    #include "platform_api/platform_api.h"
}

namespace Ui {
class OtcDialog;
}

class OtcDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit OtcDialog(qeo_platform_security_context_t sec_context, QWidget *parent = 0);
    ~OtcDialog();
    
private slots:
    void on_validateButton_clicked();
    void on_cancelButton_clicked();

private:
    qeo_platform_security_context_t sec_context;
    Ui::OtcDialog *ui;
};

#endif // OTCDIALOG_H
