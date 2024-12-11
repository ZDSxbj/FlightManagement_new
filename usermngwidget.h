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
signals:
};

#endif // USERMNGWIDGET_H
