#include "flightmngwidget.h"
#include <algorithm> // 包含 std::sort
FlightmngWidget::FlightmngWidget(QWidget *parent)
    :  QWidget(parent), departureInput(nullptr), destinationInput(nullptr),
    addressListOpt(new QListWidget(this)), addressListOpt2(new QListWidget(this)),
    datePicker(new QDateEdit(QDateTime::currentDateTime().date(), this))
{
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
    // 连接失去焦点信号到隐藏地址列表的槽。
    connect(filter, &MyEventFilter::focusOut, this,
            [=]() { hideAddressListIfApplicable(departureInput); });
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
    connect(filter2, &MyEventFilter::focusOut, this,
            [=]() { hideAddressListIfApplicable(destinationInput); });
    QPushButton *switchButton = new QPushButton("切换", this);
    queryLayout->addWidget(switchButton, 0, 2);
    connect(switchButton, &QPushButton::clicked, this, &FlightmngWidget::swapDepartureAndDestination);

    queryLayout->addWidget(new QLabel("日期:"), 0, 5);
    datePicker->setCalendarPopup(true);
    queryLayout->addWidget(datePicker, 0, 6);
    // 假设确认按钮是最后一个添加到queryLayout的部件
    QPushButton *confirmButton = new QPushButton("确认");
    queryLayout->addWidget(confirmButton, 0, 7);

    contentLayout->addLayout(queryLayout);

    // 创建水平布局
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    // 创建新增航班按钮
    addFlightButton = new QPushButton("+新增航班", this);

    // 连接新增航班按钮的点击事件
    connect(addFlightButton, &QPushButton::clicked, this, &FlightmngWidget::showAddFlightWidget);

    buttonLayout->addWidget(addFlightButton);  // 将按钮添加到水平布局的左侧
    // 设置按钮的对齐方式为左对齐
    buttonLayout->setAlignment(addFlightButton, Qt::AlignLeft);
    addFlightButton->setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FF9800, stop:1 #FFB74D);"
        "color: white;"
        "border-radius: 8px;"
        "font-size: 12px;"
        "font-weight: bold;"
        "padding: 3px 8px;"
        "width: 70px;"
        "border: none;"
        "}"
        "QPushButton:hover {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FFB74D, stop:1 #FFCC80);"
        "}"
        "QPushButton:pressed {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #F57C00, stop:1 #FF6F00);"
        "}");
    // 添加按钮布局到垂直布局中
    contentLayout->addLayout(buttonLayout);
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

    // 加载所有航班信息
    loadFlightsFromDatabase();

    // 对所有航班信息按照出发时间进行排序
    sortFlightsByDepartureTime();
    // 将所有航班信息添加到滚动页面上
    populateScrollAreaWithFlights();

    // 连接确认按钮点击信号到槽函数
    connect(confirmButton, &QPushButton::clicked, this, &FlightmngWidget::onConfirmButtonClicked);


    // 设置默认布局间距和边距
    contentLayout->setContentsMargins(10, 10, 10, 10);
    queryLayout->setSpacing(5);
}
FlightmngWidget::~FlightmngWidget(){};

void FlightmngWidget::toggleAddressListVisibility(QLineEdit *input, QListWidget *list) {
    QPoint globalPos = input->mapToGlobal(QPoint(0, input->height()));
    list->move(globalPos);
    list->resize(input->width(), list->sizeHint().height());
    list->setVisible(!list->isVisible());
}

void FlightmngWidget::setAddressFromList(QLineEdit *input, QListWidget *list, QListWidgetItem *item) {
    input->setText(item->text());
    list->hide();
}

void FlightmngWidget::hideAddressListIfApplicable(QLineEdit *input) {
    if (input == departureInput) {
        addressListOpt->hide();
    } else if (input == destinationInput) {
        addressListOpt2->hide();
    }
}
void FlightmngWidget::swapDepartureAndDestination() {
    QString temp = departureInput->text();
    departureInput->setText(destinationInput->text());
    destinationInput->setText(temp);
}

/// @brief 从数据库加载所有航班信息到 allFlights 成员变量中。
void FlightmngWidget::loadFlightsFromDatabase() {
    QSqlQuery query;
    query.exec("SELECT * FROM Flights");

    if(!allFlights.empty()){
        allFlights.clear();
    }
    while (query.next()) {
        FlightData data;
        data.flight_id = query.value("flight_id").toInt();
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

        allFlights.append(data);
    }
}


