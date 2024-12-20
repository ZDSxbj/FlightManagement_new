#include "notice.h"
#include <QSqlError> // 添加这一行以包含 QSqlError 的定义

Notice::Notice(const QString &userId, QWidget *parent)
    : QWidget(parent), popupLayout(new QVBoxLayout(this))
{
    setWindowTitle("通知");
    setFixedSize(600, 600);

    // 标题
    QLabel *titleLabel = new QLabel("通知列表");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; text-align: center;");
    titleLabel->setAlignment(Qt::AlignCenter);
    popupLayout->addWidget(titleLabel);

    // 滚动区域
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    QWidget *scrollWidget = new QWidget;
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollWidget->setLayout(scrollLayout);
    scrollArea->setWidget(scrollWidget);
    popupLayout->addWidget(scrollArea);

    // 关闭按钮
    QPushButton *closeButton = new QPushButton("关闭");
    closeButton->setStyleSheet("background-color: #007BFF; color: white; font-size: 14px; padding: 6px 12px; border-radius: 4px;");
    popupLayout->addWidget(closeButton);
    popupLayout->setAlignment(closeButton, Qt::AlignCenter);

    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);

    // 清零未读通知数量
    QSqlQuery clearQuery;
    clearQuery.prepare("UPDATE notice_num SET notice_num = 0 WHERE ID_card = :ID_card");
    clearQuery.bindValue(":ID_card", userId);

    if (!clearQuery.exec()) {
        qWarning("Failed to clear unread notice count.");
    }

    // 加载通知内容
    QSqlQuery query;
    query.prepare("SELECT username, flight_number, departure_time, state, new_departure_time, notice_time "
                  "FROM notice WHERE ID_card = :ID_card "
                  "ORDER BY notice_time DESC");
    query.bindValue(":ID_card", userId);

    if (query.exec()) {
        while (query.next()) {
            QString username = query.value("username").toString();
            QString flightNumber = query.value("flight_number").toString();
            QString departureTime = query.value("departure_time").toString();
            QString state = query.value("state").toString();
            QString newDepartureTime = query.value("new_departure_time").toString();
            QString noticeTime = query.value("notice_time").toString();
            QString message;

            newDepartureTime.replace("T", " ");
            noticeTime.replace("T", " ");
            if (state == "Delayed") {
                message = QString("%1<br>尊敬的%2旅客：<br><br>很抱歉地通知您，您乘坐的<span style='color:blue;'>%3</span>航班发生延误，新的起飞时间暂定为%4。")
                              .arg(noticeTime)
                              .arg(username)
                              .arg(flightNumber)
                              .arg(newDepartureTime);
            } else if (state == "Cancelled") {
                message = QString("%1<br>尊敬的%2旅客：<br><br>很抱歉地通知您，您乘坐的<span style='color:blue;'>%3</span>航班因故取消，金额已退回，请在交易记录中查收。")
                              .arg(noticeTime)
                              .arg(username)
                              .arg(flightNumber);
            } else {
                message = "<b>未知状态的通知</b>";
            }

            // 每条通知的布局
            QWidget *noticeWidget = new QWidget;
            QVBoxLayout *noticeLayout = new QVBoxLayout(noticeWidget);
            noticeLayout->setContentsMargins(10, 10, 10, 10);

            QLabel *messageLabel = new QLabel(message);
            messageLabel->setWordWrap(true);
            messageLabel->setStyleSheet("font-size: 14px; color: #333;");
            noticeLayout->addWidget(messageLabel);

            noticeWidget->setStyleSheet("background-color: #f9f9f9; "
                                        "border: 1px solid #ddd; "
                                        "border-radius: 8px; "
                                        "margin-bottom: 10px;");
            scrollLayout->setAlignment(Qt::AlignTop);
            scrollLayout->addWidget(noticeWidget);
        }
    } else {
        QLabel *errorLabel = new QLabel("<b>查询通知失败！</b>");
        errorLabel->setAlignment(Qt::AlignCenter);
        errorLabel->setStyleSheet("color: red;");
        scrollLayout->addWidget(errorLabel);
        qWarning() << "Failed to load notices. Error:" << query.lastError().text();
    }
}

Notice::~Notice()
{
}
