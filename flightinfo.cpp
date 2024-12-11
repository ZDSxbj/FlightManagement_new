#include "flightinfo.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QPropertyAnimation>
#include"buywidget.h"
flightinfo::flightinfo(const FlightData &data, QWidget *parent)
    : QWidget(parent), data(data)
{
    // 设置主布局
    mainLayout = new QVBoxLayout(this);
    QFont globalFont;

    globalFont.setPointSize(12);
    this->setFont(globalFont);
    // 创建顶部水平布局
    topLayout = new QHBoxLayout();
    mainLayout->addLayout(topLayout);

    // 创建左侧垂直布局（航空公司、航班编号、飞机型号）
    leftVerticalLayout = new QVBoxLayout();
    topLayout->addLayout(leftVerticalLayout);

    airlineLabel = new QLabel(data.airline);
    airlineLabel->setStyleSheet("font-weight: bold; color: #333; font-size: 16px;");
    leftVerticalLayout->addWidget(airlineLabel);

    flightNumberLabel = new QLabel(data.flight_number);

    leftVerticalLayout->addWidget(flightNumberLabel);

    airplaneModelLabel = new QLabel(data.airplane_model);
    airplaneModelLabel->setStyleSheet("color: #666; font-size: 16px;");
    leftVerticalLayout->addWidget(airplaneModelLabel);

    // 创建出发信息垂直布局（出发时间、机场、站楼）
    departureVerticalLayout = new QVBoxLayout();
    topLayout->addLayout(departureVerticalLayout);

    departureTimeLabel = new QLabel(data.departure_time.toString("HH:mm"));
    departureTimeLabel->setStyleSheet("color: #666; font-size: 16px;");
    departureVerticalLayout->addWidget(departureTimeLabel);

    departureAirportLabel = new QLabel(data.departure_airport);
    departureAirportLabel->setStyleSheet("color: #666; font-size: 16px;");
    departureVerticalLayout->addWidget(departureAirportLabel);

    departureTerminalLabel = new QLabel(data.departure_terminal);
    departureTerminalLabel->setStyleSheet("color: #666; font-size: 16px;");
    departureVerticalLayout->addWidget(departureTerminalLabel);

    // 创建水平分隔线
    QFrame *separator = new QFrame();
    separator->setFrameShape(QFrame::HLine); // 设置为水平线
    separator->setFrameShadow(QFrame::Sunken); // 设置阴影效果
    separator->setLineWidth(2); // 设置线宽（可选）
    separator->setFixedWidth(100); // 设置固定宽度，调整为适合你布局的长度（例如 300 像素）
    topLayout->addWidget(separator);

    // 创建到达信息垂直布局（到达时间、机场、站楼）
    arrivalVerticalLayout = new QVBoxLayout();
    topLayout->addLayout(arrivalVerticalLayout);

    arrivalTimeLabel = new QLabel(data.arrival_time.toString("HH:mm"));
    arrivalTimeLabel->setStyleSheet("color: #666; font-size: 16px;");
    arrivalVerticalLayout->addWidget(arrivalTimeLabel);

    arrivalAirportLabel = new QLabel(data.arrival_airport);
    arrivalAirportLabel->setStyleSheet("color: #666; font-size: 16px;");
    arrivalVerticalLayout->addWidget(arrivalAirportLabel);

    arrivalTerminalLabel = new QLabel(data.arrival_terminal);
    arrivalTerminalLabel->setStyleSheet("color: #666; font-size: 16px;");
    arrivalVerticalLayout->addWidget(arrivalTerminalLabel);

    // 创建历时信息垂直布局（历时、即日到达）
    durationVerticalLayout = new QVBoxLayout();
    topLayout->addLayout(durationVerticalLayout);

    durationLabel = new QLabel("历时: " + data.duration.toString("hh:mm"));
    durationLabel->setStyleSheet("color: #666; font-size: 14px;");
    durationVerticalLayout->addWidget(durationLabel);

    sameDayArrivalLabel = new QLabel(data.same_day_arrival ? "即日到达" : "次日到达");
    sameDayArrivalLabel->setStyleSheet("color: #666; font-size: 14px;");
    durationVerticalLayout->addWidget(sameDayArrivalLabel);

    // 设置价格标签样式
    priceLabel = new QLabel("111");
    priceLabel->setStyleSheet("font-weight: bold; color: #008000; font-size: 16px; margin-top: 5px;");
    updatePriceLabel(); // 初始化时调用 updatePriceLabel 设置正确的文本
    topLayout->addWidget(priceLabel);

    // 创建详情按钮
    detailsButton = new QPushButton("详情");
    detailsButton->setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #7F7EFF, stop:1 #9E8CFE);" // 渐变紫色背景
        "color: white;" // 字体颜色为白色
        "border-radius: 20px;" // 圆角按钮
        "font-size: 18px;" // 增大字体
        "font-weight: bold;" // 字体加粗
        "padding: 10px 20px;" // 增加内边距
        "min-width: 80px;" // 按钮最小宽度
        "border: none;" // 去除边框
        "}"
        "QPushButton:hover {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #9E8CFE, stop:1 #BCA4FF);" // 悬停时更亮的渐变色
        "}"
        "QPushButton:pressed {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #6D6CFF, stop:1 #8E7AFE);" // 按下时更深的渐变色
        "}"
        );
    detailsButton->setFixedWidth(120); // 固定宽度为 60px
    topLayout->addWidget(detailsButton);

    // 连接按钮信号和槽
    connect(detailsButton, &QPushButton::clicked, this, &flightinfo::showDetails);

    setupDetailsLayout();  // 初始化详情布局
}

