/********************************************************************************
** Form generated from reading UI file 'Register.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *Label;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_2;
    QLineEdit *Id_card;
    QSpacerItem *horizontalSpacer_11;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLineEdit *Email;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_4;
    QLineEdit *Username;
    QSpacerItem *horizontalSpacer_4;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_3;
    QLineEdit *Passwords;
    QSpacerItem *horizontalSpacer_6;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName("Register");
        Register->resize(403, 432);
        Register->setStyleSheet(QString::fromUtf8("/* \350\256\276\347\275\256 QMainWindow \347\232\204\350\203\214\346\231\257\345\222\214\345\255\227\344\275\223 */\n"
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
"    background-image: url(:/new/prefix1/Far Cry 5 Josephs Word View.png); /* \350\203\214\346\231\257\345\233\276\347\211\207 */\n"
"    background-repeat: no-repeat; /* \344\270\215\351\207\215\345\244\215 */\n"
"    background-position: center; /* \345\261\205\344\270\255\346\230\276\347\244\272\350\203\214\346\231\257\345\233\276\347\211\207 */\n"
"}\n"
"\n"
"/* \350\256\276\347\275\256 QLineEdit \346\240\267\345\274\217 */\n"
"QLineEdit {\n"
"    color: #8d98a1; /* \350\276\223\345\205\245\346\226\207\346\234\254\347\232\204\351\242\234\350\211\262 */\n"
"    background-color: #405361; /* \350\276\223\345\205\245\346\241\206\350\203\214\346\231\257\350\211\262 */\n"
"    font-size: 16px; "
                        "/* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    border-style: outset; /* \345\244\226\345\207\270\350\276\271\346\241\206\346\240\267\345\274\217 */\n"
"    border-radius: 10px; /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"    font-family: \"MingLiU-ExtB\", \"Arial\", sans-serif; /* \350\256\276\347\275\256\345\255\227\344\275\223 */\n"
"}\n"
"\n"
"/* \350\256\276\347\275\256 QPushButton \346\240\267\345\274\217 */\n"
"QPushButton {\n"
"    background: rgb(170, 85, 255); /* \346\214\211\351\222\256\350\203\214\346\231\257\350\211\262 */\n"
"    border-style: outset; /* \345\244\226\345\207\270\350\276\271\346\241\206\346\240\267\345\274\217 */\n"
"    border-radius: 10px; /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"    font-family: \"MingLiU-ExtB\", \"Arial\", sans-serif; /* \350\256\276\347\275\256\345\255\227\344\275\223 */\n"
"}\n"
"\n"
"/* \350\256\276\347\275\256 QPushButton \346\214\211\344\270\213\346\227\266\347\232\204\346\240\267\345\274\217 */\n"
"QPushBut"
                        "ton:pressed {\n"
"    background-color: rgb(0, 170, 255); /* \346\214\211\351\222\256\346\214\211\344\270\213\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
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
""
                        "}\n"
""));
        gridLayout = new QGridLayout(Register);
        gridLayout->setObjectName("gridLayout");
        widget = new QWidget(Register);
        widget->setObjectName("widget");
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        Label = new QLabel(Register);
        Label->setObjectName("Label");
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setPointSize(18);
        font.setBold(true);
        Label->setFont(font);
        Label->setMidLineWidth(0);
        Label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(Label, 1, 0, 1, 1);

        widget_6 = new QWidget(Register);
        widget_6->setObjectName("widget_6");
        horizontalLayout_5 = new QHBoxLayout(widget_6);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);

        label_2 = new QLabel(widget_6);
        label_2->setObjectName("label_2");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font1.setPointSize(14);
        font1.setBold(true);
        label_2->setFont(font1);

        horizontalLayout_5->addWidget(label_2);

        Id_card = new QLineEdit(widget_6);
        Id_card->setObjectName("Id_card");
        Id_card->setMinimumSize(QSize(0, 30));

        horizontalLayout_5->addWidget(Id_card);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_11);


        gridLayout->addWidget(widget_6, 2, 0, 1, 1);

        widget_3 = new QWidget(Register);
        widget_3->setObjectName("widget_3");
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        label = new QLabel(widget_3);
        label->setObjectName("label");
        label->setMinimumSize(QSize(40, 30));
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label);

        Email = new QLineEdit(widget_3);
        Email->setObjectName("Email");
        Email->setMinimumSize(QSize(100, 30));
        Email->setFrame(false);
        Email->setCursorMoveStyle(Qt::LogicalMoveStyle);

        horizontalLayout_3->addWidget(Email);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        gridLayout->addWidget(widget_3, 3, 0, 1, 1);

        widget_4 = new QWidget(Register);
        widget_4->setObjectName("widget_4");
        horizontalLayout_4 = new QHBoxLayout(widget_4);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        label_4 = new QLabel(widget_4);
        label_4->setObjectName("label_4");
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_4);

        Username = new QLineEdit(widget_4);
        Username->setObjectName("Username");
        Username->setMinimumSize(QSize(0, 30));

        horizontalLayout_4->addWidget(Username);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        gridLayout->addWidget(widget_4, 4, 0, 1, 1);

        widget_5 = new QWidget(Register);
        widget_5->setObjectName("widget_5");
        horizontalLayout = new QHBoxLayout(widget_5);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        label_3 = new QLabel(widget_5);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(45, 0));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_3);

        Passwords = new QLineEdit(widget_5);
        Passwords->setObjectName("Passwords");
        Passwords->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(Passwords);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);


        gridLayout->addWidget(widget_5, 5, 0, 1, 1);

        widget_2 = new QWidget(Register);
        widget_2->setObjectName("widget_2");
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(90, 40));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("MingLiU-ExtB")});
        font2.setPointSize(14);
        font2.setBold(true);
        pushButton->setFont(font2);

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_9);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName("pushButton_2");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setMinimumSize(QSize(90, 40));
        pushButton_2->setFont(font2);

        horizontalLayout_2->addWidget(pushButton_2);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_8);


        gridLayout->addWidget(widget_2, 6, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 7, 0, 1, 1);


        retranslateUi(Register);

        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QDialog *Register)
    {
        Register->setWindowTitle(QCoreApplication::translate("Register", "Dialog", nullptr));
        Label->setText(QCoreApplication::translate("Register", "\346\263\250\345\206\214", nullptr));
        label_2->setText(QCoreApplication::translate("Register", "\350\272\253\344\273\275\345\217\267", nullptr));
        label->setText(QCoreApplication::translate("Register", "\351\202\256\347\256\261\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("Register", "\345\220\215\345\255\227\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("Register", "\345\257\206\347\240\201\357\274\232", nullptr));
        pushButton->setText(QCoreApplication::translate("Register", "\346\263\250\345\206\214", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Register", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
