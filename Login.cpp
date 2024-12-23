#include "Login.h"
#include "mainwindow.h"
#include "ui_Login.h"
#include"Register.h"
#include"Forget.h"
#include <QSqlDatabase>
#include <QSqlError>
#include<QSqlQuery>
#include<QMainWindow>
#include<QMessageBox>
#include<QInputDialog>
#include<mainwindowmng.h>
#include"someGlobal.h"
using namespace std;
Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    // 设置 Login 对话框的固定宽度为 400 像素
    this->setFixedWidth(400);
    this->setFixedHeight(611);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);

    ui->forget->setTextFormat(Qt::RichText);
    ui->forget->setText("<a href=\"forgot_password\">忘记密码？</a>");
    ui->forget->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->forget->setOpenExternalLinks(false); // 禁止打开外部链接
    connect(ui->forget,&QLabel::linkActivated,this,[=](const QString &link) {
        // 当点击链接时，打开 Forget 窗口
        if (link == "forgot_password") {
            Forget *f = new Forget();
            f->show();
        }
    });

    ui->regis->setTextFormat(Qt::RichText);
    ui->regis->setText("<a href=\"register_account\">注册</a>");
    ui->regis->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->regis->setOpenExternalLinks(false); // 禁止打开外部链接
    connect(ui->regis,&QLabel::linkActivated,this,[=](const QString &link) {
        // 当点击链接时，打开 Forget 窗口
        if (link == "register_account") {
            Register *f = new Register();
            f->show();
        }
    });
    ui->registe->setTextFormat(Qt::RichText);
    ui->registe->setText("<a href=\"register_account1\">管理员注册</a>");
    ui->registe->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->registe->setOpenExternalLinks(false); // 禁止打开外部链接
    connect(ui->registe,&QLabel::linkActivated,this,[=](const QString &link) {
        // 当点击链接时，打开 Forget 窗口
        if (link == "register_account1") {
            bool ok;
            QString passwords = QInputDialog::getText(nullptr,
                                                      tr("密码输入"),
                                                      tr("请输入密码:"),
                                                      QLineEdit::Password,
                                                      QString(),
                                                      &ok);

            if (!ok || passwords.isEmpty()||passwords!="123456") {
                QMessageBox::warning(nullptr, "警告", "取消操作");
                return;
            }
            this->close();
             whoUse=false;
            MainWindowMng *v= new MainWindowMng();

            v->show();
        }
    });

    connect(ui->pushButton_2,&QPushButton::clicked,this,[=]{
        QSqlQuery query("SELECT ID_card,password FROM users");
        while(query.next())
        {
            //int id = query.value(0).toInt();
            QString card = query.value(0).toString();
            QString password = query.value(1).toString();
            QString ucard = ui->lineEdit->text();
            QString words= ui->lineEdit_2->text();
            //qDebug() << name<<" "<<words<<" "<<username<<" "<<password<<"\n";
            if(card==ucard&&password==words)
            {
                f=1;
                this->close();

                whoUse=true;
                curUser=card;
                MainWindow *w= new MainWindow();
                w->setWindowTitle("航班管理系统");
                // w->resize(800, 600);

                    w->show();
                break;
            }
        }
        if(f==0)
        {
            QMessageBox::warning(this, "登录失败", "用户名或密码错误，请重新输入！");
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
        }
    });
}
Login::~Login()
{
    delete ui;
}


