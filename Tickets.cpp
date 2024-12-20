#include "Tickets.h"
#include"Indent_detail.h"
#include<QSqlError>
#include<QApplication>
Tickets::Tickets(const QString & name,QWidget *parent)
    : name(name),QWidget(parent)
{
    setWindowTitle("航班购票系统");
    resize(800,600);
    payCheckTimer = new QTimer(this);
    connect(payCheckTimer, &QTimer::timeout, this, &Tickets::checkAndSearchFlights);

    // 设置定时器时间间隔（例如每500毫秒检查一次）
    payCheckTimer->start(500);
    // 创建内容区域
    queryINFO();
    createContentArea();

    // 创建主布局
    createMainLayout();
}
void Tickets::createContentArea()
{
    if (!contentWidget) {
        contentWidget = new QWidget(this);
        QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);

        // 标题

        // QLabel *titleLabel = new QLabel((status==0)?"待出行订单":"已出行订单", this);
        // titleLabel->setStyleSheet("font-size: 24px; color: #4a90e2;");
        // contentLayout->addWidget(titleLabel);

        // 划分线
        QFrame *line = new QFrame(this);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line->setStyleSheet("border: none; background-color:rgb(65, 157, 255); height: 2px;");
        contentLayout->addWidget(line);

        // 创建滚动区域
        QScrollArea *scrollArea = new QScrollArea(this);
        scrollArea->setWidgetResizable(true);

        // 创建滚动区域的内容区域
        QWidget *scrollContent = new QWidget;
        QVBoxLayout *scrollContentLayout = new QVBoxLayout(scrollContent);
        scrollContentLayout->setSpacing(5); // 减少组件之间的间距
        scrollContentLayout->setContentsMargins(5, 5, 5, 5); // 减少布局的边距

        // 排序并添加 Indent_detail 小部件到滚动内容布局中
        std::sort(q.begin(), q.end(), [](const Indent_detail* a, const Indent_detail* b) {
            return a->getDepartureDate() < b->getDepartureDate();
        });
        if (q.empty()) {
            // 如果没有记录，添加一个居中的 "暂无记录" 标签
            QLabel *noRecordsLabel = new QLabel("还没有要出行的航班哦", this);
            noRecordsLabel->setAlignment(Qt::AlignCenter);
            noRecordsLabel->setStyleSheet("color: gray; font-size: 20px;");
            scrollContentLayout->addStretch();
            scrollContentLayout->addWidget(noRecordsLabel);
            scrollContentLayout->addStretch();
        } else {
            if (QVBoxLayout* vboxLayout = dynamic_cast<QVBoxLayout*>(scrollContentLayout)) {
                vboxLayout->setAlignment(Qt::AlignTop);
            }
            for (auto widget : q) {
                widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
                widget->update();
                scrollContentLayout->addWidget(widget);
            }
        }

        scrollArea->setWidget(scrollContent);
        contentLayout->addWidget(scrollArea);

        // 设置容器小部件的样式作为背景
        contentWidget->setStyleSheet(
            "background-color: #f0f0f0;"
            "padding: 10px;"
            );

        // 将 contentWidget 添加到主布局中
        //mainLayout()->addWidget(contentWidget);
    } else {
        // 如果 contentWidget 已经存在，则直接更新其内容
        QVBoxLayout *contentLayout = static_cast<QVBoxLayout*>(contentWidget->layout());

        // 清空现有内容
        QLayoutItem *child;
        while ((child = contentLayout->takeAt(0)) != nullptr) {
            if (child->widget()) {
                child->widget()->deleteLater();
            }
            delete child;
        }


        QFrame *line = new QFrame(this);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line->setStyleSheet("border: none; background-color:rgb(65, 157, 255); height: 2px;");
        contentLayout->addWidget(line);

        QScrollArea *scrollArea = new QScrollArea(this);
        scrollArea->setWidgetResizable(true);

        QWidget *scrollContent = new QWidget;
        QVBoxLayout *scrollContentLayout = new QVBoxLayout(scrollContent);
        scrollContentLayout->setSpacing(5);
        scrollContentLayout->setContentsMargins(5, 5, 5, 5);

        std::sort(q.begin(), q.end(), [](const Indent_detail* a, const Indent_detail* b) {
            return a->getDepartureDate() < b->getDepartureDate();
        });
        if (q.empty()) {
            // 如果没有记录，添加一个居中的 "暂无记录" 标签
            QLabel *noRecordsLabel = new QLabel("还没有要出行的航班哦", this);
            noRecordsLabel->setAlignment(Qt::AlignCenter);
            noRecordsLabel->setStyleSheet("color: gray; font-size: 20px;");
            scrollContentLayout->addStretch();
            scrollContentLayout->addWidget(noRecordsLabel);
            scrollContentLayout->addStretch();
        } else {
            if (QVBoxLayout* vboxLayout = dynamic_cast<QVBoxLayout*>(scrollContentLayout)) {
                vboxLayout->setAlignment(Qt::AlignTop);
            }
            for (auto widget : q) {
                widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
                widget->update();
                scrollContentLayout->addWidget(widget);
            }
        }

        scrollArea->setWidget(scrollContent);
        contentLayout->addWidget(scrollArea);

        contentWidget->setStyleSheet(
            "background-color: #f0f0f0;"
            "padding: 10px;"
            );
    }
}
void Tickets::queryINFO()
{
    q.clear();
    // QSqlDatabase dbco = QSqlDatabase::addDatabase("QODBC", "flightManagement"); // 使用唯一连接名
    // dbco.setHostName("127.0.0.1");
    // dbco.setPort(3306);
    // dbco.setDatabaseName("tickets");
    // dbco.setUserName("root");
    // dbco.setPassword("20050516");

    // if (!dbco.open()) {
    //     qDebug() << "Error, 数据库文件打开失败！" << dbco.lastError().text();
    //     return;
    // } else {
    //     qDebug() << "Success, 数据库文件打开成功！";
    // }
    QSqlQuery query;
    if (!query.prepare("SELECT flight_number, seat_class, price, departure_time,changed FROM orders WHERE realname=:realname AND status =:status"))
    {
        qDebug() << "Failed to execute orders query. Error:" << query.lastError().text();
        return;
    }
    query.bindValue(":realname",name);
    query.bindValue(":status","upcoming");
    if (!query.exec()) {
        qDebug() << "Failed to execute orders query. Error:" << query.lastError().text();
        return;
    }

    while(query.next())
    {
        //QString name = query.value(1).toString();
        QString fli_number = query.value(0).toString();
        QDateTime departure_Date = query.value(3).toDateTime();
        QString dd = query.value(1).toString();
        int cost = query.value(2).toInt();
        //bool statuss = (query.value(5).toString() == "upcoming");
        int change= query.value(4).toInt();
        int fli_class;
        if(dd=="economy")
            fli_class=3;
        else if(dd=="business")
            fli_class=2;
        else fli_class=1;
        qDebug() << "Order details: Name:" << name
                 << ", Flight Number:" << fli_number
                 << ", Departure Date:" << departure_Date
                 << ", Class:" << fli_class
                 << ", Cost:" << cost;
        QSqlQuery query1;
        if (!query1.prepare("SELECT airline, airplane_model, departure_city, arrival_city, "
                            "arrival_airport, departure_airport, arrival_time, duration,same_day_arrival "
                            "FROM flights WHERE flight_number = :flight_number AND departure_time = :departure_time"))
        {
            qDebug() << "Failed to prepare flights query. Error:" << query1.lastError().text();
            continue;
        }
        query1.bindValue(":flight_number", fli_number);
        query1.bindValue(":departure_time", departure_Date);

        if (!query1.exec())
        {
            qDebug() << "Failed to execute flights query. Error:" << query1.lastError().text();
            continue;
        }
        if (query1.next())
        {
            QString airline = query1.value(0).toString();
            QString airmodel = query1.value(1).toString();
            QString departure_city = query1.value(2).toString();
            QString arrival_city = query1.value(3).toString();
            QString arrival_airport = query1.value(4).toString();
            QString departure_airport = query1.value(5).toString();
            QDateTime arrival_time = query1.value(6).toDateTime();
            QTime duration = query1.value(7).toTime();
            bool day=query1.value(7).toBool();
            qDebug() << "Flight details: Airline:" << airline
                     << ", Model:" << airmodel
                     << ", From:" << departure_city << "(" << departure_airport << ")"
                     << "To:" << arrival_city << "(" << arrival_airport << ")"
                     << ", Arrival Time:" << arrival_time
                     << ", Duration:" << duration;

            Indent_detail *indent = new Indent_detail(
                nullptr,
                name,
                departure_city,
                departure_airport,
                arrival_city,
                arrival_airport,
                fli_number,
                departure_Date,
                arrival_time,
                airline,
                airmodel,
                duration,
                0,
                fli_class,
                cost,
                3,
                change,
                day
                );
            //QWidget *widget = indent->getWidget();
            //connect(indent,&Indent_detail::deleteRequested,this,&Mine_indent::handledeleteRequest);
            //connect(indent,&Indent_detail::completed,this,&Mine_indent::handlecomplete);
            q.push_back(indent);
            qDebug() << "Added widget to display list.";
        }
        else
        {
            qDebug() << "No matching flight found for flight number:" << fli_number;
        }

        query1.finish();
    }
    query.finish();
}

void Tickets::createMainLayout()
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(contentWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);
}
void Tickets::refresh() {
    // 确保 contentWidget 已经被添加到布局中
    if (!contentWidget) return;

    // 清空现有内容
    QLayout *layout = contentWidget->layout();
    if (layout) {
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != nullptr) {
            if (child->widget()) {
                child->widget()->deleteLater();
            }
            delete child;
        }
    }

    // 重新查询信息并创建内容区域
    queryINFO();

    // 调用 createContentArea 创建新的内容
    createContentArea();

    // 强制重新布局
    mainLayout->activate();
    contentWidget->updateGeometry();
    contentWidget->update();

    // 确保所有事件都被处理
    QApplication::processEvents();
}
void Tickets::checkAndSearchFlights()
{
    if (isbuys) {
        refresh();  // 调用 searchFlights 函数
        isbuys = false;    // 置为 false，防止重复调用
    }
    if (isRefund) {
        refresh();  // 调用 searchFlights 函数
        isRefund = false;    // 置为 false，防止重复调用
    }

}
