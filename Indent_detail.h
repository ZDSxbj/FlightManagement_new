#ifndef INDENT_DETAIL_H
#define INDENT_DETAIL_H

#include <QWidget>
#include <QDateTime>
#include<QTime>
#include<QVBoxLayout>
#include<QPainter>
#include<QMessageBox>
#include "someGlobal.h"
class Indent_detail : public QWidget
{
    Q_OBJECT
public:
    explicit Indent_detail(QWidget *parent,
                           const QString &uname,
                           const QString &departure_city,
                           const QString &departure_airport,
                           const QString &arrival_city,
                           const QString &arrival_airport,
                           const QString &number,
                           const QDateTime &udate,
                           const QDateTime &adate,
                           const QString &airline,
                           const QString &airmodel,
                           const QTime & Duration,
                           const QString& card,
                           int uclass,
                           double ucost,
                           //int Duration,
                           int ustatus,
                           int change,
                           bool day
                           );
    QDateTime getDepartureDate()const
    {
        return departure_Date;
    }

private:

    void getWidget();
    void setupDateAndStatusLabels(QVBoxLayout *layout);
    void setupFlightInfoLabels(QVBoxLayout *layout);
    void setupFlightDetailsLabels(QVBoxLayout *layout);
    void setupPassengerInfoLabels(QVBoxLayout *layout);
    void setupTicketActions(QVBoxLayout *layout);
    void paintEvent(QPaintEvent *event) override {
        // 先调用父类的 paintEvent 确保子控件正确绘制
        //QWidget::paintEvent(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿

        // 绘制渐变背景
        QLinearGradient gradient(0, 0, 0, height());
        if(statuss==0||statuss==3)
        {
            gradient.setColorAt(0, QColor(255, 255, 255));  // 白色
            gradient.setColorAt(1, QColor(224, 223, 255)); // 淡紫色
        }
        else
        {
            gradient.setColorAt(0, QColor(255, 255, 255));  // 白色
            gradient.setColorAt(1, QColor(138, 255, 230)); // 淡紫色
        }

        painter.setBrush(gradient);
        painter.setPen(Qt::NoPen);  // 不需要边框
        painter.drawRect(rect());   // 使用 rect() 方法获取整个 widget 的矩形区域
    }

    // 成员变量
    QString name;  // 真实姓名
    QString fli_number;
    int fli_class; // 舱位等级 1为头等舱，2为商务舱，3为经济舱
    double cost;      // 价格
    int statuss;
    QString departure_city, departure_airport, arrival_city, arrival_airport;
    QDateTime departure_Date;//离开天数时间
    QDateTime arrival_time;//到达天数时间
    QString airline,airmodel;
    QTime duration;
    QMessageBox *refundMessage;
    QString id_card;
    int change;
    bool day;
signals:
    void deleteRequested(const QString& name,const QString& plane,const int& uclass,const QDateTime& time,const double& price,const QString& id_card);
    void completed();
private slots:
    void ondeleteCliced();
    void handlecomplete();
};

#endif // INDENT_DETAIL_H
