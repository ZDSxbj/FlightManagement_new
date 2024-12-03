#include "completedordersw.h"


CompletedOrdersW::CompletedOrdersW(QWidget *parent)
    : QWidget(parent), ordersTable(new QTableWidget(this)), refreshButton(new QPushButton("Refresh", this))
{
    // 设置表格属性
    ordersTable->setColumnCount(4); // 假设有四列
    ordersTable->setHorizontalHeaderLabels({"Order ID", "Customer", "Date", "Total"}); // 设置表头

    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 添加订单表格到布局中
    layout->addWidget(ordersTable);

    // 添加刷新按钮到布局中
    layout->addWidget(refreshButton);

    // 设置窗口的默认布局
    setLayout(layout);
}
