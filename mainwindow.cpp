#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),

    orderbuttonGroup(new QButtonGroup(this)),  // 初始化订单按钮组
    mybuttonGroup(new QButtonGroup(this)),    // 初始化“我的”按钮组
    buttonGroup(new QButtonGroup(this)),
    homePage(new HomeWidget(this)),
    minePage(new Mine(curUser)),
    ticketsPage(new Tickets(getUsernameByIdCard(curUser))),
    userInfoPage(new UserInfo(this)),
    walletWindow(new WalletWindow(this)),
    chatPage(new ChatWidget(this))
{
    ui->setupUi(this);

    // 设置主窗口默认大小
    this->resize(1000, 700); // 宽1200，高800
    QWidget *centralWidget = new QWidget; // 创建中心部件
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget); // 水平布局将界面分为左右两部分


    QString mainButtonStyle =
        "QPushButton {"
        "    color: white;"  // 图标和文字颜色
        "    background-color: transparent;" // 默认透明背景
        "    border: none;"  // 无边框
        "    border-radius: 25px;" // 圆形按钮效果（主按钮较大）
        "    padding: 15px;"  // 主按钮内边距较大，增强突出效果
        "    font-size: 18px;"  // 主按钮文字稍大
        "    font-weight: bold;" // 字体加粗
        "    text-align: center;"
        "    width: 85px;" // 设置主按钮的宽度为200px
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(255, 255, 255, 0.2);" // 悬停时半透明白色背景
        "}"
        "QPushButton:checked {"
        "    background-color: rgba(255, 255, 255, 0.3);" // 激活状态更明显
        "}"
        "QPushButton:pressed {"
        "    background-color: rgba(255, 255, 255, 0.6);" // 按下时更深的透明白
        "}";

    QString subButtonStyle =
        "QPushButton {"
        "    color: white;"  // 图标和文字颜色
        "    background-color: transparent;" // 默认透明背景
        "    border: none;"  // 无边框
        "    border-radius: 12px;" // 圆形按钮效果（子按钮较小）
        "    padding: 10px;"  // 子按钮内边距较小
        "    font-size: 14px;"  // 子按钮文字稍小
        "    font-weight: bold;" // 字体加粗
        "    text-align: center;"

        "}"
        "QPushButton:hover {"
        "    background-color: rgba(255, 255, 255, 0.15);" // 悬停时半透明白色背景稍浅
        "}"
        "QPushButton:checked {"
        "    background-color: rgba(255, 255, 255, 0.35);" // 激活状态稍弱于主按钮
        "}"
        "QPushButton:pressed {"
        "    background-color: rgba(255, 255, 255, 0.5);" // 按下时透明度更高
        "}";
    // 创建一个 QWidget 作为 menuLayout 的容器
    QWidget *menuContainer = new QWidget;
    QVBoxLayout *menuLayout = new QVBoxLayout();
    // 设置菜单容器的背景样式
    menuContainer->setStyleSheet(
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
        "stop:0 #504BB0, " // 起始颜色稍深#504BB0
        "stop:0.5 #7D74F5, " // 中间颜色稍深
        "stop:1 #A9A4FF); " // 终止颜色不变
        "border-radius: 10px;"
        );

    // 将 menuLayout 设置为 menuContainer 的布局
    menuContainer->setLayout(menuLayout);

    homeButton = new QPushButton("首页"); // 创建“首页”按钮
    homeButton->setStyleSheet(mainButtonStyle);
    buttonGroup->addButton(homeButton, buttonGroup->buttons().size()); // 将按钮添加到按钮组
    orderButton = new QPushButton("出行服务");// 创建“订单”按钮
    orderButton->setStyleSheet(mainButtonStyle);
    buttonGroup->addButton(orderButton, buttonGroup->buttons().size()); // 将按钮添加到按钮组
    myButton =new QPushButton("我的");// 创建“我的”按钮，并允许展开/折叠
    myButton->setStyleSheet(mainButtonStyle);
    buttonGroup->addButton(myButton, buttonGroup->buttons().size()); // 将按钮添加到按钮组
    contactButton =new QPushButton("消息"); // 创建“联系客服”按钮
    contactButton->setStyleSheet(mainButtonStyle);
    buttonGroup->addButton(contactButton, buttonGroup->buttons().size()); // 将按钮添加到按钮组


    //"订单"按钮下的子菜单
    orderButtonsContainer = new QWidget;
    QVBoxLayout *orderButtonsLayout = new QVBoxLayout(orderButtonsContainer);
    orderButtonsLayout->setContentsMargins(0, 0, 0, 0); // 设置内边距为0
    uncompletedButton =new QPushButton("我的订单"); // 创建“未完成订单”按钮

    uncompletedButton->setStyleSheet(subButtonStyle);
    orderbuttonGroup->addButton(uncompletedButton, orderbuttonGroup->buttons().size()); // 将按钮添加到按钮组
    orderButtonsLayout->addWidget(uncompletedButton); // 添加“未完成订单”按钮到子菜单
    completedButton =new QPushButton("我的车票"); // 创建“已完成订单”按钮
    completedButton->setStyleSheet(subButtonStyle);
    orderbuttonGroup->addButton(completedButton, orderbuttonGroup->buttons().size()); // 将按钮添加到按钮组
    orderButtonsLayout->addWidget(completedButton); // 添加“已完成订单”按钮到子菜单
    orderButtonsContainer->setVisible(false); // 默认隐藏子菜单

    // “我的”按钮下的子菜单
    myButtonsContainer = new QWidget;
    QVBoxLayout *myButtonsLayout = new QVBoxLayout(myButtonsContainer);
    myButtonsLayout->setContentsMargins(0, 0, 0, 0); // 设置内边距为0
    myinfoButton =new QPushButton("个人信息"); // 创建“个人信息”按钮
    myinfoButton->setStyleSheet(subButtonStyle);
    mybuttonGroup->addButton(myinfoButton, mybuttonGroup->buttons().size()); // 将按钮添加到按钮组
    myButtonsLayout->addWidget(myinfoButton); // 添加“个人信息”按钮到子菜单
    walletButton =new QPushButton("钱包"); // 创建“钱包”按钮
    walletButton->setStyleSheet(subButtonStyle);
    mybuttonGroup->addButton(walletButton, mybuttonGroup->buttons().size()); // 将按钮添加到按钮组
    myButtonsLayout->addWidget(walletButton); // 添加“钱包”按钮到子菜单
    myButtonsContainer->setVisible(false); // 默认隐藏子菜单
    // uncompletedButton->setMinimumSize(80, 40); // 设置最小宽度和高度
    // completedButton->setMinimumSize(80, 40);
    // // 添加上方占3份的伸展器
    // 添加上方占3份的拉伸器
    menuLayout->addStretch(3);
     // 创建主菜单布局，并将所有元素添加进去
    menuLayout->addWidget(homeButton);
    menuLayout->addWidget(orderButton);
    menuLayout->addWidget(orderButtonsContainer);
    menuLayout->addWidget(myButton);
    menuLayout->addWidget(myButtonsContainer);
    menuLayout->addWidget(contactButton);
    // 添加下方占7份的拉伸器
    menuLayout->addStretch(7);
    // 初始化动画
    orderMenuAnimation = new QPropertyAnimation(orderButtonsContainer, "maximumHeight", this);
    orderMenuAnimation->setDuration(300); // 动画持续时间300毫秒
    orderMenuAnimation->setStartValue(0);
    orderMenuAnimation->setEndValue(200); // 根据实际内容调整高度

    myMenuAnimation = new QPropertyAnimation(myButtonsContainer, "maximumHeight", this);
    myMenuAnimation->setDuration(300); // 动画持续时间300毫秒
    myMenuAnimation->setStartValue(0);
    myMenuAnimation->setEndValue(200); // 根据实际内容调整高度


    // 在构造函数中添加以下代码：
    buttonGroup->setExclusive(true); // 设置按钮组为互斥模式
    orderbuttonGroup->setExclusive(true);
    mybuttonGroup->setExclusive(true);
    homeButton->setCheckable(true);
    orderButton->setCheckable(true);
    myButton->setCheckable(true);
    contactButton->setCheckable(true);
    uncompletedButton->setCheckable(true);
    completedButton->setCheckable(true);
    myinfoButton->setCheckable(true);
    walletButton->setCheckable(true);
     // 连接按钮的 clicked 信号到对应的槽函数，用于控制菜单展开和收起
    connect(orderButton, &QPushButton::clicked, this, [this]() {
        orderButton->setChecked(true);

        toggleOrderMenu();
           });
    connect(myButton, &QPushButton::clicked, this, [this]() {
        myButton->setChecked(true);
        walletButton->setChecked(false);
        myinfoButton->setChecked(false);
        toggleMyMenu();
            });


    // 右侧内容区域包含标题栏和QStackedWidget
    QVBoxLayout *contentLayout = new QVBoxLayout;

    QWidget *titleBar = new QWidget;// 创建标题栏

    titleBar->setStyleSheet(
        "background: qlineargradient("
        "    spread:pad, x1:0, y1:0, x2:1, y2:1, "
        "    stop:0 #F7F7FF, stop:1 #EBF0FF);" // 渐变背景：白色到浅蓝
        "border-bottom: 2px solid #D0D8FF;" // 下边框为柔和的浅蓝色
        );
    QHBoxLayout *titlelayout = new QHBoxLayout(titleBar);

    maintitle=new QLabel("航班管理系统（用户）");
    maintitle->setStyleSheet(
        "font-size: 30px;"           // 主标题字体更大
        "font-weight: bold;"         // 设置为粗体
        "color: #625AFF;"            // 主标题颜色为紫色
        "padding: 10px 0px;"         // 上下内边距
        "text-align: center;"        // 文本水平居中
        "border: none;"  // 确保移除边框
        );

    functitle=new QLabel("首页");
    functitle->setStyleSheet(
        "font-size: 26px;"           // 功能标题字体稍小
        "font-weight: 500;"          // 设置中等粗细
        "color: #625AFF;"            // 功能标题颜色为紫色
        "padding: 5px 0px;"          // 上下内边距
        "text-align: center;"        // 文本水平居中
        "border: none;"  // 确保移除边框
        );
    titlelayout->addWidget(maintitle); // 应用名称
    titlelayout->addWidget(functitle); //处于那一页名称

    titlelayout->addStretch(); // 使应用名称靠左对齐

    // personButton样式
    QSqlQuery query;

    if (query.exec(QString("SELECT username FROM users WHERE ID_card='%1'").arg(curUser)) && query.next()) {
        QString userName = query.value(0).toString();

        // 创建按钮并设置其文本
        personButton = new QPushButton(userName + "，您好", this);
    } else {
        // 如果查询失败或者没有找到用户，设置默认文本
        personButton = new QPushButton("用户，您好", this);
        qDebug() << "Database query failed or user not found:" << query.lastError();
    }

    personButton->setStyleSheet("QPushButton {"
                                "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #7F7EFF, stop:1 #9E8CFE);"
                                "color: white;"
                                "border-radius: 8px;"
                                "font-size: 12px;"
                                "font-weight: bold;"
                                "padding: 3px 8px;"
                                "width: 80px;"
                                "border: none;"
                                "}"
                                "QPushButton:hover {"
                                "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #9E8CFE, stop:1 #BCA4FF);"
                                "}"
                                "QPushButton:pressed {"
                                "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #6D6CFF, stop:1 #8E7AFE);"
                                "}");

    // 将按钮添加到布局中
    titlelayout->addWidget(personButton); // 个人按钮
    personButton->installEventFilter(this);
    // switchButton样式
    switchButton = new QPushButton("切换账号");
    switchButton->setStyleSheet("QPushButton {"
                                "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FF9800, stop:1 #FFB74D);"
                                "color: white;"
                                "border-radius: 8px;"
                                "font-size: 12px;"
                                "font-weight: bold;"
                                "padding: 3px 8px;"
                                "width: 50px;"
                                "border: none;"
                                "}"
                                "QPushButton:hover {"
                                "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FFB74D, stop:1 #FFCC80);"
                                "}"
                                "QPushButton:pressed {"
                                "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #F57C00, stop:1 #FF6F00);"
                                "}");

    // 将按钮添加到布局中
    titlelayout->addWidget(switchButton); // 切换账号按钮

    // noticeButton样式
    noticeButton = new QPushButton("通知");
    noticeButton->setStyleSheet("QPushButton {"
                                "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #7F7EFF, stop:1 #9E8CFE);"
                                "color: white;"
                                "border-radius: 8px;"
                                "font-size: 12px;"
                                "font-weight: bold;"
                                "padding: 3px 8px;"
                                "width: 50px;"
                                "border: none;"
                                "}"
                                "QPushButton:hover {"
                                "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #9E8CFE, stop:1 #BCA4FF);"
                                "}"
                                "QPushButton:pressed {"
                                "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #6D6CFF, stop:1 #8E7AFE);"
                                "}");

    // 将按钮添加到布局中
    titlelayout->addWidget(noticeButton); // 通知按钮
    contentLayout->addWidget(titleBar);


    stackedWidget = new QStackedWidget; // 创建QStackedWidget用于页面切换
    //添加页面到QStackedWidget
    // 将所有页面添加到 QStackedWidget 中
    stackedWidget->addWidget(homePage);
    stackedWidget->addWidget(minePage);
    stackedWidget->addWidget(ticketsPage);
    stackedWidget->addWidget(userInfoPage);
    stackedWidget->addWidget(walletWindow);
    stackedWidget->addWidget(chatPage);
    stackedWidget->setCurrentIndex(0); // 假设首页是第一页，索引为0
    // 添加信号与槽的连接，并确保点击时按钮变为 checked 状态
    connect(homeButton, &QPushButton::clicked, this, [this]() {
        myButtonsContainer->setVisible(false);
        orderButtonsContainer->setVisible(false);
        homeButton->setChecked(true);
        switchPage(0);
    });

    connect(uncompletedButton, &QPushButton::clicked, this, [this]() {
        uncompletedButton->setChecked(true);
        switchPage(1);
    });

    connect(completedButton, &QPushButton::clicked, this, [this]() {
        completedButton->setChecked(true);
        switchPage(2);
    });

    connect(myinfoButton, &QPushButton::clicked, this, [this]() {
        myinfoButton->setChecked(true);
        switchPage(3);
    });

    connect(walletButton, &QPushButton::clicked, this, [this]() {
        walletButton->setChecked(true);
        switchPage(4);
    });

    // 初始化按钮文本（需要实现 queryUserUnreadCount 方法）
    int unreadCount = queryUserUnreadCount(curUser);
    if (unreadCount > 0) {
        contactButton->setText(tr("消息 (%1)").arg(unreadCount));
    }
    connect(contactButton, &QPushButton::clicked, this, [this]() {
        myButtonsContainer->setVisible(false);
        orderButtonsContainer->setVisible(false);
        contactButton->setChecked(true);
        // 更新按钮文本为默认文本 "消息"
        contactButton->setText(tr("消息"));

        // 清除用户的未读消息计数（需要实现 resetUserUnreadCount 方法）
        resetUserUnreadCount(curUser);
        switchPage(5);
    });
    homeButton->setChecked(true);  //初始化时先选中homeButton
    contentLayout->addWidget(stackedWidget);

    // 将菜单容器添加到主布局中，而不是直接添加 menuLayout
    mainLayout->addWidget(menuContainer); // 将左侧菜单布局添加到主布局中
    mainLayout->addLayout(contentLayout); // 将右侧内容布局添加到主布局中

    setCentralWidget(centralWidget); // 设置中心部件

}

