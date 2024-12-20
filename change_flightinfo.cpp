#include "change_flightinfo.h"
#include"someGlobal.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QPropertyAnimation>
#include<QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include<QSqlError>
#include<QSqlQuery>
change_flightinfo::change_flightinfo(const FlightData &data,const QString& real_name,const QString& fli_number,const QString& fli_class,const QDateTime& departure_date,const double price,const QString& card,  QWidget *parent)
    : QWidget(parent), data(data),real_name(real_name),fli_number(fli_number),fli_class(fli_class),departure_date(departure_date),price(price),id_card(card)
{
    // 设置主布局
    //            change_flightinfo *newFlightInfo = new change_flightinfo(data,real_name,fli_class,cost,this);
    mainLayout = new QVBoxLayout(this);
    QFont globalFont;

    economyPurchaseButton = new QPushButton("改签");
    businessPurchaseButton = new QPushButton("改签");
    firstClassPurchaseButton = new QPushButton("改签");
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
    topLayout->addWidget(detailsButton);


    connect(detailsButton, &QPushButton::clicked, this, &change_flightinfo::showDetails);

    setupDetailsLayout();  // 初始化详情布局

    QSignalMapper *signalMapper = new QSignalMapper(this);


    // 设置映射关系
    signalMapper->setMapping(economyPurchaseButton, "economy");
    signalMapper->setMapping(businessPurchaseButton, "business");
    signalMapper->setMapping(firstClassPurchaseButton, "first_class");

    // 连接按钮点击信号到 QSignalMapper 的 map 槽
    connect(economyPurchaseButton, &QPushButton::clicked, signalMapper,  static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
    connect(businessPurchaseButton, &QPushButton::clicked, signalMapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
    connect(firstClassPurchaseButton, &QPushButton::clicked, signalMapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));

    // 将信号映射器的 mappedString 信号连接到槽函数
    connect(signalMapper, &QSignalMapper::mappedString, this, &change_flightinfo::onclicked);
}

change_flightinfo::~change_flightinfo()
{
    // 清理动画对象
    if (animation) {
        animation->stop();
        delete animation;
    }
}

void change_flightinfo::setupDetailsLayout()
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


        firstClassPurchaseButton ->setStyleSheet(buttonStyle);
        firstClassLayout->addWidget(firstClassPurchaseButton);
        firstClassPurchaseButton->setFixedWidth(90); // 固定宽度为 60px
    }

    // 初始化动画对象，作用于容器部件的最大高度
    animation = new QPropertyAnimation(detailsContainer, "maximumHeight", this);
    animation->setDuration(300);  // 动画持续时间设为300毫秒

    // 设置初始状态为隐藏
    detailsContainer->setMaximumHeight(0);
}

void change_flightinfo::showDetails()
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

void change_flightinfo::updatePriceLabel() {
    double price = getPrice();
    if (price == -1) {
        priceLabel->setText("已售空");
    } else {
        priceLabel->setText(QString::number(price, 'f', 2) + " 起"); // 格式化为两位小数并追加" 起"
    }
}

void  change_flightinfo::onclicked(const QString &type) {
    // 密码输入对话框
    bool ok;
    QString passwords = QInputDialog::getText(nullptr,
                                              tr("密码输入"),
                                              tr("请输入密码:"),
                                              QLineEdit::Password,
                                              QString(),
                                              &ok);

    if (!ok || passwords.isEmpty()) {
        QMessageBox::warning(nullptr, "警告", "取消操作");
        return;
    }
    QSqlDatabase dbc;
    dbc = QSqlDatabase::addDatabase("QODBC","database");
    dbc.setHostName("127.0.0.1");
    dbc.setPort(3306);
    dbc.setDatabaseName("Local instance MySQL8");
    dbc.setUserName("root");  // 添加用户名
    dbc.setPassword("ZXJsnd4697");  // 添加密码

    bool ok1 = dbc.open();
    if (!ok1) {
        qDebug() << "Error, persondatabase 数据库文件打开失败！" << dbc.lastError().text();
    } else {
        qDebug() << "Success, persondatabase 数据库文件打开成功！";
    }

    if (!dbc.transaction()) {
        qDebug() << "Failed to start transaction:" << dbc.lastError().text();
        dbc.close();
        return;
    }

    // 创建独立的 QSqlQuery 对象用于每个查询
    QSqlQuery passwordQuery(dbc);
    QSqlQuery deleteOrderQuery(dbc);
    QSqlQuery updateSeatsQuery(dbc);
    QSqlQuery newOrderQuery(dbc);
    QSqlQuery walletTransactionQuery(dbc);

    // 验证用户密码
    if (!verifyUserPassword(passwordQuery, passwords)) {
        QMessageBox::warning(nullptr, "警告", "输入密码错误，请重新输入");
        dbc.rollback();
        dbc.close();
        return;
    }

    // 删除旧订单并更新航班座位
    if (!deleteOldOrderAndUpdateSeats(deleteOrderQuery, updateSeatsQuery)) {
        dbc.rollback();
        dbc.close();
        return;
    }

    //创建新订单
    if (!createNewOrder(newOrderQuery, type)) {
        dbc.rollback();
        dbc.close();
        return;
    }

    //更新钱包交易记录
    if (!updateWalletTransaction(walletTransactionQuery, type)) {
        dbc.rollback();
        dbc.close();
        return;
    }

    // 提交事务
    if (dbc.commit()) {
        qDebug() << "All operations completed successfully.";
    } else {
        qDebug() << "Failed to commit transaction:" << dbc.lastError().text();
        dbc.rollback(); // 确保在提交失败时回滚
    }

    dbc.close();
    emit completed();
    isPay=true;
    this->close();
}

