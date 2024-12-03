#ifndef MYEVENTFILTER_H
#define MYEVENTFILTER_H

#include <QObject>

#include <QEvent>
#include <QMouseEvent>
#include <QLineEdit>

class MyEventFilter : public QObject
{
    Q_OBJECT

public:
    explicit MyEventFilter(QObject *parent = nullptr) : QObject(parent) {}

protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (event->type() == QEvent::MouseButtonPress) {
            emit clicked();
            return true; // 捕获了事件，不再传递给其他对象
        }
        return QObject::eventFilter(obj, event); // 默认处理方式
    }

signals:
    void clicked();
};

#endif // MYEVENTFILTER_H
