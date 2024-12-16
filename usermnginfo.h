#ifndef USERMNGINFO_H
#define USERMNGINFO_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QPainter>
#include<QPainterPath>
#include "userData.h"  // 包含userData结构体的头文件

class userMngInfo : public QWidget
{
    Q_OBJECT
public:
    explicit userMngInfo(userData &data, QWidget *parent = nullptr); // 修改构造函数以接受userData参数

private:
    void paintEvent(QPaintEvent *event)
    {
        // 调用父类的 paintEvent 以确保正常绘制
        QWidget::paintEvent(event);

        // 创建 QPainter 对象
        QPainter painter(this);

        // 设置抗锯齿
        painter.setRenderHint(QPainter::Antialiasing);

        // 创建线性渐变
        QLinearGradient gradient(rect().topLeft(), rect().bottomLeft());
        gradient.setColorAt(0, QColor("#E1E1E1"));   // 渐变起始颜色
        gradient.setColorAt(0.75, QColor("#F6FAFF")); // 中间颜色更接近 #F6FAFF
        gradient.setColorAt(1, QColor("#F6FAFF"));   // 渐变结束颜色

        // 设置画刷为渐变
        painter.setBrush(gradient);
        painter.setPen(Qt::NoPen);

        // 创建带圆角的矩形路径
        QPainterPath path;
        int radius = 20; // 圆角半径
        path.addRoundedRect(rect(), radius, radius);  // 添加圆角矩形

        // 绘制带圆角的矩形
        painter.drawPath(path);
    }
    QLabel *avatarLabel;                // 用户头像
    QLabel *nameLabel;                  // 姓名标签
    QLabel *emailLabel;                 // Email 标签
    QLabel *phoneLabel;                 // 电话标签
    QLabel *idCardLabel;                // 身份证标签
    QLabel *genderLabel;                // 性别标签
    QLabel *balanceLabel;               // 余额标签

    QPushButton *orderButton;           // "他的订单" 按钮
    QPushButton *contactButton;         // "联系用户" 按钮

    QVBoxLayout *mainLayout;            // 主垂直布局
    QHBoxLayout *topLayout;             // 上部水平布局
    QVBoxLayout *leftInfoLayout;        // 左边信息布局
    QVBoxLayout *rightInfoLayout;       // 右边信息布局
    QHBoxLayout *buttonLayout;          // 按钮布局
    // 非提醒样式：更深的颜色
    const QString NonReminderStyle=
        "QPushButton {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FFC085, stop:1 #FF9A5B);" // 渐变橙黄色背景
        "color: white;" // 字体颜色为白色
        "border-radius: 10px;" // 圆角按钮
        "font-size: 14px;" // 字体大小
        "font-weight: bold;" // 字体加粗
        "padding: 5px 10px;" // 内边距
        "width: 100px;" // 按钮宽度
        "border: none;" // 无边框
        "}"
        "QPushButton:hover {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FFD5A2, stop:1 #FFB67C);" // 悬停时更亮
        "}"
        "QPushButton:pressed {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #E69E6C, stop:1 #CC8654);" // 按下时更深
        "}";   //按钮样式
    // 提醒样式：更亮眼的颜色
    const QString ReminderStyle =
        "QPushButton {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FFD700, stop:1 #FFA500);"
        "color: white;"
        "border-radius: 10px;"
        "font-size: 14px;"
        "font-weight: bold;"
        "padding: 5px 10px;"
        "width: 100px;"
        "border: none;"
        "}"
        "QPushButton:hover {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FFE68C, stop:1 #FFB964);"
        "}"
        "QPushButton:pressed {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #E6A839, stop:1 #CC8F31);"
        "}";
    userData &userdata;                  // 保存用户数据的结构体

};

#endif // USERMNGINFO_H
