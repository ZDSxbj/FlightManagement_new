#ifndef FLIGHTDATA_H
#define FLIGHTDATA_H

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

struct FlightData {
    int flight_id;
    QString flight_number;
    QString airline;
    QString airplane_model;
    QString departure_city;
    QString departure_airport;
    QString arrival_city;
    QString arrival_airport;
    QString departure_terminal;
    QString arrival_terminal;
    QDateTime departure_time;
    QDateTime arrival_time;
    QTime duration;
    bool same_day_arrival;
    QString status;
    int economy_seat_capacity;
    int economy_available_seats;
    double economy_price;
    int business_seat_capacity;
    int business_available_seats;
    double business_price;
    int first_class_seat_capacity;
    int first_class_available_seats;
    double first_class_price;
    QString refund_policy;
    QString baggage_policy;

    bool operator==(const FlightData& other) const {
        return flight_number == other.flight_number && departure_time == other.departure_time;
    }
};

#endif // FLIGHTDATA_H
