#include "logindialog.h"
#include "ui_login_dialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
      QDialog(parent),
      ui(new Ui::login_dialog)
{
    ui->setupUi(this);

    ui->pwd_edit->setEchoMode(QLineEdit::Password);

    // 连接注册按钮，发送 切换到注册页面 的信号
    connect(ui->reg_btn, &QPushButton::clicked, this, &LoginDialog::switchRegister);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
