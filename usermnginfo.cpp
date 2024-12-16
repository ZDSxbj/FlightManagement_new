#include "userMngInfo.h"
#include "chatmanager.h"
#include "Mine.h"
#include <QMessageBox>
userMngInfo::userMngInfo(userData &data, QWidget *parent)
    : QWidget(parent), userdata(data) // 初始化成员 userdata
{




    // 初始化私有成员
    avatarLabel = new QLabel(this);
    nameLabel = new QLabel(this);
    emailLabel = new QLabel(this);
    phoneLabel = new QLabel(this);
    idCardLabel = new QLabel(this);
    genderLabel = new QLabel(this);
    balanceLabel = new QLabel(this);

    orderButton = new QPushButton("他的订单", this);
    contactButton = new QPushButton(this);

    // 设置按钮文本和连接信号与槽
    if (userdata.un_read_cnt > 0) {
        contactButton->setText(QString("联系用户(%1)").arg(userdata.un_read_cnt));
        contactButton->setStyleSheet(ReminderStyle);
    } else {
        contactButton->setText("联系用户");
        contactButton->setStyleSheet(NonReminderStyle);
    }


    // 根据 userData 的内容设置 QLabel 的文本
    nameLabel->setText(QString("姓名: %1").arg(userdata.username));
    emailLabel->setText(QString("Email: %1").arg(userdata.email));
    phoneLabel->setText(QString("电话: %1").arg(userdata.phone));
    idCardLabel->setText(QString("身份证: %1").arg(userdata.idCard));
    genderLabel->setText(QString("性别: %1").arg(userdata.gender));
    balanceLabel->setText(QString("余额: ¥%1").arg(QString::number(userdata.balance, 'f', 2))); // 保留两位小数

    // 设置字体
    QFont font;
    font.setPointSize(12); // 设置字体大小为 12

    // 应用字体到 QLabel
    nameLabel->setFont(font);
    emailLabel->setFont(font);
    phoneLabel->setFont(font);
    idCardLabel->setFont(font);
    genderLabel->setFont(font);
    balanceLabel->setFont(font);
    // 设置用户头像
    QPixmap avatar(userdata.avatar); // 假设头像路径保存在 userdata.avatar 中
    if (!avatar.isNull()) {
        avatarLabel->setPixmap(avatar.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        avatarLabel->setText("无头像");
        avatarLabel->setAlignment(Qt::AlignCenter);
    }

    // 创建布局
    mainLayout = new QVBoxLayout(this);

    // 创建上部水平布局
    topLayout = new QHBoxLayout();

    // 创建垂直布局显示用户信息
    leftInfoLayout = new QVBoxLayout();
    leftInfoLayout->addWidget(nameLabel);
    leftInfoLayout->addWidget(emailLabel);
    leftInfoLayout->addWidget(phoneLabel);

    // 创建另一个垂直布局显示额外信息
    rightInfoLayout = new QVBoxLayout();
    rightInfoLayout->addWidget(idCardLabel);
    rightInfoLayout->addWidget(genderLabel);
    rightInfoLayout->addWidget(balanceLabel);

    // 将头像和信息布局放入顶部水平布局
    // 在头像前添加 30 像素的间隔
    QSpacerItem *avatarSpacer = new QSpacerItem(30, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);
    topLayout->addItem(avatarSpacer); // 添加间隔
    topLayout->addWidget(avatarLabel);
    topLayout->addLayout(leftInfoLayout);
    topLayout->addLayout(rightInfoLayout);

    // 添加顶部布局到主垂直布局
    mainLayout->addLayout(topLayout);
    // 设置按钮样式
    orderButton->setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #7F7EFF, stop:1 #9E8CFE);" // 渐变紫色背景
        "color: white;" // 字体颜色为白色
        "border-radius: 10px;" // 圆角按钮
        "font-size: 14px;" // 字体大小
        "font-weight: bold;" // 字体加粗
        "padding: 5px 10px;" // 内边距
        "width: 100px;" // 按钮宽度
        "border: none;" // 无边框
        "}"
        "QPushButton:hover {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #9E8CFE, stop:1 #BCA4FF);" // 悬停时更亮
        "}"
        "QPushButton:pressed {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #6D6CFF, stop:1 #8E7AFE);" // 按下时更深
        "}"
        );


    // 使用 lambda 表达式直接在 connect 中定义槽函数
    connect(orderButton, &QPushButton::clicked, this, [this]() {
        // 创建 Mine 实例
        Mine *mineWindow = new Mine(userdata.idCard);

        // 设置为模态窗口，阻止用户与主窗口交互
        mineWindow->setWindowModality(Qt::ApplicationModal); // 如果 Mine 继承自 QWidget 使用此行

        // 显示窗口，并确保它处于最上层
        mineWindow->show();
        mineWindow->raise();
        mineWindow->activateWindow();
        mineWindow->resize(800,600);
        // 如果你需要在关闭 Mine 窗口后删除它以避免内存泄漏，请连接 closeEvent 或 destroyed 信号
        QObject::connect(mineWindow, &QWidget::destroyed, [mineWindow]() {
            delete mineWindow;
        });
    });

    connect(contactButton, &QPushButton::clicked, this, [this]() {
        // 弹出 Chatmanager 页面并传递 userdata.idCard 参数
        Chatmanager *chatWindow = new Chatmanager(userdata,this, userdata.idCard);
        chatWindow->show();
        chatWindow->setWindowModality(Qt::ApplicationModal);  // 设置为模态窗口
        // 更新未读消息计数为0
        userdata.un_read_cnt = 0;
        contactButton->setText("联系用户");
        QSqlQuery query;
        query.prepare("UPDATE unread_counts SET support_unread_count = 0 WHERE user_id = :idCard");
        query.bindValue(":idCard", userdata.idCard);

        if (!query.exec()) {
            QMessageBox::critical(this, "数据库错误", query.lastError().text());
        }
        contactButton->setStyleSheet(NonReminderStyle);
    });
    // 创建按钮布局
    buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch(); // 添加弹性空间以实现右对齐
    buttonLayout->addWidget(orderButton);
    buttonLayout->addWidget(contactButton);

    // 将按钮布局添加到主垂直布局
    mainLayout->addLayout(buttonLayout);

    // 设置窗口的主布局
    setLayout(mainLayout);
}