/// @brief 当用户点击确认按钮时调用此槽函数，根据输入筛选航班信息并更新滚动区域。
void FlightmngWidget::onConfirmButtonClicked() {
    QString departure = departureInput->text(); // 获取出发地输入框文本
    QString destination = destinationInput->text(); // 获取目的地输入框文本
    QDate date = datePicker->date(); // 获取日期选择器选定的日期

    // 清空当前滚动区域内容
    QLayoutItem* item;
    while ((item = scrollContentLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    flightInfoWidgets.clear(); // 清空航班信息部件列表

    // 确保所有添加的 widget 在布局中顶部对齐
    scrollContentLayout->setAlignment(Qt::AlignTop); // 设置布局内容顶部对齐

    // 根据输入筛选航班信息
    for (auto &flight : allFlights) {
        if (flight.departure_city == departure &&
            flight.arrival_city == destination &&
            flight.departure_time.date() == date) {
            // 如果航班匹配用户输入，则创建新的 flightinfomng 实例并添加到滚动区域
            flightinfomng *infoWidget = new flightinfomng(flight, scrollContentWidget);
            connect (infoWidget,&flightinfomng::iscanceled,this,&FlightmngWidget::onConfirmButtonClicked);
            scrollContentLayout->addWidget(infoWidget);
            flightInfoWidgets.append(infoWidget);
        }
    }

    // 如果没有匹配的航班，显示提示信息
    if (flightInfoWidgets.isEmpty()) {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("提示");
        msgBox.setText("抱歉，没有找到匹配的航班");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();

        if (ret == QMessageBox::Ok) {
            // 用户点击了确定按钮后可执行的操作
        }
    }
}

/// @brief 按照出发时间递增排序 allFlights 成员变量。
void FlightmngWidget::sortFlightsByDepartureTime() {
    std::sort(allFlights.begin(), allFlights.end(),
              [](const FlightData &a, const FlightData &b) {
                  return a.departure_time < b.departure_time;
              });
}

/// @brief 将所有航班信息添加到滚动页面上。
void FlightmngWidget::populateScrollAreaWithFlights() {
    // 清空当前滚动区域内容
    QLayoutItem* item;
    while ((item = scrollContentLayout->takeAt(0)) != nullptr) {
        delete item->widget(); // 删除部件
        delete item; // 删除布局项
    }
    flightInfoWidgets.clear(); // 清空航班信息部件列表

    // 如果 allFlights 为空，直接返回，避免不必要的操作
    if (allFlights.isEmpty()) {
        return;
    }

    // 确保所有添加的 widget 在布局中顶部对齐
    scrollContentLayout->setAlignment(Qt::AlignTop); // 设置布局内容顶部对齐

    // 将所有航班信息添加到滚动页面上
    for (auto &flight : allFlights) {
        flightinfomng *infoWidget = new flightinfomng(flight, scrollContentWidget);
        connect (infoWidget,&flightinfomng::iscanceled,this,&FlightmngWidget::handlecancel);
        scrollContentLayout->addWidget(infoWidget);
        flightInfoWidgets.append(infoWidget);
    }
}
void FlightmngWidget::handlecancel(const FlightData& data)
{
    auto it = std::find_if(allFlights.begin(), allFlights.end(), [&data](const FlightData& flight) {
        return flight == data;
    });

    if (it != allFlights.end()) {
        // 如果找到匹配的航班，则调用处理取消逻辑
        allFlights.erase(it); // 从容器中移除该航班
        populateScrollAreaWithFlights();
        // 弹出消息框提示删除成功
        // 弹出消息框提示删除成功
        QMessageBox::information(this, tr("成功"), tr("航班取消成功。"));
    } else {
        qDebug() << "No matching flight found for cancellation.";
    }


}


void FlightmngWidget::showAddFlightWidget() {
    AddFlightWidget *addFlightWidget = new AddFlightWidget(nullptr);
    addFlightWidget->setWindowTitle("新增航班");
    addFlightWidget->setWindowModality(Qt::ApplicationModal);  // 设置为模态窗口
    connect(addFlightWidget, &AddFlightWidget::flightAdded, this, &FlightmngWidget::refreshFlightList); // 连接信号
    addFlightWidget->show();
}

void FlightmngWidget::refreshFlightList() {
    // 重新加载航班数据
    loadFlightsFromDatabase();
    // 对航班数据进行排序
    sortFlightsByDepartureTime();
    // 刷新界面
    populateScrollAreaWithFlights();
}
