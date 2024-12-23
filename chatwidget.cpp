#include "chatwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QDateTime>
#include <QLabel>

ChatWidget::ChatWidget(QWidget *parent) :
    QMainWindow(parent),
    font("Arial", 14)
{

    // 创建控件
    listWidget = new QListWidget(this);
    plainTextEdit = new QPlainTextEdit(this);  // 使用 QPlainTextEdit
    sendButton = new QPushButton("Enter", this);
    emojiButton = new QPushButton("😊", this);
    evaluateButton = new QPushButton("评价客服", this);  // 评价客服按钮

    // 设置 QPlainTextEdit 的 placeholderText
    plainTextEdit->setPlaceholderText("请输入您的需求：");

    // 设置布局
    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;

    hLayout->addWidget(plainTextEdit);
    hLayout->addWidget(emojiButton);
    hLayout->addWidget(sendButton);
    hLayout->addWidget(evaluateButton);  // 将评价客服按钮添加到布局中

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

    evaluateButton->setStyleSheet(
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
        "QListWidget::item[user] { text-align: right; background-color: #E6E6FA; color: black; border-radius: 5px; word-wrap: break-word; max-width: 80%; margin-right: 10px; }"
        "QListWidget::item[ai] { text-align: left; background-color: #F5F5F5; color: black; border-radius: 5px; word-wrap: break-word; max-width: 80%; margin-left: 10px; }"
        "QListWidget::item[time] { text-align: center; color: gray; font-size: 10pt; }"
        );

    // 设置字体
    listWidget->setFont(font);
    plainTextEdit->setFont(font);
    sendButton->setFont(font);
    emojiButton->setFont(font);
    evaluateButton->setFont(font);

    // 设置输入框和发送按钮的宽度
    plainTextEdit->setFixedHeight(100);  // 设置多行输入框的高度
    plainTextEdit->setFixedWidth(500);   // 调整多行输入框的宽度
    sendButton->setFixedWidth(80);       // 设置发送按钮的宽度
    emojiButton->setFixedWidth(50);      // 设置表情按钮的宽度
    evaluateButton->setFixedWidth(100);  // 设置评价客服按钮的宽度

    // 连接信号和槽
    connect(sendButton, &QPushButton::clicked, this, &ChatWidget::onSendButtonClicked);
    connect(emojiButton, &QPushButton::clicked, this, &ChatWidget::onEmojiButtonClicked);
    connect(evaluateButton, &QPushButton::clicked, this, &ChatWidget::onEvaluateButtonClicked);  // 连接评价客服按钮

    // 创建表情对话框
    emojiDialog = new EmojiDialog(this);
    connect(emojiDialog, &EmojiDialog::emojiSelected, this, &ChatWidget::insertEmoji);

    // 创建评价对话框
    evaluationDialog = new EvaluationDialog(this);

    // 设置主窗口的初始大小
    resize(800, 600);  // 调整窗口的初始大小为 800x600 像素

    // // 加载特定用户的聊天记录
    // QString curUser = QString::number(3); // 替换为你需要的特定ID

    loadChatHistoryForSpecificUser(curUser);

    // 自动滚动到底部
    scrollToBottom();

}

ChatWidget::~ChatWidget()
{
    delete emojiDialog;
    delete evaluationDialog;
}

void ChatWidget::insertMessageToDatabase(const QString &time, const QString &from_id, const QString &to_id, const QString &message)
{
    QSqlQuery query(dbcon);
    query.prepare("INSERT INTO messages (time, from_id, to_id, message, is_read_by_sender, is_read_by_receiver) "
                  "VALUES (:time, :from_id, :to_id, :message, :is_read_by_sender, :is_read_by_receiver)");
    query.bindValue(":time", time);
    query.bindValue(":from_id", from_id);
    query.bindValue(":to_id", to_id);
    query.bindValue(":message", message);
    query.bindValue(":is_read_by_sender", true);  // 发送端初始状态为已读
    query.bindValue(":is_read_by_receiver", false);  // 接收端初始状态为未读

    if (!query.exec()) {
        qDebug() << "Error inserting message into database:" << query.lastError().text();
    }

    // 更新 unread_counts 表中的未读消息数
    query.prepare("UPDATE unread_counts SET support_unread_count = support_unread_count + 1 WHERE user_id = :from_id");
    query.bindValue(":from_id", from_id);

    if (!query.exec()) {
        qDebug() << "Error updating unread counts in database:" << query.lastError().text();
    }
}

void ChatWidget::onSendButtonClicked()
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

        // 显示用户输入（右对齐）
        QString userMessage = QString("Me: %1").arg(userInput);
        QListWidgetItem *userItem = new QListWidgetItem(userMessage);
        userItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        userItem->setBackground(QColor("#E6E6FA"));  // 用户消息的浅蓝色背景
        userItem->setData(Qt::UserRole, "user");
        listWidget->addItem(userItem);

        // // 假设 curUser 是当前用户的ID
        // QString curUser = QString::number(3);  // 这里可以根据实际情况设置用户的ID

        // 插入用户消息到数据库
        insertMessageToDatabase(formattedTime, curUser, QString::number(1), userInput);  // 假设客服管理员ID为1

        // // 增加客服的未读消息数
        // supportUnreadCount++;
        // qDebug() << "客服未读消息数增加，目前未读消息总数为：" << supportUnreadCount;

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
void ChatWidget::scrollToBottom()
{
    listWidget->scrollToBottom();
}

void ChatWidget::onEmojiButtonClicked()
{
    emojiDialog->exec();
}

