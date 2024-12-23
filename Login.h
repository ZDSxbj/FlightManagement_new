#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include"mainwindow.h"
namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    bool f=0;


private:
    Ui::Login *ui;
};

#endif // LOGIN_H
