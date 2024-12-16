#ifndef USERINFO_H
#define USERINFO_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "someGlobal.h"
class UserInfo : public QWidget {
    Q_OBJECT

public:
    explicit UserInfo(QWidget *parent = nullptr);
    ~UserInfo();

    void loadUserData(const QString &username); // 加载用户数据

private slots:
    void onEditAvatar();
    void onEditPhone();
    void onEditEmail();
    void onEditGender();
    void onEditBirthday();
    void onEditPassword();

private:
    void saveUserData(const QString &field, const QString &value); // 保存到数据库

    QLabel *avatarLabel;       // 头像显示
    QLabel *phoneLabel;        // 手机号显示
    QLabel *emailLabel;        // 邮箱显示
    QLabel *nameLabel;         // 姓名显示
    QLabel *genderLabel;       // 性别显示
    QLabel *birthdayLabel;     // 生日显示
    QLabel *passwordLabel;     // 密码显示
    QLabel *idCardLabel;       // 身份证号显示（新增）
    QPushButton *avatarEditButton; // 修改头像按钮
};

#endif // USERINFO_H
