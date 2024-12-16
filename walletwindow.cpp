#include "walletwindow.h"
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QTimer>
#include <QLabel>
#include <QTextBrowser>
#include <QPushButton>

WalletWindow::WalletWindow(QWidget *parent) : QWidget(parent), balance(0.0)
{
    // 设置窗口样式
    this->setStyleSheet(
        "QWidget { background-color: #f5f7fa; border-radius: 10px; border: 1px solid #e0e0e0; }");

    QVBoxLayout *mainLayout = new QVBoxLayout;

    // 钱包图标
    walletIconLabel = new QLabel(this);
    walletIconLabel->setFixedSize(120, 120);

    walletIconLabel->setAlignment(Qt::AlignCenter);
    walletIconLabel->setPixmap(QPixmap("D:/Qtproj/wallet.png").scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // 余额显示
    balanceLabel = new QLabel(QString("余额: %1 元").arg(balance, 0, 'f', 2), this);
    balanceLabel->setStyleSheet(
        "font-size: 24px; font-weight: bold; color: #333333;");
    balanceLabel->setAlignment(Qt::AlignCenter);

    // 充值和提现按钮
    rechargeButton = new QPushButton("充值", this);
    withdrawButton = new QPushButton("提现", this);

    // 按钮样式
    QString buttonStyle =
        "QPushButton {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #7F7EFF, stop:1 #9E8CFE);" // 渐变紫色背景
        "color: white;" // 字体颜色为白色
        "border-radius: 20px;" // 圆角按钮
        "font-size: 18px;" // 增大字体
        "font-weight: bold;" // 字体加粗
        "padding: 10px 20px;" // 增加内边距
        "min-width: 120px;" // 按钮最小宽度
        "border: none;" // 去除边框
        "}"
        "QPushButton:hover {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #9E8CFE, stop:1 #BCA4FF);" // 悬停时更亮的渐变色
        "}"
        "QPushButton:pressed {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #6D6CFF, stop:1 #8E7AFE);" // 按下时更深的渐变色
        "}";

    rechargeButton->setStyleSheet(buttonStyle);
    withdrawButton->setStyleSheet(buttonStyle);

    // 按钮布局
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    // 创建可伸缩的间隔项
    QSpacerItem* spacerBeforeButtons = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* spacerBetweenButtons = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* spacerAfterButtons = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    // 在第一个按钮之前添加可伸缩的间隔
    buttonLayout->addSpacerItem(spacerBeforeButtons);

    // 添加充值按钮
    buttonLayout->addWidget(rechargeButton);

    // 在两个按钮之间添加可伸缩的间隔
    buttonLayout->addSpacerItem(spacerBetweenButtons);

    // 添加提现按钮
    buttonLayout->addWidget(withdrawButton);

    // 在最后一个按钮之后添加可伸缩的间隔
    buttonLayout->addSpacerItem(spacerAfterButtons);
    // 添加查看账单明细文字
    viewBillLabel = new QLabel("<a href='#'>点击查看账单明细 >></a>", this);
    viewBillLabel->setStyleSheet("font-size: 14px; color: #007BFF;");
    viewBillLabel->setAlignment(Qt::AlignCenter);
    viewBillLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);

    // 连接点击事件
    connect(viewBillLabel, &QLabel::linkActivated, this, &WalletWindow::onViewBillClicked);

    // 组合布局
    mainLayout->addWidget(walletIconLabel, 0, Qt::AlignCenter);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(balanceLabel, 0, Qt::AlignCenter);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(viewBillLabel, 0, Qt::AlignCenter);
    mainLayout->addStretch();

    setLayout(mainLayout);

    // 初始化余额
    loadBalance();

    // 信号槽连接
    connect(rechargeButton, &QPushButton::clicked, this, &WalletWindow::onRecharge);
    connect(withdrawButton, &QPushButton::clicked, this, &WalletWindow::onWithdraw);

    // 定时器，用于实时更新余额
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &WalletWindow::loadBalance);
    timer->start(1000); // 每隔 5 秒刷新一次
}

WalletWindow::~WalletWindow() {}

void WalletWindow::loadBalance()
{
    QSqlQuery query;
    query.prepare("SELECT balance FROM users WHERE ID_card = :idCard");
    query.bindValue(":idCard", curUser);  // 使用指定的 ID_card

    if (query.exec() && query.next()) {
        balance = query.value(0).toDouble();
        balanceLabel->setText(QString("余额: %1 元").arg(balance, 0, 'f', 2));
    } else {
        qDebug() << "无法加载用户余额：" << query.lastError().text();
    }
}

