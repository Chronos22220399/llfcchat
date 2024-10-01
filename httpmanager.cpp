#include "httpmanager.h"


HttpManager::HttpManager() {
    connect(this, &HttpManager::sig_http_finish, this, &HttpManager::slot_http_finish);
}

/*********************************************************************
 * @file         httpmanager.cpp
 * @brief        处理 http 请求
 *
 * @author       Ess
 * @date         2024/10/01
 * @history
 **********************************************************************/
void HttpManager::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)
{
    // 创建一个 HTTP POST 请求，并设置请求头和请求体
    QByteArray data = QJsonDocument(json).toJson();
    // 通过 url 构造请求
    QNetworkRequest request { url };
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));

    // 发送请求，并处理请求，获取智能指针 避免回调函数在使用单例时单例已被销毁的情况
    auto self { shared_from_this() };
    QNetworkReply *reply = _manager.post(request, data);

    // 提前检测是否完成： -- 来源于B站中对应的第 3 期视频中的评论
    if (reply->isFinished()) {
        std::cout << "请求已得到回应" << std::endl;
    }

    // 设置信号和槽等待发送完成
    QObject::connect(reply, &QNetworkReply::finished, [reply, self, req_id, mod](){
        // 处理错误的情况
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << reply->errorString();
            emit self->sig_http_finish(req_id, "", ErrorCodes::ERR_NETWORK, Modules::REGISTERMOD);
            reply->deleteLater();
            return;
        }

        // 请求无错误则读回请求
        QString res = reply->readAll();

        // 发送信号通知完成
        emit self->sig_http_finish(req_id, res, ErrorCodes::SUCCESS, mod);
        reply->deleteLater();
        return;
    });
}


// HttpManager 是一个通用模块，因此这里不会直接对每个错误进行处理，而是根据模式进行转发，以起到解耦的作用
void HttpManager::slot_http_finish(ReqId req_id, QString res, ErrorCodes ec, Modules mod)
{
    if (mod == Modules::REGISTERMOD) {
        // 发送信号指定模块 http 响应结束
        emit this->sig_reg_mod_finish(req_id, res, ec);
    }
}


HttpManager::~HttpManager() {}
