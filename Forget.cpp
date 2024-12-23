#include "Forget.h"
#include "ui_Forget.h"
#include<QSqlQuery>
#include<QMessageBox>

Forget::Forget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Forget)
{
    ui->setupUi(this);
    connect(ui->find_button,&QPushButton::clicked,this,[=]{
        QString card = ui->Username->text();
        QString email = ui->Email->text();
        QSqlQuery query;
        query.prepare("SELECT password FROM users WHERE email = :email AND ID_card= :ID_card ");
        query.bindValue(":email",email);
        query.bindValue(":ID_card",card);
        if(query.exec())
        {
            if(query.next())
            {
                QString password = query.value(0).toString();
                QMessageBox::information(this, "找回成功",password );
                return;
            }
            else
            {
                QMessageBox::warning(this, "找回失败","输入的信息有误，请重新输入");
                ui->Email->clear();
                ui->Username->clear();
                //ui->Passwords->clear();
                return;
            }
        }
        // else
        // {
        //      qDebug() << "查询错误：" << query.lastError().text();
        // }
    });
}

Forget::~Forget()
{
    delete ui;
}
