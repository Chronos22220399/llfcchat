#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QRegularExpression>
#include "global.h"

namespace Ui {
class RegisterDialog;
}



/*********************************************************************
 * @file         registerdialog.h
 * @brief        注册页面
 *
 * @author       Ess
 * @date         2024/09/30
 * @history
 **********************************************************************/
class RegisterDialog : public QDialog {
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_get_code_clicked();
    void slot_reg_mod_finished(ReqId req_id, QString res, ErrorCodes ec);

private:
    Ui::RegisterDialog *ui;
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;

    void initHttpHandlers();
    void showTip(QString str, bool is_right);
};

#endif // REGISTERDIALOG_H
