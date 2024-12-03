#include "walletwindow.h"


WalletWindow::WalletWindow(QWidget *parent)
    : QWidget(parent),
    balanceLabel(new QLabel("Balance: $0.00", this)),
    transactionAmountEdit(new QLineEdit(this)),
    depositButton(new QPushButton("Deposit", this)),
    withdrawButton(new QPushButton("Withdraw", this)),
    transactionHistoryTable(new QTableWidget(this))
{
    // 设置交易历史表格属性
    transactionHistoryTable->setColumnCount(3); // 假设有三列
    transactionHistoryTable->setHorizontalHeaderLabels({"Date", "Type", "Amount"}); // 设置表头

    // 设置布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 添加余额标签到布局中
    mainLayout->addWidget(balanceLabel);

    // 创建一个水平布局来放置交易金额输入框和按钮
    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(transactionAmountEdit);
    inputLayout->addWidget(depositButton);
    inputLayout->addWidget(withdrawButton);
    mainLayout->addLayout(inputLayout);

    // 添加交易历史表格到布局中
    mainLayout->addWidget(transactionHistoryTable);

    // 设置窗口的默认布局
    setLayout(mainLayout);
}
