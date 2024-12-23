#ifndef FLIGHTINFOMNG_H
#define FLIGHTINFOMNG_H

#include <QObject>
#include <QWidget>
#include<QPainterPath>
#include "FlightData.h"
#include<QSqlQuery>
#include<QSqlError>
#include<QMessageBox>
#include<QDateTime>
#include<QDateTimeEdit>
class flightinfomng : public QWidget
{
    Q_OBJECT
public:
    explicit flightinfomng(FlightData &data, QWidget *parent);



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
    FlightData &data;  // 航班数据
    QVBoxLayout *mainLayout;  // 主垂直布局
    QHBoxLayout *topLayout;  // 顶部水平布局
    QVBoxLayout *leftVerticalLayout;  // 左侧垂直布局
    QVBoxLayout *departureVerticalLayout;  // 出发信息垂直布局
    QVBoxLayout *arrivalVerticalLayout;  // 到达信息垂直布局
    QVBoxLayout *durationVerticalLayout;  // 历时信息垂直布局
    QVBoxLayout *detailsLayout;  // 详情布局
    QHBoxLayout *buttonLayout;  //button布局

    QLabel *airlineLabel;
    QLabel *depatureDataLabel;
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
    QMessageBox *refundMessage;

private slots:
    void onclickedcancel();

    inline void onEditTimeButtonClicked()
    {
        // 弹出一个对话框，包含 QDateTimeEdit
        QDialog dialog(this);
        dialog.setWindowTitle("修改起飞和降落时间");

        // 设置弹窗按钮样式
        dialog.setStyleSheet(
            "QPushButton {"
            "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #7F7EFF, stop:1 #9E8CFE);" // 渐变紫色背景
            "    color: white;" // 字体颜色为白色
            "    border-radius: 10px;" // 圆角按钮
            "    font-size: 14px;" // 字体大小
            "    font-weight: bold;" // 字体加粗
            "    padding: 5px 10px;" // 内边距
            "    border: none;" // 无边框
            "}"
            "QPushButton:hover {"
            "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #9E8CFE, stop:1 #BCA4FF);" // 悬停时更亮的渐变色
            "}"
            "QPushButton:pressed {"
            "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #6D6CFF, stop:1 #8E7AFE);" // 按下时更深的渐变色
            "}"
            );

        // 调整弹窗大小
        dialog.resize(400, 200);  // 设置弹窗大小（宽度400，高度300）

        // 创建布局
        QVBoxLayout *dialogLayout = new QVBoxLayout(&dialog);

        // 添加起飞时间 QLabel 控件，并设置字体加粗加大
        QLabel *departureLabel = new QLabel("起飞时间", &dialog);
        departureLabel->setStyleSheet("color: #7F7EFF; font-size: 18px; font-weight: bold;");
        dialogLayout->addWidget(departureLabel);
        QDateTimeEdit *departureTimeEdit = new QDateTimeEdit(data.departure_time, &dialog);
        departureTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm");
        departureTimeEdit->setCalendarPopup(true); // 启用日历功能
        dialogLayout->addWidget(departureTimeEdit);

        // 添加降落时间 QLabel 控件，并设置字体加粗加大
        QLabel *arrivalLabel = new QLabel("降落时间", &dialog);
        arrivalLabel->setStyleSheet("color: #7F7EFF; font-size: 18px; font-weight: bold;");
        dialogLayout->addWidget(arrivalLabel);
        QDateTimeEdit *arrivalTimeEdit = new QDateTimeEdit(data.arrival_time, &dialog);
        arrivalTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm");
        arrivalTimeEdit->setCalendarPopup(true); // 启用日历功能
        dialogLayout->addWidget(arrivalTimeEdit);

        // 添加确认和取消按钮
        QPushButton *okButton = new QPushButton("确认", &dialog);
        QPushButton *cancelButton = new QPushButton("取消", &dialog);
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);
        dialogLayout->addLayout(buttonLayout);

