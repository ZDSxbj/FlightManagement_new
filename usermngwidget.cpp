#include "usermngwidget.h"
#include <algorithm> // 引入 std::sort
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
    queryLayout->setSpacing(10);

    // 加载用户数据
    loadUsersFromDatabase();

    // 显示所有用户
    filterAndDisplayUsers();

    // 绑定确认按钮
    connect(confirmButton, &QPushButton::clicked, this, &UsermngWidget::onConfirmButtonClicked);

}

// 从数据库加载用户数据
void UsermngWidget::loadUsersFromDatabase() {
    QSqlQuery query;
    if (!query.exec("SELECT * FROM flightmanagementsystem.users")) {
        QMessageBox::critical(this, "数据库错误", query.lastError().text());
        return;
    }

    while (query.next()) {
        userData user;
        user.id = query.value("id").toInt();
        user.username = query.value("username").toString();
        user.password = query.value("password").toString();
        user.email = query.value("email").toString();
        user.registrationDate = query.value("registration_date").toDateTime();
        user.status = query.value("status").toString();
        user.phone = query.value("phone").toString();
        user.gender = query.value("gender").toString();
        user.birthday = query.value("birthday").toDateTime();
        user.avatar = query.value("avatar").toString();
        user.balance = query.value("balance").toDouble();
        user.idCard = query.value("ID_card").toString();

        // 加载未读消息计数
        QSqlQuery unreadQuery;
        QString idCard = user.idCard;
        unreadQuery.prepare("SELECT support_unread_count FROM unread_counts WHERE user_id = :idCard");
        unreadQuery.bindValue(":idCard", idCard);

        if (unreadQuery.exec() && unreadQuery.next()) {
            user.un_read_cnt = unreadQuery.value("support_unread_count").toInt();
        } else {
            // 如果没有找到对应的记录，可以设置为默认值0
            user.un_read_cnt = 0;
        }

        allUsers.append(user);
    }
}

// 自定义比较函数，用于比较两个 userData 对象的 un_read_cnt 成员
bool compareUnreadCount(const userData &a, const userData &b) {
    return a.un_read_cnt > b.un_read_cnt; // 降序排序
}


// 根据输入框内容过滤用户并更新显示
void UsermngWidget::filterAndDisplayUsers() {

    std::sort(allUsers.begin(), allUsers.end(), compareUnreadCount);  //先按未读消息数进行排序
    // 清空现有显示
    qDeleteAll(userInfoList);
    userInfoList.clear();

    QString idFilter = idInput->text().trimmed();
    QString nameFilter = nameInput->text().trimmed();

    // 清空现有布局并设置属性
    scrollContentLayout->setAlignment(Qt::AlignTop); // 向上对齐
    scrollContentLayout->setSpacing(10);            // 设置间隔为 10 像素
    for (userData &user : allUsers) {
        if ((!idFilter.isEmpty() && user.idCard != idFilter) ||
            (!nameFilter.isEmpty() && !user.username.contains(nameFilter, Qt::CaseInsensitive))) {
            continue;
        }

        userMngInfo *userInfo = new userMngInfo(user, this);
        scrollContentLayout->addWidget(userInfo);
        userInfoList.append(userInfo);
    }

    if(userInfoList.size()==0){
         QMessageBox::information(this, "查无此人", "抱歉，未找到符合条件的用户。");
    }
    scrollContentWidget->setLayout(scrollContentLayout);
}

// 确认按钮槽函数
void UsermngWidget::onConfirmButtonClicked() {
    filterAndDisplayUsers();
}