bool change_flightinfo::verifyUserPassword(QSqlQuery &query, const QString &passwords) {
    query.prepare("SELECT * FROM users WHERE password=:password AND ID_card= :ID_card");
    query.bindValue(":password", passwords);
    query.bindValue(":ID_card", id_card);

    if (!query.exec()) {
        qDebug() << "Password verification failed:" << query.lastError().text();
        return false;
    }
    return query.next(); // 返回是否找到匹配项
}

bool change_flightinfo::deleteOldOrderAndUpdateSeats(QSqlQuery &deleteOrderQuery, QSqlQuery &updateSeatsQuery) {
    // 删除旧订单
    deleteOrderQuery.prepare("DELETE FROM orders WHERE realname= :realname AND flight_number = :flight_number AND departure_time=:departure_time");
    deleteOrderQuery.bindValue(":realname", real_name);
    deleteOrderQuery.bindValue(":flight_number", fli_number);
    deleteOrderQuery.bindValue(":departure_time", data.departure_time);
    qDebug()<<real_name<<" "<<fli_number;
    if (!deleteOrderQuery.exec()) {
        qDebug() << "Failed to execute delete order query:" << deleteOrderQuery.lastError().text();
        return false;
    }

    // 更新航班座位数
    QString seatClass = fli_class.toLower();
    updateSeatsQuery.prepare(QString("UPDATE flights SET %1_available_seats = %1_available_seats + 1 WHERE flight_number= :flight_number AND departure_time=:departure_time")
                                 .arg(seatClass));
    updateSeatsQuery.bindValue(":flight_number", data.flight_number);
    updateSeatsQuery.bindValue(":departure_time", data.departure_time); // 格式化时间字符串
    if (!updateSeatsQuery.exec()) {
        qDebug() << "Failed to execute update seats query:" << updateSeatsQuery.lastError().text();
        return false;
    }

    return true;
}

bool change_flightinfo::createNewOrder(QSqlQuery &query, const QString &type) {
    int now_price = getPrice(type); // 假设有一个方法获取对应舱位的价格

    query.prepare("INSERT INTO orders (Id_card, realname, flight_number, changed, order_date, seat_class, price, status, departure_time) "
                  "VALUES (:Id_card, :realname, :flight_number, :changed, :order_date, :seat_class, :price, :status, :departure_time)");
    query.bindValue(":Id_card", id_card);
    query.bindValue(":realname", real_name);
    query.bindValue(":flight_number", data.flight_number);
    query.bindValue(":changed", 0); // 假设 `changed` 是一个布尔值
    query.bindValue(":order_date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")); // 格式化日期时间字符串
    query.bindValue(":seat_class", type);
    query.bindValue(":price", now_price);
    query.bindValue(":status", "upcoming");
    query.bindValue(":departure_time", departure_date.toString("yyyy-MM-dd hh:mm:ss")); // 格式化日期时间字符串

    if (!query.exec()) {
        qDebug() << "Failed to create new order:" << query.lastError().text();
        return false;
    }
    query.prepare(QString("UPDATE flights SET %1_available_seats = %1_available_seats - 1 WHERE flight_number= :flight_number AND departure_time=:departure_time")
                      .arg(type));
    query.bindValue(":flight_number", data.flight_number);
    query.bindValue(":departure_time", data.departure_time); // 格式化时间字符串
    if (!query.exec()) {
        qDebug() << "Failed to execute update seats query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool change_flightinfo::updateWalletTransaction(QSqlQuery &query, const QString &type) {
    double now_price = getPrice(type); // 假设有一个方法获取对应舱位的价格

    query.prepare("INSERT INTO wallet_transactions (username, ID_card, transaction_type, amount, transaction_time, flight_number, departure_city, destination_city) "
                  "VALUES (:username, :ID_card, :transaction_type, :amount, :transaction_time, :flight_number, :departure_city, :destination_city)");

    query.bindValue(":username", real_name);
    query.bindValue(":ID_card", id_card);
    query.bindValue(":transaction_type", now_price < price ? "Change_add" : "Change_sub");
    query.bindValue(":amount", qAbs(now_price - price));
    query.bindValue(":transaction_time", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")); // 格式化日期时间字符串
    query.bindValue(":flight_number", data.flight_number);
    query.bindValue(":departure_city", data.departure_city);
    query.bindValue(":destination_city", data.arrival_city);

    if (!query.exec()) {
        qDebug() << "Failed to update wallet transaction:" << query.lastError().text();
        return false;
    }


    query.prepare("UPDATE users SET balance = balance + :price WHERE ID_card =:id_card");
    query.bindValue(":price",price-now_price);
    query.bindValue(":id_card",id_card);
    if (!query.exec()) {
        qDebug() << "Failed to update wallet transaction:" << query.lastError().text();
        return false;
    }

    return true;
}

int change_flightinfo::getPrice(const QString &type) {
    if (type == "economy") return data.economy_price;
    else if (type == "business") return data.business_price;
    else return data.first_class_price;
}
