/********************************************************************************
** Form generated from reading UI file 'Login.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QFrame *frame;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QPushButton *pushButton_2;
    QLabel *forget;
    QLabel *regis;
    QLabel *registe;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(390, 527);
        Login->setStyleSheet(QString::fromUtf8("/* \350\256\276\347\275\256 QMainWindow \347\232\204\350\203\214\346\231\257\345\222\214\345\255\227\344\275\223 */\n"
"QDialog{\n"
"    background: rgb(255, 255, 255); /* \350\203\214\346\231\257\350\211\262\344\270\272\347\231\275\350\211\262 */\n"
"    font-size: 15px; /* \350\256\276\347\275\256\345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-family: \"MingLiU-ExtB\", \"Arial\", sans-serif; /* \350\256\276\347\275\256\345\255\227\344\275\223\357\274\214\347\241\256\344\277\235\345\271\263\345\217\260\346\224\257\346\214\201 */\n"
"background-image: url(:/new/prefix1/980(1).jpg);\n"
" background-size: cover; /* \350\203\214\346\231\257\345\233\276\345\203\217\346\214\211\346\257\224\344\276\213\347\274\251\346\224\276\345\271\266\345\241\253\345\205\205\345\256\271\345\231\250 */\n"
"    background-position: center; /* \350\203\214\346\231\257\345\233\276\345\203\217\345\261\205\344\270\255\346\230\276\347\244\272 */\n"
"    background-repeat: no-repeat; /* \344\270\215\351\207\215\345\244\215"
                        "\350\203\214\346\231\257 */\n"
"}\n"
"\n"
"/* \350\256\276\347\275\256 QFrame \350\203\214\346\231\257\345\233\276\347\211\207 */\n"
"QFrame {\n"
"    border: solid 10px rgba(0, 0, 0, 1); /* \351\273\221\350\211\262\345\256\236\347\272\277\350\276\271\346\241\206\357\274\214\345\256\275\345\272\246\344\270\272 10px */\n"
"    background-repeat: no-repeat; /* \344\270\215\351\207\215\345\244\215 */\n"
"    background-position: center; /* \345\261\205\344\270\255\346\230\276\347\244\272\350\203\214\346\231\257\345\233\276\347\211\207 */\n"
"}\n"
"\n"
"/* \350\256\276\347\275\256 QLineEdit \346\240\267\345\274\217 */\n"
"QLineEdit {\n"
"    color: #8d98a1; /* \350\276\223\345\205\245\346\226\207\346\234\254\347\232\204\351\242\234\350\211\262 */\n"
"    background-color: #405361; /* \350\276\223\345\205\245\346\241\206\350\203\214\346\231\257\350\211\262 */\n"
"    font-size: 16px; /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    border-style: outset; /* \345\244\226\345\207\270\350\276\271\346\241\206"
                        "\346\240\267\345\274\217 */\n"
"    border-radius: 10px; /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"    font-family: \"MingLiU-ExtB\", \"Arial\", sans-serif; /* \350\256\276\347\275\256\345\255\227\344\275\223 */\n"
"}\n"
"\n"
"/* \350\256\276\347\275\256 QPushButton \346\240\267\345\274\217 */\n"
"QPushButton {\n"
"    background: #ced1d8; /* \346\214\211\351\222\256\350\203\214\346\231\257\350\211\262 */\n"
"    border-style: outset; /* \345\244\226\345\207\270\350\276\271\346\241\206\346\240\267\345\274\217 */\n"
"    border-radius: 10px; /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"    font-family: \"MingLiU-ExtB\", \"Arial\", sans-serif; /* \350\256\276\347\275\256\345\255\227\344\275\223 */\n"
"}\n"
"\n"
"/* \350\256\276\347\275\256 QPushButton \346\214\211\344\270\213\346\227\266\347\232\204\346\240\267\345\274\217 */\n"
"QPushButton:pressed {\n"
"    background-color: rgb(0, 170, 255); /* \346\214\211\351\222\256\346\214\211\344\270\213\346\227\266\350\203\214\346\231\257\351"
                        "\242\234\350\211\262 */\n"
"    border-style: inset; /* \346\214\211\351\222\256\346\214\211\344\270\213\346\227\266\350\276\271\346\241\206\346\240\267\345\274\217 */\n"
"    font-family: \"MingLiU-ExtB\", \"Arial\", sans-serif; /* \350\256\276\347\275\256\345\255\227\344\275\223 */\n"
"}\n"
"\n"
"/* \350\256\276\347\275\256 QCheckBox \346\240\267\345\274\217 */\n"
"QCheckBox {\n"
"    background: rgba(85, 170, 255, 0); /* \350\203\214\346\231\257\351\200\217\346\230\216 */\n"
"    color: white; /* \346\226\207\345\255\227\351\242\234\350\211\262 */\n"
"    font-family: \"MingLiU-ExtB\", \"Arial\", sans-serif; /* \350\256\276\347\275\256\345\255\227\344\275\223 */\n"
"}\n"
"\n"
"/* \350\256\276\347\275\256 QLabel \346\240\267\345\274\217 */\n"
"QLabel {\n"
"    background: rgba(85, 170, 255, 0); /* \350\203\214\346\231\257\351\200\217\346\230\216 */\n"
"    \n"
"}\n"
""));
        frame = new QFrame(Login);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(20, 110, 351, 311));
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 50, 91, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setPointSize(18);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextEditable);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(60, 90, 61, 21));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font1.setPointSize(16);
        font1.setBold(true);
        label_2->setFont(font1);
        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(60, 120, 171, 31));
        lineEdit_2 = new QLineEdit(frame);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(60, 190, 171, 31));
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(60, 160, 41, 21));
        label_3->setFont(font1);
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(70, 250, 161, 41));
        forget = new QLabel(frame);
        forget->setObjectName("forget");
        forget->setGeometry(QRect(160, 226, 61, 20));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Adobe Devanagari")});
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setItalic(true);
        font2.setUnderline(true);
        forget->setFont(font2);
        regis = new QLabel(frame);
        regis->setObjectName("regis");
        regis->setGeometry(QRect(170, 50, 51, 31));
        regis->setFont(font);
        registe = new QLabel(frame);
        registe->setObjectName("registe");
        registe->setGeometry(QRect(250, 10, 91, 21));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font3.setPointSize(12);
        font3.setBold(true);
        registe->setFont(font3);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Login", "\347\231\273\345\275\225/", nullptr));
        label_2->setText(QCoreApplication::translate("Login", "\350\272\253\344\273\275\345\217\267\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("Login", "\345\257\206\347\240\201\357\274\232", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Login", "\347\231\273\345\275\225", nullptr));
        forget->setText(QCoreApplication::translate("Login", "\345\277\230\350\256\260\345\257\206\347\240\201", nullptr));
        regis->setText(QCoreApplication::translate("Login", "\346\263\250\345\206\214", nullptr));
        registe->setText(QCoreApplication::translate("Login", "\347\256\241\347\220\206\345\221\230\345\205\245\345\217\243", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
