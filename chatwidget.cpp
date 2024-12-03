#include "chatwidget.h"


ChatWidget::ChatWidget(QWidget *parent)
    : QWidget(parent), chatDisplay(new QTextEdit(this)), messageInput(new QLineEdit(this)), sendButton(new QPushButton("Send", this))
{
    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 添加聊天显示区域到布局中
    layout->addWidget(chatDisplay);

    // 创建一个水平布局来放置消息输入框和发送按钮
    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(messageInput);
    inputLayout->addWidget(sendButton);

    // 将水平布局添加到主布局中
    layout->addLayout(inputLayout);

    // 设置窗口的默认布局
    setLayout(layout);

    // 禁用编辑聊天显示区域
    chatDisplay->setReadOnly(true);
}