flightinfo::~flightinfo()
{
    // 清理动画对象
    if (animation) {
        animation->stop();
        delete animation;
    }
}

void flightinfo::setupDetailsLayout()
{
    // 创建一个容器部件来容纳详情布局
    QWidget *detailsContainer = new QWidget(this);
    mainLayout->addWidget(detailsContainer);

    detailsLayout = new QVBoxLayout(detailsContainer);
    QString buttonStyle =
        "QPushButton {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #7F7EFF, stop:1 #9E8CFE);" // 渐变紫色背景
        "color: white;" // 字体颜色为白色
        "border-radius: 10px;" // 圆角按钮，边角更小
        "font-size: 14px;" // 较小字体
        "font-weight: bold;" // 字体加粗
        "padding: 5px 10px;" // 较小内边距
        "width: 60px;" // 按钮最小宽度
        "border: none;" // 去除边框
        "}"
        "QPushButton:hover {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #9E8CFE, stop:1 #BCA4FF);" // 悬停时更亮的渐变色
        "}"
        "QPushButton:pressed {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #6D6CFF, stop:1 #8E7AFE);" // 按下时更深的渐变色
        "}";

    // 经济舱信息
    if (data.economy_available_seats > 0) {
        QHBoxLayout *economyLayout = new QHBoxLayout();

        detailsLayout->addLayout(economyLayout);

        QLabel *economyLabel = new QLabel("经济舱");
        economyLayout->addWidget(economyLabel);

        QLabel *economyAvailableSeatsLabel = new QLabel("剩余座位: " + QString::number(data.economy_available_seats));
        economyLayout->addWidget(economyAvailableSeatsLabel);

        QLabel *economyPriceLabel = new QLabel("价格: " + QString::number(data.economy_price));
        economyLayout->addWidget(economyPriceLabel);

        economyPurchaseButton = new QPushButton("购买");
        economyLayout->addWidget(economyPurchaseButton);
        economyPurchaseButton->setFixedWidth(90); // 固定宽度为 60px
        economyPurchaseButton->setStyleSheet(buttonStyle);
    }

    // 商务舱信息
    if (data.business_available_seats > 0) {
        QHBoxLayout *businessLayout = new QHBoxLayout();
        detailsLayout->addLayout(businessLayout);

        QLabel *businessLabel = new QLabel("商务舱");
        businessLayout->addWidget(businessLabel);

        QLabel *businessAvailableSeatsLabel = new QLabel("剩余座位: " + QString::number(data.business_available_seats));
        businessLayout->addWidget(businessAvailableSeatsLabel);

        QLabel *businessPriceLabel = new QLabel("价格: " + QString::number(data.business_price));
        businessLayout->addWidget(businessPriceLabel);

        businessPurchaseButton = new QPushButton("购买");
        businessLayout->addWidget(businessPurchaseButton);

        businessPurchaseButton ->setStyleSheet(buttonStyle);
        businessPurchaseButton->setFixedWidth(90); // 固定宽度为 60px
    }

    // 头等舱信息
    if (data.first_class_available_seats > 0) {
        QHBoxLayout *firstClassLayout = new QHBoxLayout();
        detailsLayout->addLayout(firstClassLayout);

        QLabel *firstClassLabel = new QLabel("头等舱");
        firstClassLayout->addWidget(firstClassLabel);

        QLabel *firstClassAvailableSeatsLabel = new QLabel("剩余座位: " + QString::number(data.first_class_available_seats));
        firstClassLayout->addWidget(firstClassAvailableSeatsLabel);

        QLabel *firstClassPriceLabel = new QLabel("价格: " + QString::number(data.first_class_price));
        firstClassLayout->addWidget(firstClassPriceLabel);

        firstClassPurchaseButton = new QPushButton("购买");
        firstClassPurchaseButton ->setStyleSheet(buttonStyle);
        firstClassLayout->addWidget(firstClassPurchaseButton);
        firstClassPurchaseButton->setFixedWidth(90); // 固定宽度为 60px
    }
    connect(economyPurchaseButton, &QPushButton::clicked, [this]() {
        BuyWidget *widget = new BuyWidget(data,1);  //后面的数字是机票类型，后来才记得加，有点草率
        widget->setWindowModality(Qt::ApplicationModal);  // 设置为模态窗口
        widget->setWindowFlags(widget->windowFlags() | Qt::WindowStaysOnTopHint);
        widget->show();
        qDebug()<<"断点";
    });

    connect(businessPurchaseButton, &QPushButton::clicked, [this]() {
        BuyWidget *widget = new BuyWidget(data,2);
        widget->setWindowModality(Qt::ApplicationModal);  // 设置为模态窗口
        widget->setWindowFlags(widget->windowFlags() | Qt::WindowStaysOnTopHint);
        widget->show();
    });

    connect(firstClassPurchaseButton, &QPushButton::clicked, [this]() {
        BuyWidget *widget = new BuyWidget(data,3);
        widget->setWindowModality(Qt::ApplicationModal);  // 设置为模态窗口
        widget->setWindowFlags(widget->windowFlags() | Qt::WindowStaysOnTopHint);
        widget->show();
    });
    // 初始化动画对象，作用于容器部件的最大高度
    animation = new QPropertyAnimation(detailsContainer, "maximumHeight", this);
    animation->setDuration(200);  // 动画持续时间设为300毫秒

    // 设置初始状态为隐藏
    detailsContainer->setMaximumHeight(0);
}

void flightinfo::showDetails()
{
    // 检查当前状态并切换动画方向
    int currentHeight = detailsLayout->parentWidget()->maximumHeight();

    if (currentHeight == 0) {
        // 如果详情布局是隐藏的，则设置动画结束高度为内容的高度，并启动动画
        int contentHeight = detailsLayout->sizeHint().height();
        animation->setStartValue(0);
        animation->setEndValue(contentHeight);
        animation->start();
    } else {
        // 如果详情布局是可见的，则设置动画结束高度为0，并启动动画
        animation->setStartValue(currentHeight);
        animation->setEndValue(0);
        animation->start();
    }
}

void flightinfo::updatePriceLabel() {
    double price = getPrice();
    if (price == -1) {
        priceLabel->setText("已售空");
    } else {
        priceLabel->setText(QString::number(price, 'f', 2) + " 起"); // 格式化为两位小数并追加" 起"
    }
}
