#ifndef MINE_H
#define MINE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QPushButton>
#include <QString>
#include <QList>
#include "Mine_indent.h"

class Mine : public QWidget { // 或者是 QMainWindow 如果选择方案一
    Q_OBJECT
public:
    explicit Mine(const QString& card, QWidget *parent = nullptr);

private slots:
    void onButtonClicked(int index);

private:
    void setupUi();
    void setupButtons();
    void setupStackedWidget();

    QVBoxLayout *mainLayout;
    QStackedWidget *stackedWidget;
    QList<QPushButton*> buttons;
    QString card;
    QWidget *contentWidget; // 声明 contentWidget
};

#endif // MINE_H