MainWindow::~MainWindow()
{
    delete ui;
}

/// @brief 切换订单菜单的可见性，并执行展开或收起动画
void MainWindow::toggleOrderMenu() {
    if (orderButtonsContainer->isVisible()) {
        // 如果菜单已经可见，则执行收起动画
        orderMenuAnimation->setDirection(QAbstractAnimation::Backward);
        orderMenuAnimation->start();
        orderButtonsContainer->setVisible(false);

    } else {
        // 如果菜单不可见，则执行展开动画
        orderMenuAnimation->setDirection(QAbstractAnimation::Forward);
        orderMenuAnimation->start();
        orderButtonsContainer->setVisible(true);
        myButtonsContainer->setVisible(false); // 确保一次只展开一个子菜单

    }

}

/// @brief 切换我的菜单的可见性，并执行展开或收起动画
void MainWindow::toggleMyMenu() {
    if (myButtonsContainer->isVisible()) {
        // 如果菜单已经可见，则执行收起动画
        myMenuAnimation->setDirection(QAbstractAnimation::Backward);
        myMenuAnimation->start();
        myButtonsContainer->setVisible(false);
    } else {
        // 如果菜单不可见，则执行展开动画
        myMenuAnimation->setDirection(QAbstractAnimation::Forward);
        myMenuAnimation->start();
        myButtonsContainer->setVisible(true);
        orderButtonsContainer->setVisible(false); // 确保一次只展开一个子菜单
    }
}