void WalletWindow::updateBalanceInDatabase()
{
    QSqlQuery query;
    query.prepare("UPDATE users SET balance = :balance WHERE ID_card = :idCard");
    query.bindValue(":balance", balance);
    query.bindValue(":idCard", curUser);  // 使用指定的 ID_card

    if (!query.exec()) {
        QMessageBox::warning(this, "更新失败", "无法更新余额：" + query.lastError().text());
    }
}



void WalletWindow::onRecharge()
{
    bool ok;
    double amount = QInputDialog::getDouble(this, "充值", "请输入充值金额:", 0, 0, 10000, 2, &ok);
    if (ok && amount > 0) {
        // 弹出输入密码的对话框
        bool passwordOk;
        QString password = QInputDialog::getText(this, "密码验证", "请输入密码:", QLineEdit::Password, "", &passwordOk);

        if (passwordOk && !password.isEmpty()) {
            // 验证密码
            QSqlQuery query;
            query.prepare("SELECT password FROM users WHERE ID_card = :idCard");
            query.bindValue(":idCard", curUser);  // 使用指定的 ID_card

            if (query.exec() && query.next()) {
                QString correctPassword = query.value(0).toString();
                if (password == correctPassword) {
                    // 密码正确，执行充值操作
                    query.prepare("SELECT ID_card FROM users WHERE ID_card = :idCard");
                    query.bindValue(":idCard", curUser);

                    if (query.exec() && query.next()) {
                        QString idCard = query.value(0).toString(); // 获取 ID_card

                        query.prepare("INSERT INTO wallet_transactions (username, ID_card, transaction_type, amount) "
                                      "VALUES (:username, :idCard, 'Recharge', :amount)");
                        query.bindValue(":username", "user1");
                        query.bindValue(":idCard", idCard); // 插入 ID_card
                        query.bindValue(":amount", amount);

                        if (query.exec()) {
                            balance += amount;
                            balanceLabel->setText(QString("余额: %1 元").arg(balance, 0, 'f', 2));
                            updateBalanceInDatabase();
                        } else {
                            QMessageBox::warning(this, "充值失败", "无法记录充值记录：" + query.lastError().text());
                        }
                    } else {
                        QMessageBox::warning(this, "获取 ID 失败", "无法获取用户的 ID_card：" + query.lastError().text());
                    }
                } else {
                    QMessageBox::warning(this, "密码错误", "密码输入错误！");
                }
            } else {
                QMessageBox::warning(this, "查询失败", "无法验证密码：" + query.lastError().text());
            }
        }
    }
}

void WalletWindow::onWithdraw()
{
    bool ok;
    double amount = QInputDialog::getDouble(this, "提现", "请输入提现金额:", 0, 0, balance, 2, &ok);
    if (ok && amount > 0) {
        // 弹出输入密码的对话框
        bool passwordOk;
        QString password = QInputDialog::getText(this, "密码验证", "请输入密码:", QLineEdit::Password, "", &passwordOk);

        if (passwordOk && !password.isEmpty()) {
            // 验证密码
            QSqlQuery query;
            query.prepare("SELECT password FROM users WHERE ID_card = :idCard");
            query.bindValue(":idCard", curUser);  // 使用指定的 ID_card

            if (query.exec() && query.next()) {
                QString correctPassword = query.value(0).toString();
                if (password == correctPassword) {
                    // 密码正确，执行提现操作
                    query.prepare("SELECT ID_card FROM users WHERE ID_card = :idCard");
                    query.bindValue(":idCard", curUser);

                    if (query.exec() && query.next()) {
                        QString idCard = query.value(0).toString(); // 获取 ID_card

                        query.prepare("INSERT INTO wallet_transactions (username, ID_card, transaction_type, amount) "
                                      "VALUES (:username, :idCard, 'Withdraw', :amount)");
                        query.bindValue(":username", "user1");
                        query.bindValue(":idCard", idCard); // 插入 ID_card
                        query.bindValue(":amount", amount);

                        if (query.exec()) {
                            balance -= amount;
                            balanceLabel->setText(QString("余额: %1 元").arg(balance, 0, 'f', 2));
                            updateBalanceInDatabase();
                        } else {
                            QMessageBox::warning(this, "提现失败", "无法记录提现记录：" + query.lastError().text());
                        }
                    } else {
                        QMessageBox::warning(this, "获取 ID 失败", "无法获取用户的 ID_card：" + query.lastError().text());
                    }
                } else {
                    QMessageBox::warning(this, "密码错误", "密码输入错误！");
                }
            } else {
                QMessageBox::warning(this, "查询失败", "无法验证密码：" + query.lastError().text());
            }
        }
    }
}

