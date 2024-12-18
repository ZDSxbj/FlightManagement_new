#ifndef FLIGHTINFO_H
#define FLIGHTINFO_H

#include <QWidget>
#include <QString>
#include <QDateTime>
#include <QTime>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QPropertyAnimation>
#include<QPainter>

#include"buywidget.h"
#include "FlightData.h"


class flightinfo : public QWidget {
    Q_OBJECT

public:
    explicit flightinfo(const FlightData &data, QWidget *parent = nullptr);
    ~flightinfo();

    double getPrice() const {
        // 定义一个足够大的初始值作为最低价格
        double lowestPrice = std::numeric_limits<double>::max();

        // 检查经济舱是否有可用座位并且更新最低价格
        if (data.economy_available_seats > 0) {
            lowestPrice = std::min(lowestPrice, data.economy_price);
        }

        // 检查商务舱是否有可用座位并且更新最低价格
        if (data.business_available_seats > 0) {
            lowestPrice = std::min(lowestPrice, data.business_price);
        }

        // 检查头等舱是否有可用座位并且更新最低价格
        if (data.first_class_available_seats > 0) {
            lowestPrice = std::min(lowestPrice, data.first_class_price);
        }

        // 如果所有舱位都没有可用座位，则返回 -1 或者其他你认为合适的值表示没有可用座位
        if (lowestPrice == std::numeric_limits<double>::max()) {
            return -1; // 或者抛出异常，或者返回特定值来表示错误状态
        }

        return lowestPrice;
    }
private slots:
    void showDetails();  // 显示或隐藏详情布局的槽函数
    void setupDetailsLayout();  // 设置舱位详细信息布局
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
    QPushButton *detailsButton;  // 详情按钮
    QLabel *priceLabel;   //多少元起
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
    // 动画相关成员
    QPropertyAnimation *animation;  // 动画对象
    void updatePriceLabel();  //显示价格标签

};

#endif // FLIGHTINFO_H


