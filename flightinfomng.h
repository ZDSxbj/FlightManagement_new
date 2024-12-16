#ifndef FLIGHTINFOMNG_H
#define FLIGHTINFOMNG_H

#include <QObject>
#include <QWidget>
#include "FlightData.h"
class flightinfomng : public QWidget
{
    Q_OBJECT
public:
    explicit flightinfomng(const FlightData &data, QWidget *parent);

signals:

private:
    FlightData data;  // 航班数据
    QVBoxLayout *mainLayout;  // 主垂直布局
    QHBoxLayout *topLayout;  // 顶部水平布局
    QVBoxLayout *leftVerticalLayout;  // 左侧垂直布局
    QVBoxLayout *departureVerticalLayout;  // 出发信息垂直布局
    QVBoxLayout *arrivalVerticalLayout;  // 到达信息垂直布局
    QVBoxLayout *durationVerticalLayout;  // 历时信息垂直布局
    QVBoxLayout *detailsLayout;  // 详情布局

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
    QLabel *economySeatCapacityLabel;
    QLabel *economyAvailableSeatsLabel;
    QLabel *economyPriceLabel;
    QLabel *businessSeatCapacityLabel;
    QLabel *businessAvailableSeatsLabel;
    QLabel *businessPriceLabel;
    QLabel *firstClassSeatCapacityLabel;
    QLabel *firstClassAvailableSeatsLabel;
    QLabel *firstClassPriceLabel;

};

#endif // FLIGHTINFOMNG_H
