#ifndef NOTICE_H
#define NOTICE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QSqlQuery>

class Notice : public QWidget
{
    Q_OBJECT

public:
    explicit Notice(const QString &userId, QWidget *parent = nullptr);
    ~Notice();

private:
    void clearUnreadCount(const QString &userId); // 清零未读通知
    void loadNotices(const QString &userId);      // 加载通知内容

    QVBoxLayout *popupLayout; // 主布局
};

#endif // NOTICE_H
