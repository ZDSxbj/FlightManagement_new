#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMainWindow>
#include <QListWidget>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QFont>
#include "emojidialog.h"
#include "evaluationdialog.h"
// 包含全局变量头文件
#include "someGlobal.h"

// // 声明全局变量
// extern int userUnreadCount;
// extern int supportUnreadCount;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ChatWidget : public QMainWindow
{
    Q_OBJECT

public:
    ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget();
    void saveUnreadCountsToDatabase(const QString &curUser);
    void loadUnreadCountsFromDatabase(const QString &curUser);
    // void resetUserUnreadCount();

private slots:
    void onSendButtonClicked();
    void onEmojiButtonClicked();
    void insertEmoji(const QString &emoji);
    void onEvaluateButtonClicked();  // 新增的槽函数
    void executeSimpleQuery();  // 新增的槽函数
    void insertMessageToDatabase(const QString &time, const QString &from_id, const QString &to_id, const QString &message);
    void scrollToBottom();
    void loadChatHistoryForSpecificUser(const QString &curUser);
    void onUserLoginSuccess(QString userId);
    void updateReadStatus(int messageId, bool isSender, bool isRead);


private:
    QSqlDatabase dbcon;  // 数据库连接
    QListWidget *listWidget;  // 列表控件
    QPlainTextEdit *plainTextEdit;  // 多行输入框
    QPushButton *sendButton;  // 发送按钮
    QPushButton *emojiButton; // 表情按钮
    QPushButton *evaluateButton;  // 评价客服按钮
    QFont font;               // 字体
    EmojiDialog *emojiDialog; // 表情选择面板
    EvaluationDialog *evaluationDialog;  // 评价对话框
};

#endif // CHATWIDGET_H