void MainWindow::showUserInfo() {
    // 假设 curUser 包含当前用户的 ID_card
    QString idCard = curUser;
    QSqlQuery query;
    query.exec(QString("SELECT username, phone, email FROM users WHERE ID_card='%1'").arg(idCard));

    if (query.next()) {
        QString userInfo = QString(
                               "姓名: %1\n"
                               "身份证号码: %2\n"
                               "电话号码: %3\n"
                               "邮箱: %4")
                               .arg(query.value(0).toString())
                               .arg(curUser)
                               .arg(query.value(1).toString())
                               .arg(query.value(2).toString());

        // 获取鼠标位置并偏移一点，避免遮挡按钮
        QPoint globalPos = QCursor::pos();
        globalPos += QPoint(20, 20);
        // 获取按钮的全局位置并计算提示框位置（按钮正下方）
        QPoint buttonBottomLeft = personButton->mapToGlobal(QPoint(0, personButton->height()));

        // 显示工具提示
        QToolTip::showText(buttonBottomLeft, userInfo, personButton);
    }
    else {
        // 如果查询失败，处理错误
        qDebug() << "Database query failed:" << query.lastError();
    }
}


/// @brief 根据索引切换到对应的页面
/// @param index QStackedWidget 的页面索引
void MainWindow::switchPage(int index) {
    stackedWidget->setCurrentIndex(index);

    // 更新标题栏中的功能标题
    switch (index) {
    case 0:
        functitle->setText("首页");
        break;
    case 1:
        functitle->setText("我的订单");
        break;
    case 2:
        functitle->setText("我的车票");
        break;
    case 3:
        functitle->setText("个人信息");
        break;
    case 4:
        functitle->setText("钱包");
        break;
    case 5:
        functitle->setText("联系客服");
        break;
    default:
        functitle->setText("未知页面");
        break;
    }
}

