#include "Mine_indent.h"
#include <QDateTime>
#include <QSqlQuery>
#include "Indent_detail.h"
#include"someGlobal.h"
#include<QSqlError>
#include<QTimer>
#include<QApplication>
Mine_indent::Mine_indent(const QString& id_card,const bool &ustatus, QWidget *parent)
    : card(id_card),status(ustatus),QWidget(parent)
{
    setWindowTitle("航班购票系统");
    resize(800,600);
    payCheckTimer = new QTimer(this);
    connect(payCheckTimer, &QTimer::timeout, this, &Mine_indent::checkAndSearchFlights);

    // 设置定时器时间间隔（例如每500毫秒检查一次）
    payCheckTimer->start(500);
    // 创建内容区域
    queryINFO();
    createContentArea();

    // 创建主布局
    createMainLayout();
}

void Mine_indent::createContentArea()
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
            QLabel *noRecordsLabel = new QLabel("暂无订单记录", this);
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
            QLabel *noRecordsLabel = new QLabel("暂无订单记录", this);
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

void Mine_indent::queryINFO()
{
    q.clear(); // 清空之前的订单小部件列表
    // QSqlDatabase db = QSqlDatabase::database();
    // if (!db.isOpen())
    // {
    //     qDebug() << "Database connection is not open.";
    //     return;
    // }

    QSqlQuery query;
    if (!query.exec("SELECT Id_card, realname, flight_number, seat_class, price, status, departure_time,changed FROM orders"))
    {
        qDebug() << "Failed to execute orders query. Error:" << query.lastError().text();
        return;
    }

    while (query.next())
    {
        QString userid = query.value(0).toString();
        QString Ust;
        if(status==1) Ust="completed";
        else Ust="upcoming";
        if (card == userid&&Ust==query.value(5).toString())
        {
            QString name = query.value(1).toString();
            QString fli_number = query.value(2).toString();
            QDateTime departure_Date = query.value(6).toDateTime();
            QString dd = query.value(3).toString();
            double cost = query.value(4).toDouble();
            //bool statuss = (query.value(5).toString() == "upcoming");
            int change= query.value(7).toInt();
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
                                "arrival_airport, departure_airport, arrival_time, duration "
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
                bool day=0;
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
                    card,
                    fli_class,
                    cost,
                    status,
                    change,
                    day
                    );
                //QWidget *widget = indent->getWidget();
                connect(indent,&Indent_detail::deleteRequested,this,&Mine_indent::handledeleteRequest);
                connect(indent,&Indent_detail::completed,this,&Mine_indent::handlecomplete);
                q.push_back(indent);
                qDebug() << "Added widget to display list.";
            }
            else
            {
                qDebug() << "No matching flight found for flight number:" << fli_number;
            }

            query1.finish();
        }
    }

    query.finish();
}
// static bool Mine_indent::compareByDepartureDate(const Indent_detail* a, const Indent_detail* b)
// {
//     return a->getDepartureDate() < b->getDepartureDate();
// }
void Mine_indent::handledeleteRequest(const QString& name, const QString& plane, const int &uclass, const QDateTime& time, const double& price, const QString& id_card)
{
    // 开始事务
    if (!QSqlDatabase::database().transaction()) {
        qDebug() << "Failed to start transaction.";
        return;
    }

    QSqlQuery deleteQuery;
    if (!deleteQuery.prepare("DELETE FROM orders WHERE realname = :realname AND flight_number = :flight_number")) {
        qDebug() << "Failed to prepare delete query:" << deleteQuery.lastError().text();
        QSqlDatabase::database().rollback();
        return;
    }

    deleteQuery.bindValue(":realname", name);
    deleteQuery.bindValue(":flight_number", plane);

    if (!deleteQuery.exec()) {
        qDebug() << "Failed to execute delete query:" << deleteQuery.lastError().text();
        QSqlDatabase::database().rollback();
        return;
    }

    QSqlQuery updateQuery;

    // 更新航班座位信息
    QString seatColumn;
    switch (uclass) {
    case 3: seatColumn = "economy_available_seats"; break;
    case 2: seatColumn = "business_available_seats"; break;
    default: seatColumn = "first_class_available_seats"; break;
    }

    if (!updateQuery.prepare(QString("UPDATE flights SET %1 = %1 + 1 WHERE flight_number = :flight_number AND departure_time = :departure_time").arg(seatColumn))) {
        qDebug() << "Failed to prepare update query:" << updateQuery.lastError().text();
        QSqlDatabase::database().rollback();
        return;
    }

    updateQuery.bindValue(":flight_number", plane);
    updateQuery.bindValue(":departure_time", time);

    if (!updateQuery.exec()) {
        qDebug() << "Failed to execute update query:" << updateQuery.lastError().text();
        QSqlDatabase::database().rollback();
        return;
    }

    // 插入退款交易记录
    if (!updateQuery.prepare("INSERT INTO wallet_transactions (username, ID_card, transaction_type, amount, transaction_time, flight_number) "
                             "VALUES (:username, :ID_card, :transaction_type, :amount, :transaction_time, :flight_number)")) {
        qDebug() << "Failed to prepare insert into wallet_transactions:" << updateQuery.lastError().text();
        QSqlDatabase::database().rollback();
        return;
    }

    updateQuery.bindValue(":username", name);
    updateQuery.bindValue(":ID_card", id_card);
    updateQuery.bindValue(":transaction_type", "Refund");
    updateQuery.bindValue(":amount", price);
    updateQuery.bindValue(":transaction_time", QDateTime::currentDateTime());
    updateQuery.bindValue(":flight_number", plane);

    if (!updateQuery.exec()) {
        qDebug() << "Failed to insert into wallet_transactions:" << updateQuery.lastError().text();
        QSqlDatabase::database().rollback();
        return;
    }

    // 更新用户余额
    if (!updateQuery.prepare("UPDATE users SET balance = balance + :price WHERE ID_card = :id_card")) {
        qDebug() << "Failed to prepare update user balance query:" << updateQuery.lastError().text();
        QSqlDatabase::database().rollback();
        return;
    }

    updateQuery.bindValue(":price", price);
    updateQuery.bindValue(":id_card", id_card);

    if (!updateQuery.exec()) {
        qDebug() << "Failed to update user balance:" << updateQuery.lastError().text();
        QSqlDatabase::database().rollback();
        return;
    }

    // 提交事务
    if (!QSqlDatabase::database().commit()) {
        qDebug() << "Failed to commit transaction.";
        QSqlDatabase::database().rollback();
        return;
    }

    refresh(); // 成功删除后刷新界面

    QMessageBox message(this);
    message.setWindowTitle("成功!");
    message.setText("删除成功并更新了航班信息！");
    message.setStyleSheet(
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
    message.setIcon(QMessageBox::Information);
    message.exec();

    isPay = true;

}

void Mine_indent::createMainLayout()
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(contentWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);
}
void Mine_indent::refresh() {
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
void Mine_indent:: handlecomplete()
{
    refresh();
}
void Mine_indent::checkAndSearchFlights()
{
    if (isbuy) {
        qDebug()<<"刷新订单界面";
         refresh();  // 调用 searchFlights 函数
        isbuy = false;    // 置为 false，防止重复调用
    }
}
