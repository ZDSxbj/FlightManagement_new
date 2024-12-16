#ifndef CHANGED_H
#define CHANGED_H


#include <QWidget>
#include <QCompleter>
#include <QListWidget>
#include <QLineEdit>
#include <QDateTimeEdit>
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
#include"change_flightinfo.h"
class Changed : public QWidget
{
    Q_OBJECT
public:
    explicit Changed(QWidget *parent,
                     const QString &departure,
                     const QString &arrival,
                     const QString& realname,
                     const QDateTime &departure_date,
                     const QString& fli_number,
                     const QString& fli_class,
                     const double& cost,
                     const QString& card);
    //Changed *change = new Changed(nullptr,departure_city,arrival_city,name,departure_Date,fli_number,fli_class,cost,id_card);
private:
    double cost;
    QLineEdit *departureInput;
    QLineEdit *destinationInput;
    QListWidget *addressListOpt;
    QListWidget *addressListOpt2;
    QDateTimeEdit *datePicker;
    QVBoxLayout *contentLayout;
    QScrollArea *scrollArea;
    QWidget *scrollContentWidget;
    QVBoxLayout *scrollContentLayout;

    // 成员变量声明按照构造函数初始化列表中的顺序排列
    QString id_card;
    QString real_name;
    QString depart;
    QString arriva;
    QDateTime departure_date; // 改名以避免与参数冲突
    QString fli_number;
    QString fli_class;

    QVector<change_flightinfo*> flightInfoWidgets;
    // QSqlDatabase dbcon; //数据库
    void searchFlights();
    void clearFlightResults();
    void printFlightInfos();  //添加航班页面在滚动区域
    static bool compareByEconomyPrice(const change_flightinfo* lhs, const change_flightinfo* rhs) {
        return lhs->getPrice() < rhs->getPrice();
    }
signals:
    void complete();
private slots:
    void handlecompleted();
};

#endif // CHANGED_H
