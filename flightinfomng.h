#ifndef FLIGHTINFOMNG_H
#define FLIGHTINFOMNG_H

#include <QObject>
#include <QWidget>
#include<QPainterPath>
#include "FlightData.h"
class flightinfomng : public QWidget
{
    Q_OBJECT
public:
    explicit flightinfomng(const FlightData &data, QWidget *parent);



    QPushButton *editTimeButton;  //修改时间按钮
    QPushButton *cancelFlightButton;  //取消航班



private:
    // 成员变量
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);

        // 启用抗锯齿
        painter.setRenderHint(QPainter::Antialiasing);

        // 绘制渐变背景
        QLinearGradient gradient(0, 0, 0, height());
        gradient.setColorAt(0, QColor(255, 255, 255));  // 白色
        gradient.setColorAt(1, QColor(224, 223, 255)); // 淡紫色

        painter.setBrush(gradient);
        painter.setPen(Qt::NoPen);  // 不需要边框

        // 创建带圆角的矩形路径
        QPainterPath path;
        int radius = 20; // 圆角半径
        path.addRoundedRect(0, 0, width(), height(), radius, radius);  // 添加圆角矩形

        // 绘制带圆角的背景
        painter.drawPath(path);

        QWidget::paintEvent(event);  // 确保子控件正确绘制
    }
    FlightData data;  // 航班数据
    QVBoxLayout *mainLayout;  // 主垂直布局
    QHBoxLayout *topLayout;  // 顶部水平布局
    QVBoxLayout *leftVerticalLayout;  // 左侧垂直布局
    QVBoxLayout *departureVerticalLayout;  // 出发信息垂直布局
    QVBoxLayout *arrivalVerticalLayout;  // 到达信息垂直布局
    QVBoxLayout *durationVerticalLayout;  // 历时信息垂直布局
    QVBoxLayout *detailsLayout;  // 详情布局
    QHBoxLayout *buttonLayout;  //button布局

    QLabel *airlineLabel;
    QLabel *flightNumberLabel;
    QLabel *airplaneModelLabel;
    QLabel *departureTimeLabel;
    QLabel *departureAirportLabel;
    QLabel *departureTerminalLabel;
    QLabel *arrivalTimeLabel;
    QLabel *arrivalAirportLabel;
    QLabel *arrivalTerminalLabel;
    QLabel *durationLabel;
    QLabel *sameDayArrivalLabel;



signals:
};

#endif // FLIGHTINFOMNG_H
