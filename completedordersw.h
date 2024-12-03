#ifndef COMPLETEDORDERSW_H
#define COMPLETEDORDERSW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>

class CompletedOrdersW : public QWidget {
    // Q_OBJECT
public:
    CompletedOrdersW(QWidget *parent = nullptr);
    ~CompletedOrdersW(){};
private:
    QTableWidget *ordersTable; // 用于显示已完成订单的表格
    QPushButton *refreshButton; // 刷新按钮
};

#endif // COMPLETEDORDERSW_H
