#include "usermngwidget.h"

UsermngWidget::UsermngWidget(QWidget *parent)
    : QWidget{parent}
{
    contentLayout=new QVBoxLayout(this); // 初始化 contentLayout
    // 查询条件布局
    // 查询条件布局

    QGridLayout *queryLayout = new QGridLayout();
    // 添加最前面的间隔
    queryLayout->addItem(new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Fixed), 0, 0);

    // 添加身份证标签和输入框
    queryLayout->addWidget(new QLabel("身份证:"), 0, 1);
    idInput = new QLineEdit(this);
    idInput->setPlaceholderText("请输入...");
    queryLayout->addWidget(idInput, 0, 2);

    // 添加空白间隔（在 idInput 与 用户姓名 标签之间）
    // 调整间隔更小
    queryLayout->addItem(new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 0, 3);

    // 添加用户姓名标签和输入框
    queryLayout->addWidget(new QLabel("用户姓名:"), 0, 4);
    nameInput = new QLineEdit(this);
    nameInput->setPlaceholderText("请输入...");
    queryLayout->addWidget(nameInput, 0, 5);

    // 添加空白间隔（在 nameInput 与 确认按钮之间）
    // 调整间隔更小
    queryLayout->addItem(new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 0, 6);

    // 添加确认按钮
    QPushButton *confirmButton = new QPushButton("确认");
    queryLayout->addWidget(confirmButton, 0, 7);

    // 添加最后面的间隔
    queryLayout->addItem(new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Fixed), 0, 8);

    // 将 queryLayout 添加到 contentLayout
    contentLayout->addLayout(queryLayout);
    // 创建可滚动区域
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollContentWidget = new QWidget(scrollArea);
    scrollContentLayout = new QVBoxLayout(scrollContentWidget);
    scrollArea->setWidget(scrollContentWidget);
    contentLayout->addWidget(scrollArea);



    // 设置默认布局间距和边距
    contentLayout->setContentsMargins(10, 10, 10, 10);
    queryLayout->setSpacing(5);
}
