#include "chatmanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QDateTime>
#include <QLabel>

Chatmanager::Chatmanager(const userData &user_data,QWidget *parent, const QString &myChoseUser) :
    QMainWindow(parent),
    font("Arial", 14),
    myChoseUser(myChoseUser),  // 将 myChoseUser 保存为类的成员变量
    userdata(user_data)
{
    // 创建控件
    listWidget = new QListWidget(this);
    plainTextEdit = new QPlainTextEdit(this);  // 使用 QPlainTextEdit
    sendButton = new QPushButton("Enter", this);
    emojiButton = new QPushButton("😊", this);

    // 设置 QPlainTextEdit 的 placeholderText
    plainTextEdit->setPlaceholderText("请输入您的回复：");

    // 设置布局
    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;

    hLayout->addWidget(plainTextEdit);
    hLayout->addWidget(emojiButton);
    hLayout->addWidget(sendButton);

    vLayout->addWidget(listWidget);
    vLayout->addLayout(hLayout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(vLayout);
    setCentralWidget(centralWidget);

    // 设置样式表
    sendButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #2196F3; /* 蓝色背景 */"
        "   color: white;"
        "   border: none;"
        "   padding: 10px 20px;"
        "   text-align: center;"
        "   text-decoration: none;"
        "   display: inline-block;"
        "   font-size: 14px;"
        "   margin: 4px 2px;"
        "   cursor: pointer;"
        "}"
        "QPushButton:hover {"
        "   background-color: #1E88E5; /* 鼠标悬停时的背景颜色 */"
        "}"
        "QPushButton:pressed {"
        "   background-color: #1565C0; /* 按钮按下时的背景颜色 */"
        "}"
        );

    // 设置样式表
    listWidget->setStyleSheet(
        "QListWidget { background-color: white; }"
        "QListWidget::item { padding: 5px; }"
        "QListWidget::item[user] { text-align: left; background-color: #F5F5F5; color: black; border-radius: 5px; word-wrap: break-word; max-width: 80%; margin-left: 10px; }"
        "QListWidget::item[ai] { text-align: right; background-color: #E6E6FA; color: black; border-radius: 5px; word-wrap: break-word; max-width: 80%; margin-right: 10px; }"
        "QListWidget::item[time] { text-align: center; color: gray; font-size: 10pt; }"
        );

    // 设置字体
    listWidget->setFont(font);
    plainTextEdit->setFont(font);
    sendButton->setFont(font);
    emojiButton->setFont(font);

    // 设置输入框和发送按钮的宽度
    plainTextEdit->setFixedHeight(100);  // 设置多行输入框的高度
    plainTextEdit->setFixedWidth(500);   // 调整多行输入框的宽度
    sendButton->setFixedWidth(80);       // 设置发送按钮的宽度
    emojiButton->setFixedWidth(50);      // 设置表情按钮的宽度

    // 连接信号和槽
    connect(sendButton, &QPushButton::clicked, this, &Chatmanager::onSendButtonClicked);
    connect(emojiButton, &QPushButton::clicked, this, &Chatmanager::onEmojiButtonClicked);

    // 创建表情对话框
    emojiDialog = new EmojiDialog(this);
    connect(emojiDialog, &EmojiDialog::emojiSelected, this, &Chatmanager::insertEmoji);

    // 设置主窗口的初始大小
    resize(800, 600);  // 调整窗口的初始大小为 800x600 像素

    // 加载特定用户的聊天记录
    //QString myChoseUser = QString::number(3);  // 替换为你需要的特定ID

    loadChatHistoryForSpecificUser(myChoseUser);

    // 自动滚动到底部
    scrollToBottom();

}

Chatmanager::~Chatmanager()
{
    delete emojiDialog;
}


void Chatmanager::insertMessageToDatabase(const QString &time, const QString &from_id, const QString &to_id, const QString &message)
{
    QSqlQuery query(dbcon);

    query.prepare("INSERT INTO messages (time, from_id, to_id, message, is_read_by_sender, is_read_by_receiver) "
                  "VALUES (:time, :from_id, :to_id, :message, :is_read_by_sender, :is_read_by_receiver)");
    query.bindValue(":time", time);
    query.bindValue(":from_id", from_id);
    query.bindValue(":to_id", to_id);
    query.bindValue(":message", message);
    query.bindValue(":is_read_by_sender", false);  // 发送端初始状态为已读
    query.bindValue(":is_read_by_receiver", true);  // 接收端初始状态为未读

    if (!query.exec()) {
        qDebug() << "Error inserting message into database:" << query.lastError().text();
    }

    // 更新 unread_counts 表中的未读消息数
    query.prepare("UPDATE unread_counts SET user_unread_count = user_unread_count + 1 WHERE user_id = :to_id");
    query.bindValue(":to_id", to_id);

    if (!query.exec()) {
        qDebug() << "Error updating unread counts in database:" << query.lastError().text();
    }
}

