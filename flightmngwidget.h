#ifndef FLIGHTMNGWIDGET_H
#define FLIGHTMNGWIDGET_H

#include <QObject>
#include <QWidget>

class FlightmngWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FlightmngWidget(QWidget *parent = nullptr);
    ~FlightmngWidget();
};

#endif // FLIGHTMNGWIDGET_H