void WalletWindow::onViewBillClicked()
{
    QSqlQuery query;

    if (!query.exec("SET NAMES 'utf8mb4'")) {
        qDebug() << "Failed to set character set: " << query.lastError().text();
    }

    query.prepare("SELECT transaction_type, amount, transaction_time, flight_number, departure_city, destination_city "
                  "FROM wallet_transactions WHERE username = :username ORDER BY transaction_time DESC");
    query.bindValue(":username", "user1");

    if (query.exec()) {
        QString billDetails;

        while (query.next()) {
            QString transactionType = query.value("transaction_type").toString();
            double amount = query.value("amount").toDouble();
            QString transactionTime = query.value("transaction_time").toString();
            QString flightNumber = query.value("flight_number").toString();
            QString departureCity = query.value("departure_city").toString();
            QString destinationCity = query.value("destination_city").toString();

            // 替换 T 为 空格
            transactionTime.replace("T", " ");

            // 根据交易类型设置颜色
            QString color;
            if (transactionType == "Recharge") { //充值
                color = "green";  // 绿色
            } else if (transactionType == "Withdraw") {  //提现
                color = "blue";   // 蓝色
            } else if (transactionType == "Buy") {  //
                color = "orange"; // 橙色
            } else if (transactionType == "Return") {
                color = "red";    // 红色
            } else {
                color = "black";  // 默认黑色
            }

            // 使用 HTML 显示交易类型和颜色
            billDetails.append(QString("<span style='color:%1;'>交易类型: %2</span><br>").arg(color, transactionType));
            billDetails.append(QString("金额: %1 元<br>").arg(amount, 0, 'f', 2));
            billDetails.append(QString("交易时间: %1<br>").arg(transactionTime));

            if (transactionType == "Buy" || transactionType == "Return") {
                billDetails.append(QString("航班号: %1<br>").arg(flightNumber));
                billDetails.append(QString("出发地: %1<br>").arg(departureCity));
                billDetails.append(QString("目的地: %1<br>").arg(destinationCity));
            }

            billDetails.append("<hr>");  // 分隔线
        }


        if (billDetails.isEmpty()) {
            QMessageBox::information(this, "账单明细", "没有找到任何账单记录。");
        } else {
            // 创建非模态窗口
            QWidget *billWidget = new QWidget;
            billWidget->setWindowTitle("账单明细");
            billWidget->resize(600, 500);

            // 设置样式
            billWidget->setStyleSheet(
                "QWidget { background-color: #f8f9fa; border-radius: 10px; }"
                "QTextBrowser { border: none; font-family: 'Microsoft YaHei'; }");

            QVBoxLayout *layout = new QVBoxLayout(billWidget);
            layout->setContentsMargins(15, 15, 15, 15);

            // 使用 QTextBrowser 替代 QTextEdit，支持更好的 HTML 样式渲染
            QTextBrowser *billTextBrowser = new QTextBrowser(billWidget);
            billTextBrowser->setHtml(billDetails);
            billTextBrowser->setOpenLinks(false); // 禁止打开超链接

            // 设置标题
            QLabel *titleLabel = new QLabel("账单明细", billWidget);
            titleLabel->setStyleSheet(
                "font-size: 20px; font-weight: bold; color: #343a40; margin-bottom: 10px;");
            titleLabel->setAlignment(Qt::AlignCenter);

            // 添加关闭按钮
            QPushButton *closeButton = new QPushButton("关闭", billWidget);
            closeButton->setStyleSheet(
                "QPushButton {"
                "    background-color: #007BFF;"
                "    color: white;"
                "    border: none;"
                "    padding: 10px 20px;"
                "    font-size: 14px;"
                "    border-radius: 5px;"
                "}"
                "QPushButton:hover { background-color: #0056b3; }");
            connect(closeButton, &QPushButton::clicked, billWidget, &QWidget::close);

            layout->addWidget(titleLabel);
            layout->addWidget(billTextBrowser);
            layout->addWidget(closeButton, 0, Qt::AlignCenter);
            billWidget->setLayout(layout);

            // 显示窗口
            billWidget->show();
        }
    } else {
        QMessageBox::warning(this, "查询失败", "无法加载账单信息：" + query.lastError().text());
    }
}
