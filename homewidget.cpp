#include "homewidget.h"
#include<QTimer>
#include <algorithm> // 确保包含这个头文件以使用 std::sort
HomeWidget::HomeWidget(QWidget *parent)
    : QWidget(parent), departureInput(nullptr), destinationInput(nullptr),
    addressListOpt(new QListWidget(this)), addressListOpt2(new QListWidget(this)),
    datePicker(new QDateEdit(QDateTime::currentDateTime().date(), this))
{
    payCheckTimer = new QTimer(this);
    connect(payCheckTimer, &QTimer::timeout, this, &HomeWidget::checkAndSearchFlights);

    // 设置定时器时间间隔（例如每500毫秒检查一次）
    payCheckTimer->start(500);
    contentLayout = new QVBoxLayout(this);

    // 地址列表
    QStringList addressList = {
        "北京", "上海", "广州", "深圳", "杭州",
        "天津", "重庆", "南京", "武汉", "成都",
        "西安", "苏州", "大连", "青岛", "宁波",
        "厦门", "长沙", "沈阳", "哈尔滨", "济南",
        "无锡", "福州", "昆明", "石家庄", "合肥",
        "郑州", "乌鲁木齐", "南昌", "南宁", "兰州",
        "银川", "呼和浩特", "海口", "贵阳", "西宁",
        "台北", "香港", "澳门", "珠海", "东莞",
        "佛山", "中山", "嘉兴", "泰州", "金华"
    };
    QCompleter* completer = new QCompleter(addressList);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);

    // 查询条件布局
    QGridLayout *queryLayout = new QGridLayout();
    queryLayout->addWidget(new QLabel("出发地:"), 0, 0);
    departureInput = new QLineEdit(this);
    departureInput->setPlaceholderText("请输入...");
    departureInput->setCompleter(completer);
    queryLayout->addWidget(departureInput, 0, 1);

    filter = new MyEventFilter(this);
    departureInput->installEventFilter(filter);

    connect(filter, &MyEventFilter::clicked, this,
            [=]() { toggleAddressListVisibility(departureInput, addressListOpt); });

    connect(addressListOpt, &QListWidget::itemClicked, this,
            [=](QListWidgetItem *item) { setAddressFromList(departureInput, addressListOpt, item); });

    queryLayout->addWidget(new QLabel("目的地:"), 0, 3);
    destinationInput = new QLineEdit(this);
    destinationInput->setPlaceholderText("请输入...");
    destinationInput->setCompleter(completer);
    queryLayout->addWidget(destinationInput, 0, 4);

    filter2 = new MyEventFilter(this);
    destinationInput->installEventFilter(filter2);

    connect(filter2, &MyEventFilter::clicked, this,
            [=]() { toggleAddressListVisibility(destinationInput, addressListOpt2); });

    connect(addressListOpt2, &QListWidget::itemClicked, this,
            [=](QListWidgetItem *item) { setAddressFromList(destinationInput, addressListOpt2, item); });

    QPushButton *switchButton = new QPushButton("切换", this);
    queryLayout->addWidget(switchButton, 0, 2);
    connect(switchButton, &QPushButton::clicked, this, &HomeWidget::swapDepartureAndDestination);

    queryLayout->addWidget(new QLabel("日期:"), 0, 5);
    datePicker->setCalendarPopup(true);
    queryLayout->addWidget(datePicker, 0, 6);
    // 假设确认按钮是最后一个添加到queryLayout的部件
    QPushButton *confirmButton = new QPushButton("确认");
    queryLayout->addWidget(confirmButton, 0, 7);
    connect(confirmButton, &QPushButton::clicked, this, &HomeWidget::searchFlights);

    contentLayout->addLayout(queryLayout);

    // 下拉地址列表
    addressListOpt->addItems(addressList);
    addressListOpt->setWindowFlags(Qt::ToolTip);
    addressListOpt->hide();

    addressListOpt2->addItems(addressList);
    addressListOpt2->setWindowFlags(Qt::ToolTip);
    addressListOpt2->hide();

    // 创建可滚动区域
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollContentWidget = new QWidget(scrollArea);
    scrollContentLayout = new QVBoxLayout(scrollContentWidget);
    scrollArea->setWidget(scrollContentWidget);
    contentLayout->addWidget(scrollArea);



    // 设置默认布局间距和边距
    contentLayout->setContentsMargins(10, 10, 10, 10);
    queryLayout->setSpacing(5);
}

void HomeWidget::toggleAddressListVisibility(QLineEdit *input, QListWidget *list) {
    QPoint globalPos = input->mapToGlobal(QPoint(0, input->height()));
    list->move(globalPos);
    list->resize(input->width(), list->sizeHint().height());
    list->setVisible(!list->isVisible());
}

void HomeWidget::setAddressFromList(QLineEdit *input, QListWidget *list, QListWidgetItem *item) {
    input->setText(item->text());
    list->hide();
}

void HomeWidget::swapDepartureAndDestination() {
    QString temp = departureInput->text();
    departureInput->setText(destinationInput->text());
    destinationInput->setText(temp);
}

//清空原来的布局
void HomeWidget::clearFlightResults()
{
    flightInfoWidgets.clear();

    // 清除布局中的所有子部件
    QLayoutItem *item;
    while ((item = scrollContentLayout->takeAt(0)) != nullptr) {
        delete item->widget(); // 删除部件
        delete item;           // 删除布局项
    }
}

