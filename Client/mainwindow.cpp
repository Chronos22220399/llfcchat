#include "mainwindow.h"
#include "ui_mainwindow.h"

// 子界面的控件被触发后发送信号，主界面接收到信号后执行槽函数
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow) {
    ui->setupUi(this);

    login_dialog = new LoginDialog(this);
    login_dialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setCentralWidget(login_dialog);
    login_dialog->show();

    connect(login_dialog, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchReg);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SlotSwitchReg()
{
    // 创建和注册消息连接
    reg_dialog = new RegisterDialog(this);
    // 可能是为了切换更安全才将其 hide 起来
    reg_dialog->hide();
    reg_dialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    // 让 reg_dialog 能够在主窗口中显示，若没有这一句，主窗口不会显示注册页面
    setCentralWidget(reg_dialog);

    login_dialog->hide();
    reg_dialog->show();
}
