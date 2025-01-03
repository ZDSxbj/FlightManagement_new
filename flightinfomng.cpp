#include "flightinfomng.h"
#include <QDebug>
flightinfomng::flightinfomng(FlightData &data, QWidget *parent)
    : QWidget(parent), data(data)
{

    // 设置主布局
    refundMessage = new QMessageBox(this);
    refundMessage->setIcon(QMessageBox::Warning);
    refundMessage->setWindowTitle("删除确认");
    refundMessage->setText("您确定要进行删除操作吗？");
    refundMessage->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    refundMessage->setDefaultButton(QMessageBox::No);
    refundMessage->setWindowFlags(refundMessage->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    refundMessage->setStyleSheet(
        "QMessageBox {"
        "background-color: #f0f0f0;"
        "font-size: 14px;"
        "}"
        "QMessageBox QLabel{"
        "color: blue;"
        "}"
        "QMessageBox QPushButton{"
        "background-color: #4CAF50;"
        "color: white;"
        "border: none;"
        "padding: 5px 10px;"
        "}"
        );
    mainLayout = new QVBoxLayout(this);
    QFont globalFont;

    globalFont.setPointSize(12);
    this->setFont(globalFont);
    // 创建顶部水平布局
    topLayout = new QHBoxLayout();
    mainLayout->addLayout(topLayout);

    // 创建左侧垂直布局（航空公司、起飞日期、航班编号、飞机型号）
    leftVerticalLayout = new QVBoxLayout();
    topLayout->addLayout(leftVerticalLayout);

    airlineLabel = new QLabel(data.airline);
    airlineLabel->setStyleSheet("font-weight: bold; color: #333; font-size: 16px;");
    leftVerticalLayout->addWidget(airlineLabel);

    // 创建出发时间标签，只显示日期部分
    depatureDataLabel = new QLabel(data.departure_time.date().toString("yyyy-MM-dd")); // 使用 "yyyy-MM-dd" 格式化为 "年-月-日"
    depatureDataLabel->setStyleSheet("color: #333; font-size: 16px;");
    leftVerticalLayout->addWidget(depatureDataLabel);
    flightNumberLabel = new QLabel(data.flight_number);

    leftVerticalLayout->addWidget(flightNumberLabel);

    airplaneModelLabel = new QLabel(data.airplane_model);
    airplaneModelLabel->setStyleSheet("color: #666; font-size: 16px;");
    leftVerticalLayout->addWidget(airplaneModelLabel);

    // 创建出发信息垂直布局（出发城市、出发时间、机场、站楼）
    departureVerticalLayout = new QVBoxLayout();
    topLayout->addLayout(departureVerticalLayout);

    QLabel *depatureCityLabel=new QLabel(data.departure_city);
    depatureCityLabel->setStyleSheet(R"(
        QLabel {
            font-weight: bold; /* 字体加粗 */
            font-size: 16px; /* 字体大小 */
        }
    )");
    departureVerticalLayout->addWidget(depatureCityLabel);
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

    QLabel *arrivalCityLabel=new QLabel(data.arrival_city);
    arrivalCityLabel->setStyleSheet(R"(
        QLabel {
            font-weight: bold; /* 字体加粗 */
            font-size: 16px; /* 字体大小 */
        }
    )");
    arrivalVerticalLayout->addWidget(arrivalCityLabel);
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


    // 创建一个容器部件来容纳详情布局
    QWidget *detailsContainer = new QWidget(this);
    mainLayout->addWidget(detailsContainer);

    detailsLayout = new QVBoxLayout(detailsContainer);
    QHBoxLayout *economyLayout = new QHBoxLayout();

    detailsLayout->addLayout(economyLayout);

    QLabel *economyLabel = new QLabel("经济舱");
    economyLayout->addWidget(economyLabel);

    // 添加座位容量标签
    QLabel *economySeatCapacityLabel = new QLabel("座位容量: " + QString::number(data.economy_seat_capacity));
    economyLayout->addWidget(economySeatCapacityLabel);

    QLabel *economyAvailableSeatsLabel = new QLabel("剩余座位: " + QString::number(data.economy_available_seats));
    economyLayout->addWidget(economyAvailableSeatsLabel);

    QLabel *economyPriceLabel = new QLabel("价格: " + QString::number(data.economy_price));
    economyLayout->addWidget(economyPriceLabel);

    // 商务舱布局
    QHBoxLayout *businessLayout = new QHBoxLayout();
    detailsLayout->addLayout(businessLayout);

    QLabel *businessLabel = new QLabel("商务舱");
    businessLayout->addWidget(businessLabel);

    // 添加座位容量标签
    QLabel *businessSeatCapacityLabel = new QLabel("座位容量: " + QString::number(data.business_seat_capacity));
    businessLayout->addWidget(businessSeatCapacityLabel);

    // 添加剩余座位标签
    QLabel *businessAvailableSeatsLabel = new QLabel("剩余座位: " + QString::number(data.business_available_seats));
    businessLayout->addWidget(businessAvailableSeatsLabel);

    // 添加价格标签
    QLabel *businessPriceLabel = new QLabel("价格: " + QString::number(data.business_price));
    businessLayout->addWidget(businessPriceLabel);


    // 头等舱布局
    QHBoxLayout *firstClassLayout = new QHBoxLayout();
    detailsLayout->addLayout(firstClassLayout);

    QLabel *firstClassLabel = new QLabel("头等舱");
    firstClassLayout->addWidget(firstClassLabel);

    // 添加座位容量标签
    QLabel *firstClassSeatCapacityLabel = new QLabel("座位容量: " + QString::number(data.first_class_seat_capacity));
    firstClassLayout->addWidget(firstClassSeatCapacityLabel);

    // 添加剩余座位标签
    QLabel *firstClassAvailableSeatsLabel = new QLabel("剩余座位: " + QString::number(data.first_class_available_seats));
    firstClassLayout->addWidget(firstClassAvailableSeatsLabel);


    // 添加价格标签
    QLabel *firstClassPriceLabel = new QLabel("价格: " + QString::number(data.first_class_price));
    firstClassLayout->addWidget(firstClassPriceLabel);


    // 创建底部水平布局，用于放置按钮
    buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch(); // 添加伸缩空间以使按钮靠右

    //创建修改时间button
    editTimeButton = new QPushButton("修改时间");
    buttonLayout->addWidget(editTimeButton);

    // 创建“取消航班”按钮
    cancelFlightButton = new QPushButton("取消航班");

    buttonLayout->addWidget(cancelFlightButton);

    // 设置 "修改时间" 按钮样式
    editTimeButton->setStyleSheet(
        "QPushButton {"
        "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #7F7EFF, stop:1 #9E8CFE);" // 渐变紫色背景
        "    color: white;" // 字体颜色为白色
        "    border-radius: 10px;" // 圆角按钮
        "    font-size: 14px;" // 字体大小
        "    font-weight: bold;" // 字体加粗
        "    padding: 5px 10px;" // 内边距
        "    width: 100px;" // 按钮宽度
        "    border: none;" // 无边框
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #9E8CFE, stop:1 #BCA4FF);" // 悬停时更亮的渐变色
        "}"
        "QPushButton:pressed {"
        "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #6D6CFF, stop:1 #8E7AFE);" // 按下时更深的渐变色
        "}"
        );

    connect(editTimeButton, &QPushButton::clicked, this, &flightinfomng::onEditTimeButtonClicked); //修改时间槽函数
    // 设置 "取消航班" 按钮样式
    cancelFlightButton->setStyleSheet(
        "QPushButton {"
        "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FFA07A, stop:1 #FF7F7F);" // 渐变浅红色背景
        "    color: white;" // 字体颜色为白色
        "    border-radius: 10px;" // 圆角按钮
        "    font-size: 14px;" // 字体大小
        "    font-weight: bold;" // 字体加粗
        "    padding: 5px 10px;" // 内边距
        "    width: 100px;" // 按钮宽度
        "    border: none;" // 无边框
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FF7F7F, stop:1 #FF6F6F);" // 悬停时更亮的浅红色
        "}"
        "QPushButton:pressed {"
        "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FF6F6F, stop:1 #FF5F5F);" // 按下时更深的红色
        "}"
        );
    connect(cancelFlightButton,&QPushButton::clicked,this,&flightinfomng::onclickedcancel);
    // 将按钮水平布局添加到主竖直布局的最下方
    mainLayout->addLayout(buttonLayout);
}
void flightinfomng::onclickedcancel()
{
    if(refundMessage->exec()==QMessageBox::No)
    {
        return;
    }
    const QString connectionName = "flight_cancellation_db";

    // 如果连接已经存在，则重用它；否则创建新的连接
    QSqlDatabase dbc;
    if (QSqlDatabase::contains(connectionName)) {
        dbc = QSqlDatabase::database(connectionName);
    } else {


        dbc = QSqlDatabase::addDatabase("QODBC", connectionName);
        dbc.setHostName("127.0.0.1");
        dbc.setPort(3306);
        dbc.setDatabaseName("Local instance MySQL8");
        dbc.setUserName("root");  // 添加用户名
        dbc.setPassword("ZXJsnd4697");  // 添加密码

    }


    if (!dbc.open()) {
        qDebug() << "Error, 数据库文件打开失败！" << dbc.lastError().text();
        return;
    }

    qDebug() << "Success, 数据库文件打开成功！";

    if (!dbc.transaction()) {
        qDebug() << "Failed to start transaction:" << dbc.lastError().text();
        dbc.close();
        QSqlDatabase::removeDatabase(connectionName);
        return;
    }

    QSqlQuery query(dbc);

    // 删除航班记录
    query.prepare("DELETE FROM flights WHERE flight_number=:flight_number AND departure_time=:departure_time");
    query.bindValue(":flight_number", data.flight_number);
    query.bindValue(":departure_time", data.departure_time);
    if (!query.exec()) {
        qDebug() << "Failed to execute delete order query:" << query.lastError().text();
        dbc.rollback();
        dbc.close();
        QSqlDatabase::removeDatabase(connectionName);
        return;
    }

    // 查询与该航班相关的订单
    query.prepare("SELECT realname, price FROM orders WHERE flight_number=:flight_number AND departure_time=:departure_time");
    query.bindValue(":flight_number", data.flight_number);
    query.bindValue(":departure_time", data.departure_time);
    if (!query.exec()) {
        qDebug() << "Failed to select orders:" << query.lastError().text();
        dbc.rollback();
        dbc.close();
        QSqlDatabase::removeDatabase(connectionName);
        return;
    }

    while (query.next()) {
        QString name = query.value(0).toString();
        int price = query.value(1).toInt();

        QSqlQuery queryy(dbc);

        // 获取用户的 ID 卡号
        queryy.prepare("SELECT ID_card FROM users WHERE username=:username");
        queryy.bindValue(":username", name);
        if (!queryy.exec() || !queryy.next()) {
            qDebug() << "Failed to get user ID card or no such user:" << queryy.lastError().text();
            dbc.rollback();
            dbc.close();
            QSqlDatabase::removeDatabase(connectionName);
            return;
        }
        QString id_card = queryy.value(0).toString();

        // 更新用户余额
        queryy.prepare("UPDATE users SET balance = balance + :price WHERE ID_card = :id_card");
        queryy.bindValue(":price", price);
        queryy.bindValue(":id_card", id_card);
        if (!queryy.exec()) {
            qDebug() << "Failed to update wallet transaction:" << queryy.lastError().text();
            dbc.rollback();
            dbc.close();
            QSqlDatabase::removeDatabase(connectionName);
            return;
        }

        // 插入钱包交易记录
        queryy.prepare(
            "INSERT INTO wallet_transactions (username, ID_card, transaction_type, amount, transaction_time, flight_number) "
            "VALUES (:username, :ID_card, :transaction_type, :amount, :transaction_time, :flight_number)"
            );
        queryy.bindValue(":username", name);
        queryy.bindValue(":ID_card", id_card);
        queryy.bindValue(":transaction_type", "Cancelled");
        queryy.bindValue(":amount", price);
        queryy.bindValue(":transaction_time", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        queryy.bindValue(":flight_number", data.flight_number);

        if (!queryy.exec()) {
            qDebug() << "Failed to insert wallet transaction:" << queryy.lastError().text();
            dbc.rollback();
            dbc.close();
            QSqlDatabase::removeDatabase(connectionName);
            return;
        }

        // 插入通知记录
        queryy.prepare(
            "INSERT INTO notice (username, ID_card, flight_number, departure_time, state, notice_time) "
            "VALUES (:username, :ID_card, :flight_number, :departure_time, :state, :notice_time)"
            );
        queryy.bindValue(":username", name);
        queryy.bindValue(":ID_card", id_card);
        queryy.bindValue(":flight_number", data.flight_number);
        queryy.bindValue(":departure_time", data.departure_time);
        queryy.bindValue(":state", "Cancelled");
        queryy.bindValue(":notice_time", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

        if (!queryy.exec()) {
            qDebug() << "Failed to insert notice:" << queryy.lastError().text();
            dbc.rollback();
            dbc.close();
            QSqlDatabase::removeDatabase(connectionName);
            return;
        }
    }

    // 删除订单记录
    query.prepare("DELETE FROM orders WHERE flight_number=:flight_number AND departure_time=:departure_time");
    query.bindValue(":flight_number", data.flight_number);
    query.bindValue(":departure_time", data.departure_time);
    if (!query.exec()) {
        qDebug() << "Failed to delete orders:" << query.lastError().text();
        dbc.rollback();
        dbc.close();
        QSqlDatabase::removeDatabase(connectionName);
        return;
    }

    if (dbc.commit()) {
        qDebug() << "All operations completed successfully.";
    } else {
        qDebug() << "Failed to commit transaction:" << dbc.lastError().text();
        dbc.rollback();
    }

    dbc.close();
    QSqlDatabase::removeDatabase(connectionName);
    emit iscanceled(data);


}
