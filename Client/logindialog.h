#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class login_dialog;
}

/*********************************************************************
 * @file         logindialog.h
 * @brief        登录页面
 *
 * @author       Ess
 * @date         2024/09/30
 * @history
 **********************************************************************/
class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::login_dialog *ui;


signals:
    void switchRegister();
};

#endif // LOGINDIALOG_H
