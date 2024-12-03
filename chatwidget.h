#ifndef CHATWIDGET_H
#define CHATWIDGET_H
#include <QMainWindow>
#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
class ChatWidget : public QWidget {
    // Q_OBJECT
public:


    ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget(){} // 确保这里有一个可见的析构函数定义

private:
    QTextEdit *chatDisplay; // 用于显示聊天记录
    QLineEdit *messageInput; // 用户输入消息的地方
    QPushButton *sendButton; // 发送按钮
};

#endif // CHATWIDGET_H
