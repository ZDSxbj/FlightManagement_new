#include "mainwindow.h"
#include "mainwindowmng.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include"Login.h"
QSqlDatabase dbcon; //数据库

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    dbcon = QSqlDatabase::addDatabase("QODBC");
    dbcon.setHostName("127.0.0.1");
    dbcon.setPort(3306);
    dbcon.setDatabaseName("Local instance MySQL8");
    dbcon.setUserName("root");  // 添加用户名
    dbcon.setPassword("ZXJsnd4697");  // 添加密码
    // 添加编码设置
    dbcon.exec("SET NAMES utf8mb4");
    bool ok = dbcon.open();
    if (!ok) {
        qDebug() << "Error, persondatabase 数据库文件打开失败！" << dbcon.lastError().text();
    } else {
        qDebug() << "Success, persondatabase 数据库文件打开成功！";
    }

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "FlightManagement_new_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    // //用户界面
    // MainWindow w;
    Login *w= new Login();
    // // 管理员界面
    // MainWindowMng w;
    // whoUse=false;
    w->show();
    return a.exec();
}
