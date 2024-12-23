QT       += core gui \
    quick
QT += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Changed.cpp \
    Forget.cpp \
    Indent_detail.cpp \
    Login.cpp \
    Mine.cpp \
    Mine_indent.cpp \
    Register.cpp \
    Tickets.cpp \
    addflightwidget.cpp \
    buywidget.cpp \
    change_flightinfo.cpp \
    chatmanager.cpp \
    chatwidget.cpp \
    emojidialog.cpp \
    evaluationdialog.cpp \
    flightinfo.cpp \
    flightinfomng.cpp \
    flightmngwidget.cpp \
    homewidget.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindowmng.cpp \
    notice.cpp \
    someGlobal.cpp \
    userinfo.cpp \
    usermnginfo.cpp \
    usermngwidget.cpp \
    walletwindow.cpp

HEADERS += \
    Changed.h \
    FlightData.h \
    Forget.h \
    Indent_detail.h \
    Login.h \
    Mine.h \
    Mine_indent.h \
    MyEventFilter.h \
    Register.h \
    Tickets.h \
    addflightwidget.h \
    buywidget.h \
    change_flightinfo.h \
    chatmanager.h \
    chatwidget.h \
    emojidialog.h \
    evaluationdialog.h \
    flightinfo.h \
    flightinfomng.h \
    flightmngwidget.h \
    homewidget.h \
    mainwindow.h \
    mainwindowmng.h \
    notice.h \
    someGlobal.h \
    userData.h \
    userinfo.h \
    usermnginfo.h \
    usermngwidget.h \
    walletwindow.h

FORMS += \
    Forget.ui \
    Login.ui \
    Register.ui \
    mainwindow.ui

TRANSLATIONS += \
    FlightManagement_new_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
