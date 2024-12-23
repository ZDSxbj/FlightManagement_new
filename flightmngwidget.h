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
#include "flightinfomng.h"
#include "FlightData.h"
#include "addflightwidget.h"
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
    void hideAddressListIfApplicable(QLineEdit *input);  //隐藏
    /// @brief 当用户点击确认按钮时调用此槽函数，根据输入筛选航班信息并更新滚动区域。
    void onConfirmButtonClicked();
    void handlecancel(const FlightData& data);
    /// @brief 从数据库加载所有航班信息到 allFlights 成员变量中。
    void loadFlightsFromDatabase();

    /// @brief 将所有航班信息添加到滚动页面上。
    void populateScrollAreaWithFlights();

    //展示添加增加航班页面
    void showAddFlightWidget();

    //新增航班后刷新数组和页面
    void refreshFlightList();
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

    QList<flightinfomng*> flightInfoWidgets; // 存储所有航班信息部件的列表
    QVector<FlightData> allFlights; // 存储从数据库加载的所有航班信息
    /// @brief 按照出发时间递增排序 allFlights 成员变量。
    void sortFlightsByDepartureTime();
};

#endif // FLIGHTMNGWIDGET_H
