#include "Changed.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>

// 假设 FlightData 和 flightinfo 类已定义

Changed::Changed(QWidget *parent,
                 const QString &departure,
                 const QString &arrival,
                 const QString& realname,
                 const QDateTime &departure_date_param,
                 const QString& fli_number,
                 const QString& fli_class,
                 const double& cost,
                 const QString& card)
    : QWidget(parent),
    id_card(card),
    real_name(realname),
    depart(departure),
    arriva(arrival),
    departure_date(departure_date_param), // 使用不同的参数名以避免混淆
    fli_number(fli_number),
    fli_class(fli_class),
    cost(cost),
    datePicker(new QDateEdit(QDate::currentDate(), this)) {

    contentLayout = new QVBoxLayout(this);

    QGridLayout *queryLayout = new QGridLayout();
    queryLayout->addWidget(new QLabel("选择新起飞时间:"), 0, 0);

    datePicker->setDisplayFormat("yyyy-MM-dd HH:mm");
    datePicker->setCalendarPopup(true);

    queryLayout->addWidget(datePicker, 0, 1);

    QPushButton *confirmButton = new QPushButton("查询可用航班");
    queryLayout->addWidget(confirmButton, 0, 2);
    connect(confirmButton, &QPushButton::clicked, this, &Changed::searchFlights);

    contentLayout->addLayout(queryLayout);

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollContentWidget = new QWidget(scrollArea);
    scrollContentLayout = new QVBoxLayout(scrollContentWidget);
    scrollArea->setWidget(scrollContentWidget);
    contentLayout->addWidget(scrollArea);

    contentLayout->setContentsMargins(10, 10, 10, 10);
    queryLayout->setSpacing(5);
}

void Changed::clearFlightResults() {
    flightInfoWidgets.clear();

    QLayoutItem *item;
    while ((item = scrollContentLayout->takeAt(0)) != nullptr) {
        delete item->widget(); // 删除部件
        delete item;           // 删除布局项
    }
}

void Changed::searchFlights() {
    qDebug() << "正确进入函数";

    QDate selectedDate = datePicker->date();

    QSqlQuery query;
    query.prepare("SELECT flight_number, airline, airplane_model, "
                  "departure_city, departure_airport, arrival_city, arrival_airport, "
                  "departure_terminal, arrival_terminal, departure_time, arrival_time, "
                  "duration, same_day_arrival, status, economy_seat_capacity, "
                  "economy_available_seats, economy_price, business_seat_capacity, "
                  "business_available_seats, business_price, first_class_seat_capacity, "
                  "first_class_available_seats, first_class_price, refund_policy, baggage_policy "
                  "FROM flights WHERE DATE(departure_time) = :date AND "
                  "departure_city = :departure_city AND arrival_city = :arrival_city");

    query.bindValue(":date", selectedDate.toString("yyyy-MM-dd"));
    query.bindValue(":departure_city", depart); // 假设 depart 成员变量保存了出发城市
    query.bindValue(":arrival_city", arriva);   // 假设 arriva 成员变量保存了到达城市

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        QMessageBox::critical(this, "错误", "数据库查询失败，请稍后再试。");
        return;
    }

    clearFlightResults();

    while (query.next()) {
        FlightData data;
        data.flight_number = query.value("flight_number").toString();
        data.airline = query.value("airline").toString();
        data.airplane_model = query.value("airplane_model").toString();
        data.departure_city = query.value("departure_city").toString();
        data.departure_airport = query.value("departure_airport").toString();
        data.arrival_city = query.value("arrival_city").toString();
        data.arrival_airport = query.value("arrival_airport").toString();
        data.departure_terminal = query.value("departure_terminal").toString();
        data.arrival_terminal = query.value("arrival_terminal").toString();
        data.departure_time = query.value("departure_time").toDateTime();
        data.arrival_time = query.value("arrival_time").toDateTime();
        data.duration = query.value("duration").toTime();
        data.same_day_arrival = query.value("same_day_arrival").toBool();
        data.status = query.value("status").toString();
        data.economy_seat_capacity = query.value("economy_seat_capacity").toInt();
        data.economy_available_seats = query.value("economy_available_seats").toInt();
        data.economy_price = query.value("economy_price").toDouble();
        data.business_seat_capacity = query.value("business_seat_capacity").toInt();
        data.business_available_seats = query.value("business_available_seats").toInt();
        data.business_price = query.value("business_price").toDouble();
        data.first_class_seat_capacity = query.value("first_class_seat_capacity").toInt();
        data.first_class_available_seats = query.value("first_class_available_seats").toInt();
        data.first_class_price = query.value("first_class_price").toDouble();
        data.refund_policy = query.value("refund_policy").toString();
        data.baggage_policy = query.value("baggage_policy").toString();

        if (data.economy_available_seats > 0 ||
            data.business_available_seats > 0 ||
            data.first_class_available_seats > 0) {
            change_flightinfo *newFlightInfo = new change_flightinfo(data,real_name,fli_number,fli_class,departure_date,cost,id_card,this);
            connect(newFlightInfo,&change_flightinfo::completed,this,&Changed::handlecompleted);
            flightInfoWidgets.append(newFlightInfo);
            qDebug() << "Added new flightinfo instance for flight:" << data.flight_number;
        } else {
            qDebug() << "Skipped flight:" << data.flight_number << "due to no available seats.";
        }
    }

    if (flightInfoWidgets.size() == 0) {
        QMessageBox::information(this, "提示", "对不起，未找到符合条件的记录。");
    } else {
        printFlightInfos();
    }
}

void Changed::printFlightInfos() {
    QVector<change_flightinfo*> sortedFlightInfoWidgets = flightInfoWidgets;

    std::sort(sortedFlightInfoWidgets.begin(), sortedFlightInfoWidgets.end(), Changed:: compareByEconomyPrice);

    scrollContentLayout->setSpacing(10);

    if (QVBoxLayout* vboxLayout = dynamic_cast<QVBoxLayout*>(scrollContentLayout)) {
        vboxLayout->setAlignment(Qt::AlignTop);
    }

    for (const auto& flightInfo : sortedFlightInfoWidgets) {
        flightInfo->update();
        scrollContentLayout->addWidget(flightInfo);
    }

    scrollContentLayout->update();
}

void Changed::handlecompleted()
{
    emit complete();
    this->close();
}