        // 设置按钮的样式
        okButton->setStyleSheet(
            "QPushButton {"
            "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #7F7EFF, stop:1 #9E8CFE);"
            "    color: white;"
            "    border-radius: 10px;"
            "    font-size: 14px;"
            "    font-weight: bold;"
            "    padding: 5px 10px;"
            "    border: none;"
            "}"
            "QPushButton:hover {"
            "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #9E8CFE, stop:1 #BCA4FF);"
            "}"
            "QPushButton:pressed {"
            "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #6D6CFF, stop:1 #8E7AFE);"
            "}"
            );

        cancelButton->setStyleSheet(
            "QPushButton {"
            "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #7F7EFF, stop:1 #9E8CFE);"
            "    color: white;"
            "    border-radius: 10px;"
            "    font-size: 14px;"
            "    font-weight: bold;"
            "    padding: 5px 10px;"
            "    border: none;"
            "}"
            "QPushButton:hover {"
            "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #9E8CFE, stop:1 #BCA4FF);"
            "}"
            "QPushButton:pressed {"
            "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #6D6CFF, stop:1 #8E7AFE);"
            "}"
            );

        // 连接按钮信号
        connect(okButton, &QPushButton::clicked, [&]() {
            QDateTime newDepartureTime = departureTimeEdit->dateTime();
            QDateTime newArrivalTime = arrivalTimeEdit->dateTime();

            if (!newDepartureTime.isValid() || !newArrivalTime.isValid()) {
                QMessageBox::warning(this, "无效时间", "选择的时间无效，请重试！");
                return;
            }

            // 检查到达时间是否早于起飞时间
            if (newArrivalTime < newDepartureTime) {
                QMessageBox::warning(this, "错误", "降落时间不能早于起飞时间，请重新选择！");
                return;
            }

            // 计算duration和same_day_arrival
            qint64 durationSeconds = newDepartureTime.secsTo(newArrivalTime);
            QTime durationTime = QTime::fromMSecsSinceStartOfDay(durationSeconds * 1000); // 转换为小时、分钟、秒

            bool sameDayArrival = newDepartureTime.date() == newArrivalTime.date();

            // 更新数据库
            QSqlQuery query;
            query.prepare("UPDATE flights SET departure_time = :departure_time, arrival_time = :arrival_time, "
                          "duration = :duration, same_day_arrival = :same_day_arrival, status = 'Delayed' WHERE flight_number = :flight_number");
            query.bindValue(":departure_time", newDepartureTime.toString("yyyy-MM-dd HH:mm:ss"));
            query.bindValue(":arrival_time", newArrivalTime.toString("yyyy-MM-dd HH:mm:ss"));
            query.bindValue(":duration", durationTime.toString("HH:mm:ss"));
            query.bindValue(":same_day_arrival", sameDayArrival);
            query.bindValue(":flight_number", data.flight_number);

            if (query.exec()) {
                QMessageBox::information(this, "修改成功", "起飞时间和降落时间已成功更新，状态已变更为‘延误’！");
                // 同时更新本地数据
                data.departure_time = newDepartureTime;
                data.arrival_time = newArrivalTime;
                data.duration = durationTime;
                data.same_day_arrival = sameDayArrival;
                data.status = "Delayed";  // 更新状态为"延误"

                departureTimeLabel->setText(newDepartureTime.toString("HH:mm"));
                depatureDataLabel->setText(newDepartureTime.date().toString("yyyy-MM-dd"));
                arrivalTimeLabel->setText(newArrivalTime.toString("HH:mm"));
                durationLabel->setText(durationTime.toString("历时:HH:mm"));
                sameDayArrivalLabel->setText(sameDayArrival ? "即日到达" : "次日到达");
            } else {
                QMessageBox::critical(this, "修改失败", "更新数据库失败，请重试！");
            }

            dialog.accept();
        });

        connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

        // 显示对话框
        dialog.exec();
    }

signals:
    void iscanceled(FlightData data);
};

#endif // FLIGHTINFOMNG_H
