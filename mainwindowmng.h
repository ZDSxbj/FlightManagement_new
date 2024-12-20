#ifndef MAINWINDOWMNG_H
#define MAINWINDOWMNG_H

#include <QMainWindow>
#include <QObject>
#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>
#include <QScrollArea>
#include <QButtonGroup>
#include <QPropertyAnimation>
#include <QToolTip>
#include <Qtimer>
#include"flightmngwidget.h"
#include"usermngwidget.h"


class MainWindowMng: public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindowMng(QWidget *parent = nullptr);
    ~MainWindowMng();

private:
    QPushButton *fightmngButton; //航班管理按钮
    QPushButton *usermngButton; //用户管理按钮
    QPushButton *switchButton;  //切换账户按钮
    QStackedWidget *stackedWidget; // 用于管理多个页面的堆叠小部件
    QButtonGroup *buttonGroup; // 按钮组，用于管理和监听所有菜单按钮的点击事件

    QLabel *maintitle; //左上角的“航班管理系统”
    QLabel *functitle; //左上角显示“哪个页面”
    FlightmngWidget *flightmngPage;
    UsermngWidget *usermngPage;
    void switchPage(int index); //切换页面函数
};

#endif // MAINWINDOWMNG_H
