#ifndef FLIGHTMNGWIDGET_H
#define FLIGHTMNGWIDGET_H

#include <QObject>
#include <QWidget>
#include <QWidget>
#include <QCompleter>
#include <QListWidget>
#include <QLineEdit>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QLabel>
#include <QObject>  // 添加这一行以包含 QObject
#include<QEvent>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include<QSqlQuery>
#include <QMessageBox> // 引入 QMessageBox
#include "MyEventFilter.h"
class FlightmngWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FlightmngWidget(QWidget *parent = nullptr);
    ~FlightmngWidget();
private slots:
    void toggleAddressListVisibility(QLineEdit *input, QListWidget *list);
    void setAddressFromList(QLineEdit *input, QListWidget *list, QListWidgetItem *item);
    void swapDepartureAndDestination();

    // void checkAndSearchFlights();  // 新增的槽函数，检查 isPay 并调用 searchFlights

    void hideAddressListIfApplicable(QLineEdit *input);  //隐藏
private:
    QLineEdit *departureInput;
    QLineEdit *destinationInput;

    QDateEdit *datePicker;
    QVBoxLayout *contentLayout;
    QScrollArea *scrollArea;
    QWidget *scrollContentWidget;
    QVBoxLayout *scrollContentLayout;

    MyEventFilter *filter;
    MyEventFilter *filter2;
    QPushButton *addFlightButton;
    QListWidget *addressListOpt;
    QListWidget *addressListOpt2;
};

#endif // FLIGHTMNGWIDGET_H
