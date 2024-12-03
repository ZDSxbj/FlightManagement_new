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
class MyEventFilter : public QObject {
    Q_OBJECT
signals:
    void clicked();
public:
    explicit MyEventFilter(QObject *parent = nullptr) : QObject(parent) {}

protected:
    bool eventFilter(QObject *obj, QEvent *event) override{
        if (event->type() == QEvent::MouseButtonPress) {
            emit clicked();
            return true; // 捕获了事件，不再传递给其他对象
        }
        return QObject::eventFilter(obj, event); // 默认处理方式
    }
};

class HomeWidget : public QWidget {
    Q_OBJECT

public:
    explicit HomeWidget(QWidget *parent = nullptr);

private slots:
    void toggleAddressListVisibility(QLineEdit *input, QListWidget *list);
    void setAddressFromList(QLineEdit *input, QListWidget *list, QListWidgetItem *item);
    void swapDepartureAndDestination();

private:
    QLineEdit *departureInput;
    QLineEdit *destinationInput;
    QListWidget *addressListOpt;
    QListWidget *addressListOpt2;
    QDateEdit *datePicker;
    QVBoxLayout *contentLayout;
    QScrollArea *scrollArea;
    QWidget *scrollContentWidget;
    QVBoxLayout *scrollContentLayout;

    MyEventFilter *filter;
    MyEventFilter *filter2;

    QVector<flightinfo*> flightInfoWidgets; // 存储flightinfo对象的指针
    // QSqlDatabase dbcon; //数据库
    void searchFlights();
    void clearFlightResults();
    void printFlightInfos();  //添加航班页面在滚动区域
};

#endif // HOMEWIDGET_H