//查找航班
void HomeWidget::searchFlights()
{
    qDebug() << "正确进入函数";

    // 获取用户输入的值
    QString departureCity = departureInput->text().trimmed();;
    QString arrivalCity = destinationInput->text().trimmed();
    QDate selectedDate = datePicker->date();

    // 准备SQL查询语句
    QSqlQuery query;
    query.prepare("SELECT flight_number, airline, airplane_model, "
                  "departure_city, departure_airport, arrival_city, arrival_airport, "
                  "departure_terminal, arrival_terminal, departure_time, arrival_time, "
                  "duration, same_day_arrival, status, economy_seat_capacity, "
                  "economy_available_seats, economy_price, business_seat_capacity, "
                  "business_available_seats, business_price, first_class_seat_capacity, "
                  "first_class_available_seats, first_class_price, refund_policy, baggage_policy "
                  "FROM Flights WHERE DATE(departure_time) = :date AND "
                  "departure_city = :departure_city AND arrival_city = :arrival_city");

    query.bindValue(":date", selectedDate.toString("yyyy-MM-dd"));
    query.bindValue(":departure_city", departureCity);
    query.bindValue(":arrival_city", arrivalCity);

    // 执行查询
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();

    } else {
        qDebug() << "Query executed successfully.";
    }

    // 检查是否有结果返回
    if (query.size() > 0) {
        qDebug() << "Query returned" << query.size() << "results.";
    } else {
        qDebug() << "No results found.";
    }

    // 清空之前的结果
    clearFlightResults();

    // 遍历查询结果并显示
    while (query.next()) {
        qDebug() << "Found and displaying result"; // 确认进入循环
        // 构建 FlightData 对象
        FlightData data;
        data.flight_number = query.value("flight_number").toString();
        data.airline = query.value("airline").toString();
        data.airplane_model = query.value("airplane_model").toString();
        data.departure_city = query.value("departure_city").toString();
        data.departure_airport = query.value("departure_airport").toString();
        data.arrival_city = query.value("arrival_city").toString();
        data.arrival_airport = query.value("arrival_airport").toString();
        data.departure_terminal = query.value("departure_terminal").toString();
        data.arrival_terminal = query.value("arrival_terminal").toString();
        data.departure_time = query.value("departure_time").toDateTime();
        data.arrival_time = query.value("arrival_time").toDateTime();
        data.duration = query.value("duration").toTime();
        data.same_day_arrival = query.value("same_day_arrival").toBool();
        data.status = query.value("status").toString();
        data.economy_seat_capacity = query.value("economy_seat_capacity").toInt();
        data.economy_available_seats = query.value("economy_available_seats").toInt();
        data.economy_price = query.value("economy_price").toDouble();
        data.business_seat_capacity = query.value("business_seat_capacity").toInt();
        data.business_available_seats = query.value("business_available_seats").toInt();
        data.business_price = query.value("business_price").toDouble();
        data.first_class_seat_capacity = query.value("first_class_seat_capacity").toInt();
        data.first_class_available_seats = query.value("first_class_available_seats").toInt();
        data.first_class_price = query.value("first_class_price").toDouble();
        data.refund_policy = query.value("refund_policy").toString();
        data.baggage_policy = query.value("baggage_policy").toString();
        // 判断是否至少有一个舱型有剩余座位
        if (data.economy_available_seats > 0 ||
            data.business_available_seats > 0 ||
            data.first_class_available_seats > 0) {
            // 创建一个新的 flightinfo 实例并传递数据
            flightinfo *newFlightInfo = new flightinfo(data, this); // 使用 this 作为父部件
            flightInfoWidgets.append(newFlightInfo); // 添加到向量中
            qDebug() << "Added new flightinfo instance for flight:" << data.flight_number;
        } else {
            qDebug() << "Skipped flight:" << data.flight_number << "due to no available seats.";
        }
    }
    if(flightInfoWidgets.size()==0){
        // 弹出提示窗口
        QMessageBox::information(this, "提示", "对不起，未找到符合条件的记录。");
    }
    printFlightInfos();
}

// 定义一个比较函数用于排序
bool compareByEconomyPrice(const flightinfo* lhs, const flightinfo* rhs) {
    return lhs->getPrice() < rhs->getPrice();
}
//打印航班页面
void HomeWidget::printFlightInfos()
{
    // 创建一个临时的可排序副本，因为我们不能修改原容器（因为该方法是const）
    QVector<flightinfo*> sortedFlightInfoWidgets = flightInfoWidgets;

    // 使用静态比较函数对副本进行排序
    std::sort(sortedFlightInfoWidgets.begin(), sortedFlightInfoWidgets.end(), compareByEconomyPrice);

    // 设置布局间距为 10 像素
    scrollContentLayout->setSpacing(10);
    // 应用统一的样式表到每个 flightinfo 部件

    if (QVBoxLayout* vboxLayout = dynamic_cast<QVBoxLayout*>(scrollContentLayout)) {
        vboxLayout->setAlignment(Qt::AlignTop);
    }

    // 将排序后的航班信息部件添加到滚动页面布局中
    for (const auto& flightInfo : sortedFlightInfoWidgets) {

        flightInfo->update();  // 强制刷新样式
        scrollContentLayout->addWidget(flightInfo);
    }

    // 更新布局以反映新增加的部件
    scrollContentLayout->update();
}

// 新增的槽函数
void HomeWidget::checkAndSearchFlights() {
    if (isPay) {
        searchFlights();  // 调用 searchFlights 函数
        isPay = false;    // 置为 false，防止重复调用
    }
}
