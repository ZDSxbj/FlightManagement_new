#ifndef UNCOMPLETEDORDERSW_H
#define UNCOMPLETEDORDERSW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>

class UncompletedOrdersW : public QWidget {
    Q_OBJECT
public:
    UncompletedOrdersW(QWidget *parent = nullptr);
    ~UncompletedOrdersW(){}
private:
    QTableWidget *ordersTable; // 用于显示未完成订单的表格
    QPushButton *refreshButton; // 刷新按钮
};

#endif // UNCOMPLETEDORDERSW_H