void ChatWidget::insertEmoji(const QString &emoji)
{
    plainTextEdit->insertPlainText(emoji);
}


void ChatWidget::onEvaluateButtonClicked()
{
    // 显示评价对话框
    int result = evaluationDialog->exec();
    if (result == QDialog::Accepted) {
        QString evaluation = evaluationDialog->getEvaluation(); // 获取评价结果
        qDebug() << "User evaluated: " << evaluation;


        QString customerServiceId = QString::number(1);  // 假设客服ID

        // 查询最近的一条消息，假设评价是针对最后一条记录
        QSqlQuery query(dbcon);
        query.prepare("SELECT id FROM messages WHERE from_id = :user_id AND to_id = :service_id ORDER BY time DESC LIMIT 1");
        query.bindValue(":user_id", curUser);
        query.bindValue(":service_id", customerServiceId);

        if (query.exec() && query.next()) {
            int messageId = query.value(0).toInt();

            // 更新评价到对应消息记录
            QSqlQuery updateQuery(dbcon);
            updateQuery.prepare("UPDATE messages SET evaluation = :evaluation WHERE id = :id");
            updateQuery.bindValue(":evaluation", evaluation);
            updateQuery.bindValue(":id", messageId);

            if (updateQuery.exec()) {
                qDebug() << "Evaluation updated successfully for message ID:" << messageId;
            } else {
                qDebug() << "Error updating evaluation:" << updateQuery.lastError().text();
            }
        } else {
            qDebug() << "Error finding the last message for evaluation:" << query.lastError().text();
        }
    }
}


// 新增的方法
void ChatWidget::executeSimpleQuery()
{
    // 创建一个 QSqlQuery 对象
    QSqlQuery query(dbcon);

    // 执行一个简单的 SELECT 查询
    if (query.exec("SELECT * FROM messages")) {
        while (query.next()) {
            // 假设你的表中有四列：id、time、from_id、to_id 和 message
            int id = query.value(0).toInt();
            QString time = query.value(1).toString();
            QString  from_id = query.value(2).toString();
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

//用户登录成功后加载聊天记录
void ChatWidget::onUserLoginSuccess(QString userId)
{
    QString curUser = userId;  // 用户ID
    loadChatHistoryForSpecificUser(curUser);  // 加载该用户的聊天记录
}


void ChatWidget::loadChatHistoryForSpecificUser(const QString &curUser)
{
    listWidget->clear();  // 清除旧的聊天记录

    // 构建查询语句，筛选出所有包含特定ID的行
    QSqlQuery query(dbcon);
    QString sql = QString("SELECT * FROM messages WHERE from_id = %1 OR to_id = %1 ORDER BY time ASC").arg(curUser);
    if (query.exec(sql)) {
        while (query.next()) {
            int messageId = query.value(0).toInt();
            QString time = query.value(1).toString();
            QString  from_id = query.value(2).toString();
            QString to_id = query.value(3).toString();  // 使用 to_id
            QString message = query.value(4).toString();
            //bool is_read_by_sender = query.value(5).toBool();
            //bool is_read_by_receiver = query.value(6).toBool();

            qDebug() << "Retrieved message: " << message;  // 打印检索的消息内容

            // 显示时间
            QListWidgetItem *timeItem = new QListWidgetItem(time);
            timeItem->setTextAlignment(Qt::AlignCenter);
            timeItem->setData(Qt::UserRole, "time");
            listWidget->addItem(timeItem);

            // 构建带前缀的消息
            QString formattedMessage;
            if (from_id == curUser) {  // 用户消息
                formattedMessage = QString("Me: %1").arg(message);
            } else {  // 客服消息
                formattedMessage = QString("客服: %1").arg(message);
            }

            // 显示消息
            QListWidgetItem *messageItem = new QListWidgetItem(formattedMessage);
            if (from_id == curUser && to_id != curUser) {  // 用户发给客服的消息
                messageItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
                messageItem->setBackground(QColor("#E6E6FA"));  // 用户消息的浅蓝色背景
                messageItem->setData(Qt::UserRole, "user");

            } else if (from_id != curUser && to_id == curUser) {  // 客服发给用户的消息
                messageItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
                messageItem->setBackground(QColor("#F5F5F5"));  // 客服消息的浅灰色背景
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
        }

    } else {
        qDebug() << "Error loading chat history for specific user:" << query.lastError().text();
    }
}


void ChatWidget::updateReadStatus(int messageId, bool isSender, bool isReceiver)
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
void ChatWidget::loadUnreadCountsFromDatabase(const QString &curUser)
{
    QSqlQuery query;
    query.prepare("SELECT user_unread_count, support_unread_count FROM unread_counts WHERE user_id = :curUser");
    query.bindValue(":curUser", curUser);

    if (query.exec() && query.next()) {
        // userUnreadCount = query.value(0).toInt();
        // supportUnreadCount = query.value(1).toInt();
    } else {
        qDebug() << "Error loading unread counts from database:" << query.lastError().text();
    }
}

// 将未读消息数保存到数据库
void ChatWidget::saveUnreadCountsToDatabase(const QString &curUser)
{
    QSqlQuery query;
    query.prepare("REPLACE INTO unread_counts (user_id, user_unread_count, support_unread_count) "
                  "VALUES (:curUser, :user_unread_count, :support_unread_count)");
    query.bindValue(":curUser", curUser);
    // query.bindValue(":user_unread_count", userUnreadCount);
    // query.bindValue(":support_unread_count", supportUnreadCount);

    if (!query.exec()) {
        qDebug() << "Error saving unread counts to database:" << query.lastError().text();
    }
}

