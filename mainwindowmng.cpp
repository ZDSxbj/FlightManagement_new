#include "mainwindowmng.h"
#include<QWidget>
#include"Login.h"
MainWindowMng::MainWindowMng(QWidget *parent)
    : QMainWindow(parent),
    buttonGroup(new QButtonGroup(this)),
    flightmngPage(new FlightmngWidget(this)),
    usermngPage(new UsermngWidget(this))
{
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


    fightmngButton = new QPushButton("航班管理"); // 创建“航班管理”按钮
    fightmngButton->setStyleSheet(mainButtonStyle);
    buttonGroup->addButton(fightmngButton, buttonGroup->buttons().size()); // 将按钮添加到按钮组
    usermngButton = new QPushButton("用户管理");// 创建“用户管理”按钮
    usermngButton->setStyleSheet(mainButtonStyle);
    buttonGroup->addButton(usermngButton, buttonGroup->buttons().size()); // 将按钮添加到按钮组

    // 将 menuLayout 设置为 menuContainer 的布局
    menuContainer->setLayout(menuLayout);

    // // 添加上方占3份的伸展器
    // 添加上方占3份的拉伸器
    menuLayout->addStretch(3);
        // 创建主菜单布局，并将所有元素添加进去
    menuLayout->addWidget(fightmngButton);
    menuLayout->addWidget(usermngButton);
    // 添加下方占7份的拉伸器
    menuLayout->addStretch(7);

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

    maintitle=new QLabel("航班管理系统（管理员）");
    maintitle->setStyleSheet(
        "font-size: 30px;"           // 主标题字体更大
        "font-weight: bold;"         // 设置为粗体
        "color: #625AFF;"            // 主标题颜色为紫色
        "padding: 10px 0px;"         // 上下内边距
        "text-align: center;"        // 文本水平居中
        "border: none;"  // 确保移除边框
        );

    functitle=new QLabel("航班管理");
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
    // switchButton样式
    switchButton=new QPushButton("切换账号");
    connect(switchButton, &QPushButton::clicked, [this]() {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("确认");
        msgBox.setText("你确定要退出吗？");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No); // 设置默认按钮为“否”

        // 显示消息框并获取用户选择的结果
        int ret = msgBox.exec();

        // 根据用户的选择执行相应的操作
        if (ret == QMessageBox::Yes)
        {
            Login *w = new Login();
            w->show();
            this->deleteLater();
        }
    });
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
    contentLayout->addWidget(titleBar);
    stackedWidget = new QStackedWidget; // 创建QStackedWidget用于页面切换
    //添加页面到QStackedWidget
    // 将所有页面添加到 QStackedWidget 中
    stackedWidget->addWidget(flightmngPage);
    stackedWidget->addWidget(usermngPage);
    stackedWidget->setCurrentIndex(0); // 假设首页是第一页，索引为0
    // 在构造函数中添加信号与槽的连接
    // 在构造函数中添加以下代码：
    buttonGroup->setExclusive(true); // 设置按钮组为互斥模式

    // 设置按钮为可检查
    fightmngButton->setCheckable(true);
    usermngButton->setCheckable(true);
    fightmngButton->setChecked(true); //初始化时，默认选中首页
    // 连接按钮的 clicked 信号到 switchPage 槽，并确保按钮被选中
    connect(fightmngButton, &QPushButton::clicked, this, [this]() {
        fightmngButton->setChecked(true);
        switchPage(0);
    });
    connect(usermngButton, &QPushButton::clicked, this, [this]() {
        usermngButton->setChecked(true);
        switchPage(1);
    });
     contentLayout->addWidget(stackedWidget);
    // 将菜单容器添加到主布局中，而不是直接添加 menuLayout
    mainLayout->addWidget(menuContainer); // 将左侧菜单布局添加到主布局中
    mainLayout->addLayout(contentLayout); // 将右侧内容布局添加到主布局中

    setCentralWidget(centralWidget); // 设置中心部件
}

/// @brief 根据索引切换到对应的页面
/// @param index QStackedWidget 的页面索引
void MainWindowMng::switchPage(int index) {
    stackedWidget->setCurrentIndex(index);

    // 更新标题栏中的功能标题
    switch (index) {
    case 0:
        functitle->setText("航班管理");
        break;
    case 1:
        functitle->setText("用户管理");
        break;

    default:
        functitle->setText("未知页面");
        break;
    }
}


MainWindowMng::~MainWindowMng() {}
