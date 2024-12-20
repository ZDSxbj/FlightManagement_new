#include "Mine.h"
#include "Mine_indent.h"
#include<QButtonGroup>
// 构造函数
Mine::Mine(const QString& card, QWidget *parent)
    : QWidget(parent), card(card) {
    setupUi();
    setupButtons();
    setupStackedWidget();

}

void Mine::setupUi() {
    mainLayout = new QVBoxLayout(this); // 直接设置 Mine 的布局

    // 创建 contentWidget 并设置样式
    contentWidget = new QWidget(this);
    contentWidget->setStyleSheet(
        "background-color: #f0f0f0;"
        "padding: 10px;"
        );
    contentWidget->setLayout(new QVBoxLayout()); // 给 contentWidget 设置一个布局

    // 将 contentWidget 添加到主布局中
    mainLayout->addWidget(contentWidget);
}

void Mine::setupButtons() {
const QString buttonStyle = R"(
    QPushButton {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #7F7EFF, stop:1 #9E8CFE);
        color: white;
        border-radius: 10px;
        font-size: 18px;
        padding: 8px 16px;
        min-width: 60px;
        border: none;
    }
    QPushButton:hover {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #9E8CFE, stop:1 #BCA4FF);
    }
    QPushButton:checked {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #5A49FF, stop:1 #7B64FF); /* 更深的紫色 */
        /* 或者使用单一颜色 */
        /* background-color: #5A49FF; */
    }
    QPushButton:checked:hover {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #4D3AFF, stop:1 #6C55FF); /* 悬停时更深层次的紫色 */
        /* 或者使用单一颜色 */
        /* background-color: #4D3AFF; */
    }
)";


    // 创建一个容器部件用于按钮布局，并设置其背景透明
    QWidget *buttonContainer = new QWidget(contentWidget); // 确保父部件是 contentWidget
    buttonContainer->setStyleSheet("background-color: transparent;");
    buttonContainer->setAttribute(Qt::WA_TranslucentBackground, true);
    buttonContainer->setAutoFillBackground(false);


    // 创建水平布局用于按钮
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->setContentsMargins(0, 0, 0, 0); // 移除内边距以确保紧贴左边

    // 创建按钮并连接信号槽
    buttons.append(new QPushButton("未出行订单", buttonContainer));
    buttons.append(new QPushButton("已出行订单", buttonContainer));

    foreach (QPushButton *button, buttons) {
        button->setStyleSheet(buttonStyle); // 应用样式表到每个按钮
        button->setCheckable(true); // 设置按钮为可选中状态
        connect(button, &QPushButton::clicked, this, [this, button]() {
            int index = buttons.indexOf(button);
            onButtonClicked(index);
        });
        buttonLayout->addWidget(button);
    }

    // 确保两个按钮互斥，即一次只能有一个按钮被选中
    QButtonGroup *buttonGroup = new QButtonGroup(this);
    for (int i = 0; i < buttons.size(); ++i) {
        buttonGroup->addButton(buttons[i], i);
    }
    buttons[0]->setChecked(true); //初始化时第一个button被选中
    // 添加一个伸展因子来推动按钮靠左
    buttonLayout->addStretch();

    // 将按钮容器添加到主布局中
    mainLayout->addWidget(buttonContainer);
}

void Mine::setupStackedWidget() {
    stackedWidget = new QStackedWidget(this);
    mainLayout->addWidget(stackedWidget);
    // 向 QStackedWidget 中添加页面
    Mine_indent *pre = new Mine_indent(card, 0);
    Mine_indent *pos = new Mine_indent(card, 1);
    stackedWidget->addWidget(pre); // Page 1
    stackedWidget->addWidget(pos); // Page 2
}

void Mine::onButtonClicked(int index) {
    stackedWidget->setCurrentIndex(index);
}
