#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include <functional>
#include <QStyle>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QMap>


extern std::function<void(QWidget*)> repolish;

/*********************************************************************
 * @file         global.h
 * @brief        http 请求 id
 *
 * @author       Ess
 * @date         2024/10/01
 * @history
 **********************************************************************/
enum ReqId {
    ID_GET_VARIFY_CODE = 1001,      // 获取验证码
    ID_REG_USER = 1002,             // 注册用户
};


/*********************************************************************
 * @file         global.h
 * @brief        错误码
 *
 * @author       Ess
 * @date         2024/10/01
 * @history
 **********************************************************************/
enum ErrorCodes {
    SUCCESS = 0,                    // 无错误
    ERR_JSON = 1,                   // json 解析失败
    ERR_NETWORK = 2,                // 网络通信错误，包括 http 请求与回应
};


/*********************************************************************
 * @file         global.h
 * @brief        模块
 *
 * @author       Ess
 * @date         2024/10/01
 * @history
 **********************************************************************/
enum Modules {
    REGISTERMOD = 0,                // 注册模块
};

#endif // GLOBAL_H
