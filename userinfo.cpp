#include "userinfo.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QInputDialog>
#include <QCalendarWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QDateEdit>

UserInfo::UserInfo(QWidget *parent) : QWidget(parent) {
    // 设置窗口样式：圆角背景
    this->setStyleSheet(
        "QWidget { background-color: #f5f7fa; border-radius: 10px; border: 1px solid #e0e0e0; }");

    QVBoxLayout *mainLayout = new QVBoxLayout;

    // 头像部分
    avatarLabel = new QLabel(this);
    avatarLabel->setFixedSize(120, 120);
    // avatarLabel->setStyleSheet(
    //     "");
    avatarLabel->setAlignment(Qt::AlignCenter);
    avatarLabel->setPixmap(QPixmap(":/default-avatar.png").scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    avatarEditButton = new QPushButton("修改头像", this);
    avatarEditButton->setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #7F7EFF, stop:1 #9E8CFE);"
        "color: white; border-radius: 20px; font-size: 18px; padding: 10px 20px; min-width: 80px; border: none; }"
        "QPushButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #9E8CFE, stop:1 #BCA4FF); }"
        "QPushButton:pressed { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #6D6CFF, stop:1 #8E7AFE); }"
        );

    QVBoxLayout *avatarLayout = new QVBoxLayout;
    avatarLayout->addWidget(avatarLabel, 0, Qt::AlignCenter);
    avatarLayout->addWidget(avatarEditButton, 0, Qt::AlignCenter);

    // 信息部分
    QStringList infoTitles = {"手机", "邮箱", "性别", "生日", "密码","姓名", "身份证号"};
    QList<QLabel *> infoLabels = {
        phoneLabel = new QLabel("未设置", this),
        emailLabel = new QLabel("未设置", this),
        genderLabel = new QLabel("未设置", this),
        birthdayLabel = new QLabel("未设置", this),
        passwordLabel = new QLabel("******", this),
        nameLabel = new QLabel("未设置", this),
        idCardLabel = new QLabel("未设置", this)
    };

    QList<QPushButton *> editButtons;
    for (int i = 0; i < infoTitles.size() - 2; ++i) { // 排除身份证号
        QPushButton *button = new QPushButton("✎", this);
        button->setFixedSize(25, 25);
        button->setStyleSheet(
            "QPushButton {"
            "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #7F7EFF, stop:1 #9E8CFE);"
            "color: white; border-radius: 20px; font-size: 18px; padding: 5px 10px; border: none; }"
            "QPushButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #9E8CFE, stop:1 #BCA4FF); }"
            "QPushButton:pressed { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #6D6CFF, stop:1 #8E7AFE); }"
            );
        editButtons.append(button);
    }

    QVBoxLayout *formLayout = new QVBoxLayout;
    // 按新顺序排列字段
    int newOrder[] = {5, 6, 0, 1, 2, 3, 4}; // 对应姓名、身份证号、手机、邮箱、性别、生日、密码
    for (int i : newOrder) {
        QHBoxLayout *rowLayout = new QHBoxLayout;
        QLabel *titleLabel = new QLabel(infoTitles[i] + ":", this);
        titleLabel->setStyleSheet("font-size: 16px; color: #333333; font-weight: 500;");
        infoLabels[i]->setStyleSheet("font-size: 16px; color: #555555;");
        rowLayout->addWidget(titleLabel);
        rowLayout->addWidget(infoLabels[i], 1);
        if (i < editButtons.size()) { // 为可编辑字段添加按钮
            rowLayout->addWidget(editButtons[i], 0, Qt::AlignRight);
        }
        formLayout->addLayout(rowLayout);
    }

    // 组合布局
    mainLayout->addLayout(avatarLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(formLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);

    // 连接信号槽
    connect(avatarEditButton, &QPushButton::clicked, this, &UserInfo::onEditAvatar);
    connect(editButtons[0], &QPushButton::clicked, this, &UserInfo::onEditPhone);
    connect(editButtons[1], &QPushButton::clicked, this, &UserInfo::onEditEmail);
    connect(editButtons[2], &QPushButton::clicked, this, &UserInfo::onEditGender);
    connect(editButtons[3], &QPushButton::clicked, this, &UserInfo::onEditBirthday);
    connect(editButtons[4], &QPushButton::clicked, this, &UserInfo::onEditPassword);

    // 加载用户数据（假设身份证号为 '23331001'）
    loadUserData(curUser);

}

UserInfo::~UserInfo() {}

// 加载用户数据
void UserInfo::loadUserData(const QString &idCard) {
    QSqlQuery query;
    query.prepare("SELECT phone, email, username, gender, birthday, avatar, password, ID_card FROM flightmanagementsystem.users WHERE ID_card = :idCard");
    query.bindValue(":idCard", idCard);

    if (query.exec() && query.next()) {
        phoneLabel->setText(query.value("phone").toString());
        emailLabel->setText(query.value("email").toString());
        nameLabel->setText(query.value("username").toString());
        genderLabel->setText(query.value("gender").toString());
        birthdayLabel->setText(query.value("birthday").toDate().toString("yyyy-MM-dd"));
        idCardLabel->setText(query.value("ID_card").toString());  // 设置身份证号显示
        QString avatarPath = query.value("avatar").toString();
        if (!avatarPath.isEmpty()) {
            avatarLabel->setPixmap(QPixmap(avatarPath).scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        passwordLabel->setText("******");
    } else {
        QMessageBox::warning(this, "加载失败", "无法加载用户数据：" + query.lastError().text());
    }
}

// 保存用户数据
void UserInfo::saveUserData(const QString &field, const QString &value) {
    QSqlQuery query;
    query.prepare(QString("UPDATE flightmanagementsystem.users SET %1 = :value WHERE ID_card = :idCard").arg(field));
    query.bindValue(":value", value);
    query.bindValue(":idCard", curUser);  // 使用指定的ID_card值

    if (!query.exec()) {
        QMessageBox::warning(this, "保存失败", "无法保存数据：" + query.lastError().text());
    }
}

// 修改头像
void UserInfo::onEditAvatar() {
    QString filePath = QFileDialog::getOpenFileName(this, "选择头像图片", "", "图片文件 (*.png *.jpg *.jpeg *.bmp);;所有文件 (*.*)");
    if (!filePath.isEmpty()) {
        QPixmap avatar(filePath);
        if (!avatar.isNull()) {
            avatarLabel->setPixmap(avatar.scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            saveUserData("avatar", filePath);
        } else {
            QMessageBox::warning(this, "加载失败", "无法加载所选图片，请选择有效的图片文件。");
        }
    }
}

// 修改手机号
void UserInfo::onEditPhone() {
    QString phone = QInputDialog::getText(this, "修改手机", "请输入新手机号码:");
    if (!phone.isEmpty()) {
        phoneLabel->setText(phone);
        saveUserData("phone", phone);
    }
}

// 修改邮箱
void UserInfo::onEditEmail() {
    QString email = QInputDialog::getText(this, "修改邮箱", "请输入新邮箱地址:");
    if (!email.isEmpty()) {
        emailLabel->setText(email);
        saveUserData("email", email);
    }
}

// 修改性别
void UserInfo::onEditGender() {
    QStringList items = {"male", "female"};
    bool ok;
    QString gender = QInputDialog::getItem(this, "修改性别", "请选择性别:", items, 0, false, &ok);
    if (ok) {
        genderLabel->setText(gender);
        saveUserData("gender", gender);
    }
}

void UserInfo::onEditBirthday() {
    // 创建一个QDialog作为对话框
    QDialog *calendarDialog = new QDialog(this);
    calendarDialog->setWindowTitle("选择生日");  // 设置窗口标题

    QVBoxLayout *layout = new QVBoxLayout(calendarDialog);

    // 创建QCalendarWidget并设置样式
    QCalendarWidget *calendarWidget = new QCalendarWidget(calendarDialog);

    // 去掉左侧的星期数字
    calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    // 设置其他样式
    calendarWidget->setStyleSheet(
        "QCalendarWidget {"
        "background-color: #f7f7f7;"
        "color: #333333;"
        "border: none;"
        "font-size: 14px;"
        "}"
        "QCalendarWidget QToolButton {"
        "border: none;"
        "background-color: #e8e8e8;"
        "border-radius: 5px;"
        "padding: 5px;"
        "}"
        "QCalendarWidget QToolButton:hover {"
        "background-color: #cccccc;"
        "}"
        "QCalendarWidget QToolButton:pressed {"
        "background-color: #aaaaaa;"
        "}"
        "QCalendarWidget QWidget:focus {"
        "border: 2px solid #6c7cfe;"
        "}"
        );
    layout->addWidget(calendarWidget);

    // 创建确认按钮，并设置样式
    QPushButton *okButton = new QPushButton("确认", calendarDialog);
    okButton->setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #7F7EFF, stop:1 #9E8CFE);"
        "color: white; border-radius: 10px; font-size: 18px; padding: 10px 20px; min-width: 100px; border: none; }"
        "QPushButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #9E8CFE, stop:1 #BCA4FF); }"
        "QPushButton:pressed { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #6D6CFF, stop:1 #8E7AFE); }"
        );
    layout->addWidget(okButton, 0, Qt::AlignCenter);

    // 连接确认按钮的点击信号
    connect(okButton, &QPushButton::clicked, calendarDialog, &QDialog::accept);

    // 显示对话框并等待用户选择
    if (calendarDialog->exec() == QDialog::Accepted) {
        // 获取选中的日期
        QDate selectedDate = calendarWidget->selectedDate();
        QString date = selectedDate.toString("yyyy-MM-dd");
        birthdayLabel->setText(date);
        saveUserData("birthday", date);  // 保存修改后的生日
    }

    delete calendarDialog;  // 删除对话框对象
}

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

void UserInfo::onEditPassword() {
    // 假设用户的 ID 已知，存储在 `userId` 变量中
    int userId = 1; // 示例 ID，实际应用中应动态获取

    // 从数据库中读取旧密码
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE id = :id");
    query.bindValue(":id", userId);

    if (!query.exec()) {
        QMessageBox::critical(this, "数据库错误", "无法查询用户信息: " + query.lastError().text());
        return;
    }

    QString storedPassword;
    if (query.next()) {
        storedPassword = query.value("password").toString();
    } else {
        QMessageBox::warning(this, "错误", "用户不存在或无法获取密码！");
        return;
    }

    // 验证旧密码
    bool okOld;
    QString oldPassword = QInputDialog::getText(this, "验证密码", "请输入旧密码:", QLineEdit::Password, "", &okOld);
    if (!okOld || oldPassword.isEmpty()) {
        return; // 用户取消或未输入旧密码
    }

    if (oldPassword != storedPassword) {
        QMessageBox::warning(this, "错误", "旧密码验证失败！");
        return;
    }

    // 验证成功，提示用户输入新密码
    bool ok1, ok2;
    QString newPassword = QInputDialog::getText(this, "修改密码", "请输入新密码:", QLineEdit::Password, "", &ok1);
    if (!ok1 || newPassword.isEmpty()) {
        return; // 用户取消或未输入新密码
    }

    QString confirmPassword = QInputDialog::getText(this, "确认密码", "请再次输入新密码:", QLineEdit::Password, "", &ok2);
    if (!ok2 || confirmPassword.isEmpty()) {
        return; // 用户取消或未输入确认密码
    }

    if (newPassword == confirmPassword) {
        // 更新数据库中的密码
        query.prepare("UPDATE users SET password = :password WHERE id = :id");
        query.bindValue(":password", newPassword); // 注意：实际应用中应对密码进行加密存储
        query.bindValue(":id", userId);

        if (query.exec()) {
            passwordLabel->setText("******"); // 密码字段始终显示掩码
            QMessageBox::information(this, "成功", "密码已修改！");
        } else {
            QMessageBox::critical(this, "数据库错误", "无法更新密码: " + query.lastError().text());
        }
    } else {
        QMessageBox::warning(this, "错误", "两次输入的新密码不一致，请重新修改！");
    }
}
