#include "Indent_detail.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDateTime>
#include <QIcon>
#include<QSqlQuery>
#include<Changed.h>
Indent_detail::Indent_detail(QWidget *parent,
                             const QString &uname,
                             const QString &departure_city,
                             const QString &departure_airport,
                             const QString &arrival_city,
                             const QString &arrival_airport,
                             const QString &number,
                             const QDateTime &udate,
                             const QDateTime &adate,
                             const QString &airline,
                             const QString &airmodel,
                             const QTime &Duration,
                             const QString & card,
                             int uclass,
                             double ucost,
                             int ustatus,
                             int change,
                             bool day)
    : QWidget(parent),
    name(uname),
    fli_number(number),
    fli_class(uclass),
    cost(ucost),
    statuss(ustatus),
    departure_city(departure_city),
    departure_airport(departure_airport),
    arrival_city(arrival_city),
    arrival_airport(arrival_airport),
    departure_Date(udate),
    arrival_time(adate),
    airline(airline),
    airmodel(airmodel),
    duration(Duration),
    id_card(card),
    change(change),
    day(day)
{
    // 计算到达时间
    //arrival_time = departure_Date.addSecs(duration.hour() * 3600 + duration.minute() * 60);
    refundMessage = new QMessageBox(this);
    refundMessage->setIcon(QMessageBox::Warning);
    refundMessage->setWindowTitle("退票确认");
    refundMessage->setText("您确定要进行退票操作吗？");
    refundMessage->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    refundMessage->setDefaultButton(QMessageBox::No);
    refundMessage->setWindowFlags(refundMessage->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    refundMessage->setStyleSheet(
        "QMessageBox {"
        "background-color: #f0f0f0;"
        "font-size: 14px;"
        "}"
        "QMessageBox QLabel{"
        "color: blue;"
        "}"
        "QMessageBox QPushButton{"
        "background-color: #4CAF50;"
        "color: white;"
        "border: none;"
        "padding: 5px 10px;"
        "}"
        );
    getWidget();
}
void Indent_detail::getWidget()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setupDateAndStatusLabels(mainLayout);   // time + status
    setupFlightInfoLabels(mainLayout);      // company
    setupFlightDetailsLabels(mainLayout);   // mainInfo
    setupPassengerInfoLabels(mainLayout);
    if(statuss==0)    // name+class
        setupTicketActions(mainLayout);        // price + button
    setLayout(mainLayout);
}
void Indent_detail::setupDateAndStatusLabels(QVBoxLayout *layout)
{
    // QWidget *dateformat = new QWidget;
    // dateformat->setStyleSheet("QWidget { background-color: transparent; }");
    QHBoxLayout *dateLayout = new QHBoxLayout(this);
    QLabel *datelabel = new QLabel(QString("%1年%2月%3日").arg(departure_Date.date().year()).arg(departure_Date.date().month()).arg(departure_Date.date().day()));
    datelabel->setStyleSheet("font-family: 'Microsoft YaHei'; font-size: 12px; background-color: transparent; color: #000000");
    QLabel *status;
    if(statuss==3)
    {
        status = new QLabel((day==1) ? "次日到达" : "即日到达");
        status->setStyleSheet(QString("font-family:'Microsoft YaHei'; color: %1; font-size: 16px;background-color: transparent; font-weight: bold;")
                                  .arg(day ? "#F44336" : "#4CAF50"));
    }
    else
    {
        status = new QLabel((statuss==1) ? "已出行" : "未出行");
        status->setStyleSheet(QString("font-family:'Microsoft YaHei'; color: %1; font-size: 16px;background-color: transparent; font-weight: bold;")
                                  .arg(statuss ? "#4CAF50" : "#F44336"));
    }

    dateLayout->addWidget(datelabel);
    dateLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    dateLayout->addWidget(status);
    dateLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    layout->addLayout(dateLayout);
}

void Indent_detail::setupFlightInfoLabels(QVBoxLayout *layout)
{
    // QWidget *flightInfoWidget = new QWidget;
    //flightInfoWidget->setStyleSheet("QWidget { background-color: transparent; }");
    QHBoxLayout *flightInfoLayout = new QHBoxLayout(this);

    QLabel *airlineLabel = new QLabel(QString("航空公司：%1").arg(airline), this);
    airlineLabel->setStyleSheet("font-family: 'Microsoft YaHei'; font-size: 12px;color: #000000; background-color: transparent;");

    QLabel *airmodelLabel = new QLabel(QString("机型：%1").arg(airmodel), this);
    airmodelLabel->setStyleSheet("font-family: 'Microsoft YaHei'; font-size: 12px;color: #000000; background-color: transparent;");

    flightInfoLayout->addWidget(airlineLabel);
    flightInfoLayout->addWidget(airmodelLabel);

    layout->addLayout(flightInfoLayout);
}

