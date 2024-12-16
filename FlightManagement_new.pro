QT       += core gui \
    quick
QT += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buywidget.cpp \
    chatmanager.cpp \
    chatwidget.cpp \
    completedordersw.cpp \
    emojidialog.cpp \
    evaluationdialog.cpp \
    flightinfo.cpp \
    flightinfomng.cpp \
    flightmngwidget.cpp \
    homewidget.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindowmng.cpp \
    someGlobal.cpp \
    uncompletedordersw.cpp \
    userinfo.cpp \
    usermnginfo.cpp \
    usermngwidget.cpp \
    walletwindow.cpp

HEADERS += \
    FlightData.h \
    MyEventFilter.h \
    buywidget.h \
    chatmanager.h \
    chatwidget.h \
    completedordersw.h \
    emojidialog.h \
    evaluationdialog.h \
    flightinfo.h \
    flightinfomng.h \
    flightmngwidget.h \
    homewidget.h \
    mainwindow.h \
    mainwindowmng.h \
    someGlobal.h \
    uncompletedordersw.h \
    userData.h \
    userinfo.h \
    usermnginfo.h \
    usermngwidget.h \
    walletwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    FlightManagement_new_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
