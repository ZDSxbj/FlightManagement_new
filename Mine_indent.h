#ifndef MINE_INDENT_H
#define MINE_INDENT_H

#include <QWidget>
#include<QVBoxLayout>
#include<QFrame>
#include<QPushButton>
#include<QLabel>
#include<QScrollArea>
#include"Indent_detail.h"
#include<QTimer>
class Mine_indent : public QWidget
{
    Q_OBJECT
public:
    explicit Mine_indent(const QString & id_card,const bool &ustatus,QWidget *parent = nullptr);
private:

    void createContentArea();
    void queryINFO();
    void createMainLayout();
    void refresh();
    QPushButton *createButton(const QString &text) {
        QPushButton *button = new QPushButton(text, this);
        button->setStyleSheet("background-color: #4a90e2; color: white; padding: 10px; margin: 5px;");
        return button;
    }
    //  static  bool compareByDepartureDate(const Indent_detail* a, const Indent_detail* b);
    QWidget *contentWidget=nullptr; // 中间内容区域的小部件
    QVBoxLayout *mainLayout;
    QString card;//根据用户名来查询订单信息。
    bool status;
    QTimer *payCheckTimer;
    std::vector<Indent_detail*> q;//订单的窗口
private slots:
    void handledeleteRequest(const QString& name,const QString& plane,const int &uclass,const QDateTime& time,const double& price,const QString& id_card);
    void handlecomplete();
    void checkAndSearchFlights();
};

#endif // MINE_INDENT_H
