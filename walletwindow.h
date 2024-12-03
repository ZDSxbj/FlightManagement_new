#ifndef WALLETWINDOW_H
#define WALLETWINDOW_H

#include <QMainWindow>
#include <QWidget>

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>

class WalletWindow : public QWidget {
    Q_OBJECT
public:
   WalletWindow(QWidget *parent = nullptr);
    ~WalletWindow(){}
private:
    QLabel *balanceLabel; // 显示余额的标签
    QLineEdit *transactionAmountEdit; // 输入交易金额的文本框
    QPushButton *depositButton; // 存款按钮
    QPushButton *withdrawButton; // 取款按钮
    QTableWidget *transactionHistoryTable; // 交易历史表格
};

#endif // WALLETWINDOW_H
