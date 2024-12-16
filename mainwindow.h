#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
// 包含所有自定义窗口部件的头文件
#include "homewidget.h"
#include "Mine.h"
#include "Tickets.h"
#include "userinfo.h"
#include "walletwindow.h"
#include "chatwidget.h"

#include "someGlobal.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QPushButton *homeButton; //首页按钮
    QWidget *orderButtonsContainer;  //订单按钮点开显示菜单的布局
    QPushButton *orderButton;//订单按钮
    QPushButton *completedButton; //已完成订单
    QPushButton *uncompletedButton; //未完成按钮
    QButtonGroup *orderbuttonGroup; // 订单的按钮组
    QWidget *myButtonsContainer;  //我的按钮点开显示菜单的布局
    QPropertyAnimation *orderMenuAnimation; //< 用于订单菜单展开/收起动画
    QPropertyAnimation *myMenuAnimation; //< 用于我的菜单展开/收起动画
    QStackedWidget *stackedWidget; // 用于管理多个页面的堆叠小部件
    QPushButton *myButton; // “我的”按钮，控制子菜单的显示/隐藏
    QPushButton *myinfoButton; //个人信息按钮
    QPushButton *walletButton; //钱包按钮
    QButtonGroup *mybuttonGroup; //我的按钮下的按钮组
    QPushButton *contactButton;//联系客服按钮
    QButtonGroup *buttonGroup; // 按钮组，用于管理和监听所有菜单按钮的点击事件


    QLabel *maintitle; //左上角的“航班管理系统”
    QLabel *functitle; //左上角显示“哪个页面”
    QPushButton *personButton; //右上角的个人按钮
    QPushButton *switchButton; //右上角的切换账户
    QPushButton *noticeButton; //右上角的通知

    HomeWidget *homePage;
    Mine *minePage;
    Tickets *ticketsPage;
    UserInfo *userInfoPage;
    WalletWindow *walletWindow;
    ChatWidget *chatPage;
    QString curusername;
    void switchPage(int index); //切换页面函数
    QString getUsernameByIdCard(const QString& idCard);
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (obj == personButton && event->type() == QEvent::Enter) {
            showUserInfo();
            return true;
        }
        return QWidget::eventFilter(obj, event);
    }

private slots:
    // @brief 切换订单菜单的可见性，并执行展开或收起动画
    void toggleOrderMenu();
    // @brief 切换我的菜单的可见性，并执行展开或收起动画
    void toggleMyMenu();

    //简单的显示个人信息
    void showUserInfo();
    int queryUserUnreadCount(const QString &userId);
    void resetUserUnreadCount(const QString &userId);
};
#endif // MAINWINDOW_H
