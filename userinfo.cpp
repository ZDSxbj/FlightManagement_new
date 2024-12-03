#include "userinfo.h"

UserInfo::UserInfo(QWidget *parent)
    : QWidget(parent),
    nameLabel(new QLabel("Name:", this)),
    nameEdit(new QLineEdit(this)),
    emailLabel(new QLabel("Email:", this)),
    emailEdit(new QLineEdit(this)),
    saveButton(new QPushButton("Save", this))
{
    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 添加用户名部分到布局中
    QHBoxLayout *nameLayout = new QHBoxLayout();
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameEdit);
    layout->addLayout(nameLayout);

    // 添加电子邮件部分到布局中
    QHBoxLayout *emailLayout = new QHBoxLayout();
    emailLayout->addWidget(emailLabel);
    emailLayout->addWidget(emailEdit);
    layout->addLayout(emailLayout);

    // 添加保存按钮到布局中
    layout->addWidget(saveButton);

    // 设置窗口的默认布局
    setLayout(layout);
}
