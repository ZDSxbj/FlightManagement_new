#include "Register.h"
#include "ui_Register.h"
#include<QSqlQuery>
#include<QMessageBox>
#include<QRegularExpression>
#include<QRegularExpressionMatch>
Register::Register(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, [=] {
        QString name = ui->Username->text();
        QString email = ui->Email->text();
        QString passwords = ui->Passwords->text();
        QString card = ui->Id_card->text();
        // 如果用户名为空
        if (name.isEmpty()) {
            QMessageBox::warning(this, "输入错误", "用户名不能为空！");
            return;
        }

        // 邮箱格式检查
        QRegularExpression emailRegex("^[A-Za-z0-9]+([._%+-][A-Za-z0-9]+)*@([A-Za-z0-9-]+\\.)+[A-Za-z]{2,}$");
        QRegularExpressionMatch match = emailRegex.match(email);
        if (!match.hasMatch()) {
            QMessageBox::warning(this, "邮箱格式错误", "请输入有效的邮箱地址！");
            return;  // 如果邮箱格式不正确，返回并阻止注册
        }

        // 检查密码长度
        if (passwords.size() < 8) {
            QMessageBox::warning(this, "注册失败", "密码长度必须至少为 8 个字符！");
            ui->Username->clear();
            ui->Email->clear();
            ui->Passwords->clear();
            ui->Id_card->clear();
            return;
        }
        if(card.size()!=8)
        {
            QMessageBox::warning(this, "注册失败", "身份证长度必须至少为 8 个字符！");
            ui->Username->clear();
            ui->Email->clear();
            ui->Passwords->clear();
            ui->Id_card->clear();
            return;
        }

        // 执行插入操作
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM users WHERE email = :email");
        query.bindValue(":email",email);
        if(query.exec())
        {
            query.next();
            int count= query.value(0).toInt();
            if(count>0)
            {
                QMessageBox::warning(this, "邮箱已注册", "该邮箱已被注册，请使用其他邮箱！");
                ui->Email->clear();  // 清空邮箱输入框
                return;
            }
        }
        //QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM users WHERE ID_card = :ID_card");
        query.bindValue(":ID_card",card);
        if(query.exec())
        {
            query.next();
            int count= query.value(0).toInt();
            if(count>0)
            {
                QMessageBox::warning(this, "身份已注册", "该身份已被注册，请使用其他身份！");
                ui->Id_card->clear();  // 清空邮箱输入框
                return;
            }
        }
        // else
        //     {
        //     qDebug() << "Error checking email:" << query.lastError().text();
        // }
        // 2. 执行插入操作
        query.prepare("INSERT INTO users (username, password, email,ID_card) VALUES (:username, :password, :email, :ID_card)");
        query.bindValue(":username", name);
        query.bindValue(":password", passwords);
        query.bindValue(":email", email);
        query.bindValue(":ID_card",card);

        if (query.exec()) {
            QMessageBox::information(this, "注册成功", "注册成功，请返回重新登录");
            this->close();  // 注册成功后关闭当前窗口
        } else {
            QMessageBox::warning(this, "注册失败", "注册失败, 请再次尝试！");
            ui->Username->clear();
            ui->Email->clear();
            ui->Passwords->clear();
            ui->Id_card->clear();
        }
    });

}
//基本逻辑：重复邮箱检查，格式检查，注册功能。
Register::~Register()
{
    delete ui;
}