int MainWindow::queryUserUnreadCount(const QString &userId)
{
    QSqlQuery query;
    query.prepare("SELECT user_unread_count FROM unread_counts WHERE user_id = :id");
    query.bindValue(":id", userId);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0; // 如果没有找到记录或者有其他错误则返回0
}

void MainWindow::resetUserUnreadCount(const QString &userId)
{
    QSqlQuery query;
    query.prepare("UPDATE unread_counts SET user_unread_count = 0 WHERE user_id = :id");
    query.bindValue(":id", userId);

    if (!query.exec()) {
        // 错误处理...
    }
}

QString MainWindow::getUsernameByIdCard(const QString& idCard) {
    // 创建并准备SQL查询
    QSqlQuery query;
    query.prepare("SELECT username FROM users WHERE ID_card = :idCard");
    query.bindValue(":idCard", idCard);

    // 执行查询
    if (query.exec()) {
        // 检查是否有结果返回
        if (query.next()) {
            // 获取查询到的username
            return query.value(0).toString();
        } else {
            // 如果没有找到匹配的记录，可以返回一个空串或其他默认值
            qDebug() << "No user found for ID card:" << idCard;
            return QString(); // 返回空串
        }
    } else {
        // 如果查询失败，打印错误信息
        qDebug() << "Database query failed:" << query.lastError().text();
        return QString(); // 返回空串
    }
}
