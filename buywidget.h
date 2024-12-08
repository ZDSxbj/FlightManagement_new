#ifndef BUYWIDGET_H
#define BUYWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QScrollArea>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QLineEdit>
#include<QPainter>
#include<QPainterPath>
#include <QSet>
#include "someGlobal.h"
#include"FlightData.h"

class PassengerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PassengerWidget(QWidget *parent = nullptr);
    void setLabel(int index);
    QPushButton *confirmBtn;  // 确认按钮
    QPushButton *deleteBtn;   // 删除按钮
    QLineEdit *nameEdit;      // 姓名输入框
    QLineEdit *idCardEdit;    // 身份证输入框
    QLineEdit *phoneEdit;     // 电话号码输入框
signals:

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
    QLabel *indexLabel;       // 显示序号


};



//这就是个工具用来放置多次添加同一个乘车人，配合着set来用
struct PassengerInfo {
    QString name;
    QString idCard;
    QString phone;

    // 重载 `<` 运算符，确保结构体可以用于 QSet 的哈希和比较
    bool operator==(const PassengerInfo &other) const {
        return name == other.name && idCard == other.idCard && phone == other.phone;
    }
};
// 为结构体提供哈希函数，使其可以被 QSet 使用
inline uint qHash(const PassengerInfo &key, uint seed = 0) {
    return qHash(key.name, seed) ^ qHash(key.idCard, seed) ^ qHash(key.phone, seed);
}



class BuyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BuyWidget(FlightData data,int type,QWidget *parent = nullptr);


    ~BuyWidget();



private slots:
    void addPassenger(); // 添加乘机人的槽函数
    void updatePassengerList(); // 更新乘车人列表显示
    void removePassenger(PassengerWidget *passenger);
    bool validatePassengerInfo(PassengerWidget *passenger);
    void onPayButtonClicked();  //支付按钮
private:
    int type;   //机票类型，后来才记得加有点草率
    FlightData data;
    double seatPrice;
    // 私有成员变量
    QFrame *topFrame;
    QLabel *headerLabel;
    QPushButton *addPassengerButton;
    QScrollArea *scrollArea;
    QWidget *scrollWidget;
    QVBoxLayout *scrollLayout;
    QPushButton *payButton;
    QPushButton *cancelButton;
    QHBoxLayout *bottomLayout;
    QLabel *totalPriceLabel;
    void setPayment();
    QVector<PassengerWidget *> passengerWidgets; // 存储 PassengerWidget 的数组
    // 存储乘机人信息的 QSet
    QSet<PassengerInfo> passengerSet;

    // 执行支付操作：更新用户余额
    bool processPayment(double totalCost);
    // 更新航班座位数
    bool updateFlightSeats();

    // 更新指定舱位的座位数
    bool updateSeatCount(const QString &columnName, int &seats, int seatsToReduce);
    // 记录支付交易
    bool recordTransaction(double amount);
    // 创建订单：遍历乘机人信息，并插入订单
    bool createOrders();
    // 获取座舱类型的字符串
    QString getSeatClassString(int seatType);
};
#endif // BUYWIDGET_H
