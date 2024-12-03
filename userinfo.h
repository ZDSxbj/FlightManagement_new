#ifndef USERINFO_H
#define USERINFO_H

#include <QMainWindow>
#include <QWidget>

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class UserInfo : public QWidget {
    Q_OBJECT
public:
    UserInfo(QWidget *parent = nullptr);
    ~UserInfo(){}
private:
    QLabel *nameLabel; // 用户名标签
    QLineEdit *nameEdit; // 用户名输入框
    QLabel *emailLabel; // 电子邮件标签
    QLineEdit *emailEdit; // 电子邮件输入框
    QPushButton *saveButton; // 保存按钮
};

#endif // USERINFO_H
