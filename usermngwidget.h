#ifndef USERMNGWIDGET_H
#define USERMNGWIDGET_H

#include <QObject>
#include <QWidget>
#include <QWidget>
#include <QCompleter>
#include <QListWidget>
#include <QLineEdit>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QLabel>
#include <QObject>  // 添加这一行以包含 QObject
#include<QEvent>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include<QSqlQuery>
#include <QMessageBox> // 引入 QMessageBox
#include "userData.h"
#include "usermnginfo.h"
class UsermngWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UsermngWidget(QWidget *parent = nullptr);
private:
    QLineEdit *idInput;
    QLineEdit *nameInput;
    QVBoxLayout *contentLayout;  //全局的垂直布局
    QScrollArea *scrollArea;
    QWidget *scrollContentWidget;  //拖动页面的垂直布局
    QVBoxLayout *scrollContentLayout;

    QVector<userMngInfo*> userInfoList; // 存储 userMngInfo 的数组
    QVector<userData> allUsers;         // 存储所有用户数据

    void loadUsersFromDatabase();       // 从数据库加载用户数据
    void filterAndDisplayUsers();       // 根据输入框过滤用户并更新显示
     void onConfirmButtonClicked();      // 绑定确认按钮的槽函数
signals:

};

#endif // USERMNGWIDGET_H
