#ifndef TICKETS_H
#define TICKETS_H
#include <QDateTime>
#include <QSqlQuery>
#include <QWidget>
#include<QVBoxLayout>
#include<QFrame>
#include<QPushButton>
#include<QLabel>
#include<QScrollArea>
#include<QTimer>
#include"Indent_detail.h"
class Tickets : public QWidget
{
    Q_OBJECT
public:
    explicit Tickets(const QString & name,QWidget *parent = nullptr);
    void createContentArea();
    void queryINFO();
    void createMainLayout();
    void refresh();
    QPushButton *createButton(const QString &text) {
        QPushButton *button = new QPushButton(text, this);
        button->setStyleSheet("background-color: #4a90e2; color: white; padding: 10px; margin: 5px;");
        return button;
    }
    QWidget *contentWidget=nullptr; // 中间内容区域的小部件
    QVBoxLayout *mainLayout;
    QString name;
    QTimer *payCheckTimer;
    std::vector<Indent_detail*> q;//订单的窗口
private slots:
    void checkAndSearchFlights();
signals:
};

#endif // TICKETS_H
