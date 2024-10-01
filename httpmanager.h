#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QUrl>
#include "global.h"
#include "singleton.h"


/*********************************************************************
 * @file         httpmanager.cpp
 * @brief        管理 http 的请求及回应
 *
 * @author       Ess
 * @date         2024/10/01
 * @history
 **********************************************************************/


// the syntax in here is CRTP
class HttpManager: public QObject, public SingleTon<HttpManager>, std::enable_shared_from_this<HttpManager>
{
    Q_OBJECT
public:
    ~HttpManager();
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);

private:
    friend class SingleTon<HttpManager>;     // SingleTon<HttpManager> must be friend class, because std::shared_ptr(new T) need use constructor
    HttpManager();

    QNetworkAccessManager _manager;

private slots:
    void slot_http_finish(ReqId req_id, QString res, ErrorCodes ec, Modules mod);

signals:
    void sig_http_finish(ReqId req_id, QString res, ErrorCodes ec, Modules mod);
    void sig_reg_mod_finish(ReqId req_id, QString res, ErrorCodes ec);
};

#endif // HTTPMANAGER_H
