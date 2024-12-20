#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

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
#include"flightinfo.h"
#include "someGlobal.h"
#include "MyEventFilter.h"
class HomeWidget : public QWidget {
    Q_OBJECT

public:
    explicit HomeWidget(QWidget *parent = nullptr);

private slots:
    void toggleAddressListVisibility(QLineEdit *input, QListWidget *list);
    void setAddressFromList(QLineEdit *input, QListWidget *list, QListWidgetItem *item);
    void swapDepartureAndDestination();
    void searchFlights();
    void checkAndSearchFlights();  // 新增的槽函数，检查 isPay 并调用 searchFlights
    void refresh();
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

    QVector<flightinfo*> flightInfoWidgets; // 存储flightinfo对象的指针
    QListWidget *addressListOpt;
    QListWidget *addressListOpt2;
    QTimer *payCheckTimer;    // 定时器，用于检查 isPay 状态
    void clearFlightResults();
    void printFlightInfos();  //添加航班页面在滚动区域
};

#endif // HOMEWIDGET_H