void Chatmanager::onSendButtonClicked()
{
    QString userInput = plainTextEdit->toPlainText();
    if (!userInput.isEmpty()) {
        // 获取当前时间
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString formattedTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");

        // 显示时间
        QListWidgetItem *timeItem = new QListWidgetItem(formattedTime);
        timeItem->setTextAlignment(Qt::AlignCenter);
        timeItem->setData(Qt::UserRole, "time");
        listWidget->addItem(timeItem);

        // 显示客服输入（右对齐）
        QString aiMessage = QString("客服: %1").arg(userInput);
        QListWidgetItem *aiItem = new QListWidgetItem(aiMessage);
        aiItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        aiItem->setBackground(QColor("#E6E6FA"));  // 客服消息的灰色背景
        aiItem->setData(Qt::UserRole, "ai");
        listWidget->addItem(aiItem);

        // QString myChoseUser = QString::number(3);

        // 插入客服消息到数据库
        insertMessageToDatabase(formattedTime, QString::number(1), myChoseUser, userInput);  // 假设用户ID为3

        // // 增加用户的未读消息数
        // userUnreadCount++;
        // qDebug() << "用户未读消息数增加，目前未读消息总数为：" << userUnreadCount;

        // 清空输入框
        plainTextEdit->clear();

        // 滚动到底部
        scrollToBottom();

    } else {
        // 显示自定义的消息框
        QMessageBox msgBox;
        msgBox.setWindowTitle("Empty Input!");
        msgBox.setText("输入消息不能为空哦~");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStyleSheet(
            "QMessageBox {"
            "   width: 200px;"
            "}"
            "QPushButton {"
            "   background-color: #6A5ACD; "
            "   color: white;"
            "   border: none;"
            "   padding: 10px 20px;"
            "   text-align: center;"
            "   text-decoration: none;"
            "   display: inline-block;"
            "   font-size: 14px;"
            "   margin: 4px 2px;"
            "   cursor: pointer;"
            "}"
            "QPushButton:hover {" //鼠标悬停
            "   background-color: #BA55D3;"
            "}"
            "QPushButton:pressed {"  //鼠标按下
            "   background-color: #6543A4;"
            "}"
            );
        msgBox.exec();

        // 自动聚焦到输入框
        plainTextEdit->setFocus();
    }
}


// 滚动到底部的方法
void Chatmanager::scrollToBottom()
{
    listWidget->scrollToBottom();
}

void Chatmanager::onEmojiButtonClicked()
{
    emojiDialog->exec();
}

void Chatmanager::insertEmoji(const QString &emoji)
{
    plainTextEdit->insertPlainText(emoji);
}


// 新增的方法
void Chatmanager::executeSimpleQuery()
{
    // 创建一个 QSqlQuery 对象
    QSqlQuery query(dbcon);

    // 执行一个简单的 SELECT 查询
    if (query.exec("SELECT * FROM messages")) {
        while (query.next()) {
            // 假设你的表中有四列：id、time、from_id、to_id 和 message
            int id = query.value(0).toInt();
            QString time = query.value(1).toString();
            QString from_id = query.value(2).toString();
            QString to_id = query.value(3).toString();
            QString message = query.value(4).toString();

            // 创建一个 QListWidgetItem 来显示查询结果
            QListWidgetItem *item = new QListWidgetItem(QString("ID: %1, 时间: %2, 发送者: %3, 接收者: %4, 消息: %5")
                                                            .arg(id).arg(time).arg(from_id).arg(to_id).arg(message));
            item->setData(Qt::UserRole, "queryResult");
            listWidget->addItem(item);
        }
    } else {
        // 如果查询失败，输出错误信息
        qDebug() << "Error: query failed" << query.lastError().text();
    }
}


