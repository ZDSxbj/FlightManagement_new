#ifndef CHATMANAGER_H
#define CHATMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMainWindow>
#include <QListWidget>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QFont>
#include "emojidialog.h"
// 包含全局变量头文件
#include "someGlobal.h"
#include "userData.h"
// // 声明全局变量
// extern int userUnreadCount;
// extern int supportUnreadCount;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Chatmanager : public QMainWindow
{
    Q_OBJECT

public:
    explicit Chatmanager(const userData &user_data,QWidget *parent = nullptr, const QString &chosenUser = "" );
    ~Chatmanager();
    void saveUnreadCountsToDatabase(const QString &myChoseUser);
    void loadUnreadCountsFromDatabase(const QString &myChoseUser);
    //void resetSupportUnreadCount();

private slots:
    void onSendButtonClicked();
    void onEmojiButtonClicked();
    void insertEmoji(const QString &emoji);
    void executeSimpleQuery();  // 新增的槽函数
    void insertMessageToDatabase(const QString &time, const QString &from_id, const QString &to_id, const QString &message);
    void scrollToBottom();
    void loadChatHistoryForSpecificUser(const QString &myChoseUser);
    void updateReadStatus(int messageId, bool isSender, bool isRead);

private:
    QSqlDatabase dbcon;  // 数据库连接
    QListWidget *listWidget;  // 列表控件
    QPlainTextEdit *plainTextEdit;  // 多行输入框
    QPushButton *sendButton;  // 发送按钮
    QPushButton *emojiButton; // 表情按钮
    QFont font;               // 字体
    EmojiDialog *emojiDialog; // 表情选择面板

    QString myChoseUser;  // 添加 myChoseUser 成员变量
    userData userdata;
};
#endif // CHATMANAGER_H
