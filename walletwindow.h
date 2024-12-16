#ifndef WALLETWINDOW_H
#define WALLETWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>  // 添加QTextEdit头文件
#include <QDialog>    // 添加QDialog头文件
#include "someGlobal.h"
class WalletWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WalletWindow(QWidget *parent = nullptr);
    ~WalletWindow();

private slots:
    void onRecharge();         // 充值
    void onWithdraw();         // 提现
    void onViewBillClicked();  // 查看账单明细

private:
    void loadBalance();              // 从数据库加载余额
    void updateBalanceInDatabase();  // 更新余额到数据库

    QLabel *walletIconLabel;         // 钱包图标
    QLabel *balanceLabel;            // 余额显示
    QPushButton *rechargeButton;     // 充值按钮
    QPushButton *withdrawButton;     // 提现按钮
    QLabel *viewBillLabel;           // 账单明细文字标签
    QString buttonStyle; // 按钮样式
    double balance;                  // 当前余额
};

#endif // WALLETWINDOW_H
