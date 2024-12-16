#ifndef MYEVENTFILTER_H
#define MYEVENTFILTER_H
#include<QEvent>
#include<QString>
#include<QObject>
class MyEventFilter : public QObject {
    Q_OBJECT
signals:
    void clicked();
    void focusOut(); // 新增：当捕获到失去焦点事件时发射
public:
    explicit MyEventFilter(QObject *parent = nullptr) : QObject(parent) {}

protected:
    bool eventFilter(QObject *obj, QEvent *event) override{
        if (event->type() == QEvent::MouseButtonPress) {
            emit clicked();
            return true; // 捕获了事件，不再传递给其他对象
        }else if (event->type() == QEvent::FocusOut) {
            emit focusOut(); // 发射失去焦点信号
            return false; // 让事件继续传播给其他可能的监听者
        }
        return QObject::eventFilter(obj, event); // 默认处理方式
    }
};

#endif // MYEVENTFILTER_H
