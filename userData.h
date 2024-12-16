#ifndef USERDATA_H
#define USERDATA_H

#include <QString>
#include <QDateTime>

struct userData {
    int id;                   // 用户ID
    QString username;         // 用户名
    QString password;         // 密码
    QString email;            // 电子邮件
    QDateTime registrationDate;  // 注册日期
    QString status;           // 用户状态 (例如: active)
    QString phone;            // 电话号码
    QString gender;           // 性别 (male, female)
    QDateTime birthday;       // 生日
    QString avatar;           // 头像文件名
    double balance;           // 账户余额
    QString idCard;           // 身份证号
    int un_read_cnt;         //管理员未读的消息
};

#endif // USERDATA_H
