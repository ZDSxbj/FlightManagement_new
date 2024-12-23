#ifndef ADDFLIGHTWIDGET_H
#define ADDFLIGHTWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QFormLayout>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QPainter>
#include<QPainterPath>
class AddFlightWidget : public QWidget {
    Q_OBJECT

public:
    explicit AddFlightWidget(QWidget *parent = nullptr);

signals:
    void flightAdded(); // 添加航班成功后发送的信号

private slots:
    void submitFlight(); // 提交航班信息
    void updateDepartureAirports(const QString &city); // 更新出发地机场
    void updateArrivalAirports(const QString &city);   // 更新目的地机场

private:
    // void connectToDatabase(); // 连接数据库

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
        // int radius = 20; // 圆角半径
        // path.addRoundedRect(rect(), radius, radius);  // 添加圆角矩形

        // 绘制带圆角的矩形
        painter.drawPath(path);
    }
    // void paintEvent(QPaintEvent *event)
    // {
    //     // 调用父类的 paintEvent 以确保正常绘制
    //     QWidget::paintEvent(event);

    //     // 创建 QPainter 对象
    //     QPainter painter(this);

    //     // 设置抗锯齿
    //     painter.setRenderHint(QPainter::Antialiasing);

    //     // 创建线性渐变
    //     QLinearGradient gradient(rect().topLeft(), rect().bottomLeft());
    //     gradient.setColorAt(0, QColor("#E1E1E1"));   // 渐变起始颜色
    //     gradient.setColorAt(0.75, QColor("#F6FAFF")); // 中间颜色更接近 #F6FAFF
    //     gradient.setColorAt(1, QColor("#F6FAFF"));   // 渐变结束颜色

    //     // 设置画刷为渐变
    //     painter.setBrush(gradient);
    //     painter.setPen(Qt::NoPen);

    //     // 创建带圆角的矩形路径
    //     QPainterPath path;
    //     int radius = 20; // 圆角半径
    //     path.addRoundedRect(rect(), radius, radius);  // 添加圆角矩形

    //     // 绘制带圆角的矩形
    //     painter.drawPath(path);
    // }

    // UI 控件
    QComboBox *departureCity;
    QComboBox *destinationCity;
    QDateTimeEdit *departureTime;
    QDateTimeEdit *arrivalTime;
    QComboBox *airplaneModel;
    QLineEdit *departureAirport; // 修改为 QLineEdit*
    QLineEdit *arrivalAirport;   // 修改为 QLineEdit*
    QComboBox *departureTerminal;
    QComboBox *arrivalTerminal;
    QSpinBox *economyCapacity;
    QSpinBox *economyAvailable;
    QSpinBox *economyPrice;
    QSpinBox *businessCapacity;
    QSpinBox *businessAvailable;
    QSpinBox *businessPrice;
    QSpinBox *firstClassCapacity;
    QSpinBox *firstClassAvailable;
    QSpinBox *firstClassPrice;
    QComboBox *airlineComboBox;
    QLineEdit *flightNumberEdit;
};

#endif // ADDFLIGHTWIDGET_H