void Chatmanager::loadChatHistoryForSpecificUser(const QString &myChoseUser)
{
    listWidget->clear();  // 清除旧的聊天记录

    // 构建查询语句，筛选出所有包含特定ID的行
    QSqlQuery query(dbcon);
    QString sql = QString("SELECT * FROM messages WHERE from_id = %1 OR to_id = %1 ORDER BY time ASC").arg(myChoseUser);
    if (query.exec(sql)) {
        while (query.next()) {
            int messageId = query.value(0).toInt();
            QString time = query.value(1).toString();
            QString from_id = query.value(2).toString();
            QString to_id = query.value(3).toString();  // 使用 to_id
            QString message = query.value(4).toString();
            //bool is_read_by_sender = query.value(5).toBool();
            //bool is_read_by_receiver = query.value(6).toBool();
            QString evaluation = query.value(7).toString(); // 假设evaluation是第7列

            qDebug() << "Retrieved message: " << message;  // 打印检索的消息内容

            // 显示时间
            QListWidgetItem *timeItem = new QListWidgetItem(time);
            timeItem->setTextAlignment(Qt::AlignCenter);
            timeItem->setData(Qt::UserRole, "time");
            listWidget->addItem(timeItem);

            // 构建带前缀的消息
            QString formattedMessage;
            if (from_id == myChoseUser) {  // 用户消息
                formattedMessage = QString("%1: %2").arg(userdata.username,message);
            } else {  // 客服消息
                formattedMessage = QString("客服: %1").arg(message);
            }

            // 显示消息
            QListWidgetItem *messageItem = new QListWidgetItem(formattedMessage);
            if (from_id == myChoseUser && to_id != myChoseUser) {  // 用户发给客服的消息
                messageItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);  // 左对齐
                messageItem->setBackground(QColor("#F5F5F5"));  // 用户消息的浅灰色背景
                messageItem->setData(Qt::UserRole, "user");

            } else if (from_id != myChoseUser && to_id == myChoseUser) {  // 客服发给用户的消息
                messageItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);  // 右对齐
                messageItem->setBackground(QColor("#E6E6FA"));  // 客服消息的浅蓝色背景
                messageItem->setData(Qt::UserRole, "ai");

            } else {
                // 其他情况处理
                messageItem->setTextAlignment(Qt::AlignCenter);
                messageItem->setBackground(QColor("#FFFFFF"));  // 默认白色背景
                messageItem->setData(Qt::UserRole, "other");
            }
            listWidget->addItem(messageItem);

            // 更新历史消息为已读
            updateReadStatus(messageId, true, true);

            // 显示评价
            if (!evaluation.isEmpty()) {
                QString evalMessage = QString("用户评价: %1").arg(evaluation);
                QListWidgetItem *evaluationItem = new QListWidgetItem(evalMessage);
                evaluationItem->setTextAlignment(Qt::AlignCenter);
                evaluationItem->setBackground(QColor("#FFFAF0")); // 浅黄色背景
                evaluationItem->setData(Qt::UserRole, "evaluation");
                listWidget->addItem(evaluationItem);
            }
        }
        // // 清零未读消息计数
        // QSqlQuery updateQuery(dbcon);
        // updateQuery.prepare("UPDATE unread_counts SET user_unread_count = 0, support_unread_count = 0 WHERE user_id = :myChoseUser");
        // updateQuery.bindValue(":myChoseUser", myChoseUser);
        // if (!updateQuery.exec()) {
        //     qDebug() << "Error resetting unread counts in database:" << updateQuery.lastError().text();
        // }
    } else {
        qDebug() << "Error loading chat history for specific user:" << query.lastError().text();
    }
}

void Chatmanager::updateReadStatus(int messageId, bool isSender, bool isReceiver)
{
    QSqlQuery query(dbcon);
    query.prepare("UPDATE messages SET is_read_by_sender = :isSender, is_read_by_receiver = :isReceiver WHERE id = :id");
    query.bindValue(":isSender", isSender);
    query.bindValue(":isReceiver", isReceiver);
    query.bindValue(":id", messageId);

    if (!query.exec()) {
        qDebug() << "Error updating read status in database:" << query.lastError().text();
    }
}


// 从数据库加载未读消息数
void Chatmanager::loadUnreadCountsFromDatabase(const QString &myChoseUser)
{
    QSqlQuery query;
    query.prepare("SELECT user_unread_count, support_unread_count FROM unread_counts WHERE user_id = :myChoseUser");
    query.bindValue(":myChoseUser", myChoseUser);

    if (query.exec() && query.next()) {
        //userUnreadCount = query.value(0).toInt();
        //supportUnreadCount = query.value(1).toInt();
    } else {
        qDebug() << "Error loading unread counts from database:" << query.lastError().text();
    }
}

// 将未读消息数保存到数据库
void Chatmanager::saveUnreadCountsToDatabase(const QString &myChoseUser)
{
    QSqlQuery query;
    query.prepare("REPLACE INTO unread_counts (user_id, user_unread_count, support_unread_count) "
                  "VALUES (:myChoseUser, :user_unread_count, :support_unread_count)");
    query.bindValue(":myChoseUser", myChoseUser);
    //query.bindValue(":user_unread_count", userUnreadCount);
    //query.bindValue(":support_unread_count", supportUnreadCount);

    if (!query.exec()) {
        qDebug() << "Error saving unread counts to database:" << query.lastError().text();
    }
}

/*
void Chatmanager::resetSupportUnreadCount()
{
    QSqlQuery query(dbcon);
    query.prepare("UPDATE unread_counts SET support_unread_count = 0 WHERE user_id = :user_id");
    query.bindValue(":user_id", myChoseUser);  // 假设 myChoseUser 是当前用户的 ID

    if (!query.exec()) {
        qDebug() << "Error resetting support_unread_count in database:" << query.lastError().text();
    } else {
        qDebug() << "Support unread count reset successfully.";
    }
}
*/
