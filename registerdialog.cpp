#include <httpmanager.h>
#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::RegisterDialog) {

    ui->setupUi(this);
    // 将密码框和确认框设置为密码模式
    ui->pwd_edit->setEchoMode(QLineEdit::Password);
    ui->confirm_edit->setEchoMode(QLineEdit::Password);

    // 添加样式设置
    ui->error_tip_label->setProperty("state", "normal");
    repolish(ui->error_tip_label);

    connect(ui->get_code, &QPushButton::clicked, this, &RegisterDialog::on_get_code_clicked);
    connect(HttpManager::Getinstance().get(), &HttpManager::sig_reg_mod_finish, this, &RegisterDialog::slot_reg_mod_finished);
}

RegisterDialog::~RegisterDialog() {
    delete ui;
}

void RegisterDialog::on_get_code_clicked()
{
    auto email = ui->email_edit->text();
    // 因为每次进入此函数时，创建的 regex 里的内容均相同，因此将其声明为 static 可避免重复创建
    static QRegularExpression regex {R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)"};
    bool match = regex.match(email).hasMatch();

    if (match) {
        // 后续 showTip 中的字符串需改变
        showTip("邮箱格式正确", true);
        // 发送 http 请求验证码

    } else {
        // 提示邮箱不正确
        showTip("邮箱地址不正确", false);
    }
}

void RegisterDialog::slot_reg_mod_finished(ReqId req_id, QString res, ErrorCodes ec)
{
    if (ec != ErrorCodes::SUCCESS) {
        showTip(tr("网络请求错误"), false);
        return;
    }

    // 解析 json 字符串，res 需转化为 QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    // json 解析出错
    if (jsonDoc.isNull()) {
        showTip(tr("json 解析出错"), false);
        return;
    }
    // json 解析出错
    if (!jsonDoc.isObject()) {
        showTip(tr("json 解析出错"), false);
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();
    // 调用对应的逻辑
    _handlers[req_id](jsonObj);
    return;
}

void RegisterDialog::initHttpHandlers()
{
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](QJsonObject jsonObj) {
        int error = jsonObj["error"].toInt();
        if (error != ErrorCodes::ERR_JSON) {
            showTip(tr("参数错误"), false);
            return;
        }

        auto email = jsonObj["email"].toString();
        showTip(tr("验证码已发送到邮箱，请注意查收"), true);
        qDebug() << "email is " << email;
    });
}

void RegisterDialog::showTip(QString str, bool is_right)
{
    ui->error_tip_label->setText(str);
    // 此处似乎可以用 crtp 模仿多态 或是直接使用多态，也可以使用键，以避免过多的 if else，以免违反开闭原则
    if (is_right) {
        ui->error_tip_label->setProperty("state", "normal");
    } else {
        ui->error_tip_label->setProperty("state", "err");
    }
    repolish(ui->error_tip_label);
}