void Indent_detail::setupFlightDetailsLabels(QVBoxLayout *layout)
{
    // QWidget *flightDetailsWidget = new QWidget;
    //  flightDetailsWidget->setStyleSheet("QWidget { background-color: transparent; }");
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(0); // 减少主布局中的间距

    // QWidget *leftSideWidget = new QWidget;
    // leftSideWidget->setStyleSheet("QWidget { background-color: transparent; }");
    QVBoxLayout *leftSideLayout = new QVBoxLayout(this);
    leftSideLayout->setSpacing(5);

    QLabel *originCityLabel = new QLabel(QString("%1").arg(departure_city), this);
    originCityLabel->setStyleSheet("font-family: 'Microsoft YaHei'; font-size: 16px; color: #000000; background-color: transparent;");

    QLabel *departureTimeLabel = new QLabel(departure_Date.time().toString("hh:mm"), this);
    departureTimeLabel->setStyleSheet("font-family: 'Microsoft YaHei'; font-size: 18px; color: #000000; background-color: transparent; font-weight: bold;");

    QLabel *departureAirportLabel = new QLabel(QString("机场：%1").arg(departure_airport), this);
    departureAirportLabel->setStyleSheet("font-family: 'Microsoft YaHei'; font-size: 14px; background-color: transparent; color: #BFBFBF;");

    leftSideLayout->addWidget(originCityLabel);
    leftSideLayout->addWidget(departureTimeLabel);
    leftSideLayout->addWidget(departureAirportLabel);
    //leftSideLayout->addStretch();

    /* QWidget *rightSideWidget = new QWidget;
    rightSideWidget->setStyleSheet("QWidget { background-color: transparent; }");*/
    QVBoxLayout *rightSideLayout = new QVBoxLayout(this);
    rightSideLayout->setSpacing(5);

    QLabel *arrivalCityLabel = new QLabel(QString("%1").arg(arrival_city), this);
    arrivalCityLabel->setStyleSheet("font-family: 'Microsoft YaHei'; font-size: 16px; color: #000000; background-color: transparent;");

    QLabel *arrivalTimeLabel = new QLabel(arrival_time.time().toString("hh:mm"), this);
    arrivalTimeLabel->setStyleSheet("font-family: 'Microsoft YaHei'; font-size: 18px; color: #000000; background-color: transparent; font-weight: bold;");

    QLabel *arrivalAirportLabel = new QLabel(QString("机场：%1").arg(arrival_airport), this);
    arrivalAirportLabel->setStyleSheet("font-family: 'Microsoft YaHei'; font-size: 14px;background-color: transparent; color: #BFBFBF;");

    rightSideLayout->addWidget(arrivalCityLabel);
    rightSideLayout->addWidget(arrivalTimeLabel);
    rightSideLayout->addWidget(arrivalAirportLabel);
    //rightSideLayout->addStretch();

    // QWidget *centerWidget = new QWidget;
    //  centerWidget->setStyleSheet("QWidget { background-color: transparent; }");
    QVBoxLayout *centerLayout = new QVBoxLayout(this);
    centerLayout->setSpacing(0); // 减少中心布局中的间距
    //centerLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    // 增大箭头字体，使其看起来更长
    QLabel *arrowLabel = new QLabel("→", this);
    arrowLabel->setStyleSheet("font-family: 'Microsoft YaHei'; font-size: 48px; color: #000000; background-color: transparent;");
    arrowLabel->setAlignment(Qt::AlignCenter);

    QLabel *durationLabel = new QLabel(QString("%1小时%2分钟")
                                           .arg(duration.hour())
                                           .arg(duration.minute()),
                                       this);
    durationLabel->setStyleSheet("font-family: 'Microsoft YaHei'; font-size: 12px; color: #000000; background-color: transparent;");
    durationLabel->setAlignment(Qt::AlignCenter);

    centerLayout->addWidget(durationLabel); // 先添加持续时间
    //centerLayout->addItem(new QSpacerItem(10, 10, QSizePolicy::Fixed, QSizePolicy::Minimum));
    centerLayout->addWidget(arrowLabel);    // 再添加箭头
    centerLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    mainLayout->addLayout(leftSideLayout);
    mainLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    mainLayout->addLayout(centerLayout);
    mainLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    mainLayout->addLayout(rightSideLayout);

    layout->addLayout(mainLayout);
}
void Indent_detail::setupPassengerInfoLabels(QVBoxLayout *layout)
{
    //  QWidget *passengerInfoWidget = new QWidget;
    // passengerInfoWidget->setStyleSheet("QWidget { background-color: transparent; }");
    QHBoxLayout *passengerInfoLayout = new QHBoxLayout(this);
    passengerInfoLayout->setSpacing(10); // 减少组件之间的间距

    QLabel *passengerLabel = new QLabel(QString("%1").arg(name), this);
    passengerLabel->setStyleSheet("font-family: 'Microsoft YaHei'; font-size: 14px; color: #000000; background-color: transparent; font-weight: bold;");

    QLabel *seatLabel = new QLabel(QString("座位：%1")
                                       .arg(fli_class == 1 ? "头等舱" :
                                                fli_class == 2 ? "商务舱" : "经济舱"),
                                   this);
    seatLabel->setStyleSheet("font-family: 'Microsoft YaHei'; font-size: 14px; color: #000000; background-color: transparent;");
    passengerInfoLayout->addWidget(passengerLabel);
    passengerInfoLayout->addWidget(seatLabel);
    if(statuss==1)
    {
        QLabel *priceLabel = new QLabel(QString("票价：￥%1").arg(cost), this);
        priceLabel->setStyleSheet("font-family: 'Microsoft YaHei'; font-size: 14px; color: #FF9800;background-color: transparent; font-weight: bold;");
        passengerInfoLayout->addWidget(priceLabel);
    }

    layout->addLayout(passengerInfoLayout);
}
void Indent_detail::setupTicketActions(QVBoxLayout *layout)
{
    // QWidget *ticketActionsWidget = new QWidget;
    // ticketActionsWidget->setStyleSheet(" background-color: transparent; ");
    QHBoxLayout *ticketActionsLayout = new QHBoxLayout(this);
    QLabel *priceLabel = new QLabel(QString("票价：￥%1").arg(cost), this);
    priceLabel->setStyleSheet("font-family: 'Microsoft YaHei'; font-size: 14px; color: #FF9800;background-color: transparent; font-weight: bold;");
    ticketActionsLayout->addWidget(priceLabel);

    //refundButton->setStyleSheet("background-color: #E91E63; color: white; border-radius: 5px; padding: 10px 20px; font-family: 'Microsoft YaHei'; font-size: 16px; font-weight: bold;");
    if(change==1)
    {
        QPushButton *changeButton = new QPushButton(QIcon(":/icons/change.png"), "改签", this);
        changeButton->setStyleSheet(
            "QPushButton {"
            "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #7F7EFF, stop:1 #9E8CFE);" // 渐变紫色背景
            "color: white;" // 字体颜色为白色
            "border-radius: 10px;" // 圆角按钮
            "font-size: 18px;" // 增大字体
            "padding: 8px 8px;" // 增加内边距
            "min-width: 60px;" // 按钮最小宽度
            "border: none;" // 去除边框
            "}"
            "QPushButton:hover {"
            "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #9E8CFE, stop:1 #BCA4FF);" // 悬停时更亮的渐变色
            "}"
            "QPushButton:pressed {"
            "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #6D6CFF, stop:1 #8E7AFE);" // 按下时更深的渐变色
            "}"
            );
        ticketActionsLayout->addWidget(changeButton);
        if(!whoUse){
            changeButton->hide();
        }
        connect(changeButton,&QPushButton::clicked,this,[=]{
            QString cla;
            if(fli_class==1) cla="first_class";
            else if(fli_class==2) cla="business";
            else cla="economy";
            Changed *change = new Changed(nullptr,departure_city,arrival_city,name,departure_Date,fli_number,cla,cost,id_card);//传递参数不同,id由order来的
            connect (change,&Changed::complete,this,&Indent_detail::handlecomplete);
            change->resize(800,600);
            change->setWindowModality(Qt::ApplicationModal);
            change->show();
        });
    }
    QPushButton *refundButton = new QPushButton(QIcon(":/icons/refund.png"), "退票", this);
    refundButton->setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #7F7EFF, stop:1 #9E8CFE);" // 渐变紫色背景
        "color: white;" // 字体颜色为白色
        "border-radius: 10px;" // 圆角按钮
        "font-size: 18px;" // 增大字体
        "padding: 8px 8px;" // 增加内边距
        "min-width: 60px;" // 按钮最小宽度
        "border: none;" // 去除边框
        "}"
        "QPushButton:hover {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #9E8CFE, stop:1 #BCA4FF);" // 悬停时更亮的渐变色
        "}"
        "QPushButton:pressed {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #6D6CFF, stop:1 #8E7AFE);" // 按下时更深的渐变色
        "}"
        );

        ticketActionsLayout->addWidget(refundButton);
    if(!whoUse){
        refundButton->hide();
    }
    connect(refundButton,&QPushButton::clicked,this,&Indent_detail::ondeleteCliced);

    layout->addLayout(ticketActionsLayout);
}
void Indent_detail::ondeleteCliced()
{
    if(refundMessage->exec()==QMessageBox::Yes)
    {
        emit deleteRequested(name,fli_number,fli_class,departure_Date,cost,id_card);
    }
}
void Indent_detail::handlecomplete()
{
    qDebug()<<"have change";
    emit completed();
}

