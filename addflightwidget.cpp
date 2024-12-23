#include "addflightwidget.h"
#include <QMessageBox> // 用于显示提示窗口
#include <QDateTime> // 包含 QDateTime 头文件
#include <QLabel>

AddFlightWidget::AddFlightWidget(QWidget *parent) : QWidget(parent) {

    QVBoxLayout* mainLayout=new QVBoxLayout(this);
    QGridLayout *layout = new QGridLayout(this);

    // 设置窗口大小为 800x600
    this->resize(600, 600);

    QFrame *topFrame=new QFrame(this);
    // 最上方的框架
    topFrame->setFrameShape(QFrame::StyledPanel);
    topFrame->setFrameShadow(QFrame::Raised);
    // 设置 topFrame 样式表
    topFrame->setStyleSheet(
        "background: qlineargradient("
        "    spread:pad, x1:0, y1:0, x2:1, y2:1, "
        "    stop:0 #E0E7FF, stop:1 #C1D4FF);" // 渐变背景：浅蓝到深蓝
        "border-bottom: 2px solid #A4B8FF;"    // 下边框为深浅蓝
        "border-radius: 15px;"                // 设置圆角，半径为 15px
        );
    QVBoxLayout *topLayout = new QVBoxLayout(topFrame);
    QLabel *headerLabel=new QLabel("新增航班");
    topLayout->addWidget(headerLabel, 0, Qt::AlignCenter);
    headerLabel->setStyleSheet(
        "font-size: 24px;"           // 主标题字体更大
        "font-weight: bold;"         // 设置为粗体
        "color: #625AFF;"            // 主标题颜色为紫色
        "padding: 10px 0px;"         // 上下内边距
        "text-align: center;"        // 文本水平居中
        "border: none;"              // 移除边框
        "background: transparent;"   // 设置背景为透明
        );
    mainLayout->addWidget(topFrame);


    // 航空公司
    airlineComboBox = new QComboBox();
    airlineComboBox->addItems({
        "中国东方航空",  // China Eastern
        "中国国际航空",  // Air China
        "中国南方航空",  // China Southern
        "海南航空"       // Hainan Airlines
    }); // 添加航空公司样例
    airlineComboBox->setFixedWidth(150);
    airlineComboBox->setCurrentIndex(-1); // 移除默认显示值


    // 出发地和目的地
    departureCity = new QComboBox();
    departureCity->addItems({        "北京", "上海", "广州", "深圳", "杭州",
                             "天津", "重庆", "南京", "武汉", "成都",
                             "西安", "苏州", "大连", "青岛", "宁波",
                             "厦门", "长沙", "沈阳", "哈尔滨", "济南",
                             "无锡", "福州", "昆明", "石家庄", "合肥",
                             "郑州", "乌鲁木齐", "南昌", "南宁", "兰州",
                             "银川", "呼和浩特", "海口", "贵阳", "西宁",
                             "台北", "香港", "澳门", "珠海", "东莞",
                             "佛山", "中山", "嘉兴", "泰州", "金华"});
    departureCity->setFixedWidth(150);
    departureCity->setCurrentIndex(-1); // 移除默认显示值

    destinationCity = new QComboBox();
    destinationCity->addItems({        "北京", "上海", "广州", "深圳", "杭州",
                               "天津", "重庆", "南京", "武汉", "成都",
                               "西安", "苏州", "大连", "青岛", "宁波",
                               "厦门", "长沙", "沈阳", "哈尔滨", "济南",
                               "无锡", "福州", "昆明", "石家庄", "合肥",
                               "郑州", "乌鲁木齐", "南昌", "南宁", "兰州",
                               "银川", "呼和浩特", "海口", "贵阳", "西宁",
                               "台北", "香港", "澳门", "珠海", "东莞",
                               "佛山", "中山", "嘉兴", "泰州", "金华"});
    destinationCity->setFixedWidth(150);
    destinationCity->setCurrentIndex(-1); // 移除默认显示值

    // 出发和到达时间
    departureTime = new QDateTimeEdit();
    departureTime->setDisplayFormat("yyyy-MM-dd HH:mm");
    departureTime->setCalendarPopup(true); // 允许用户选择日期
    departureTime->setButtonSymbols(QAbstractSpinBox::NoButtons); // 隐藏上下箭头
    departureTime->setFixedWidth(150);
    departureTime->setDateTime(QDateTime::currentDateTime()); // 设置为当前时间

    arrivalTime = new QDateTimeEdit();
    arrivalTime->setDisplayFormat("yyyy-MM-dd HH:mm");
    arrivalTime->setCalendarPopup(true); // 允许用户选择日期
    arrivalTime->setButtonSymbols(QAbstractSpinBox::NoButtons); // 隐藏上下箭头
    arrivalTime->setFixedWidth(150);
    arrivalTime->setDateTime(QDateTime::currentDateTime()); // 设置为当前时间

    // 航班编号
    flightNumberEdit = new QLineEdit();
    flightNumberEdit->setPlaceholderText("请输入航班编号");
    flightNumberEdit->setFixedWidth(150);

    // 飞机型号
    airplaneModel = new QComboBox();
    airplaneModel->addItems({"Boeing 737", "Airbus A320", "C919", "ARJ21"});
    airplaneModel->setFixedWidth(150);
    airplaneModel->setCurrentIndex(-1); // 移除默认显示值

    // 出发地机场
    departureAirport = new QLineEdit();
    departureAirport->setPlaceholderText("请输入出发机场");
    departureAirport->setFixedWidth(150);

    // 目的地机场
    arrivalAirport = new QLineEdit();
    arrivalAirport->setPlaceholderText("请输入出发机场");
    arrivalAirport->setFixedWidth(150);

    // 出发地和目的地的航站楼
    departureTerminal = new QComboBox();
    departureTerminal->addItems({"T1", "T2", "T3", "T4"});
    departureTerminal->setFixedWidth(100);
    departureTerminal->setCurrentIndex(-1); // 移除默认显示值

    arrivalTerminal = new QComboBox();
    arrivalTerminal->addItems({"T1", "T2", "T3", "T4"});
    arrivalTerminal->setFixedWidth(100);
    arrivalTerminal->setCurrentIndex(-1); // 移除默认显示值

    // 经济舱、商务舱、头等舱的座位容量、剩余座位和价格
    economyCapacity = new QSpinBox();
    economyCapacity->setRange(0, 1000);
    economyCapacity->setValue(150); // 设置初始值为 150
    economyCapacity->setFixedWidth(100); // 设置输入框宽度

    economyAvailable = new QSpinBox();
    economyAvailable->setRange(0, 1000);
    economyAvailable->setValue(140); // 设置初始值为 140
    economyAvailable->setFixedWidth(100); // 设置输入框宽度

    economyPrice = new QSpinBox();
    economyPrice->setRange(0,100000);
    economyPrice->setValue(500);
    economyPrice->setFixedWidth(100); // 设置输入框宽度

    businessCapacity = new QSpinBox();
    businessCapacity->setRange(0, 1000);
    businessCapacity->setValue(30); // 设置初始值为 30
    businessCapacity->setFixedWidth(100); // 设置输入框宽度

    businessAvailable = new QSpinBox();
    businessAvailable->setRange(0, 1000);
    businessAvailable->setValue(25); // 设置初始值为 25
    businessAvailable->setFixedWidth(100); // 设置输入框宽度

    businessPrice = new QSpinBox();
    businessPrice->setRange(0,100000);
    businessPrice->setValue(1000);
    businessPrice->setFixedWidth(100); // 设置输入框宽度

    firstClassCapacity = new QSpinBox();
    firstClassCapacity->setRange(0, 1000);
    firstClassCapacity->setValue(10); // 设置初始值为 10
    firstClassCapacity->setFixedWidth(100); // 设置输入框宽度

    firstClassAvailable = new QSpinBox();
    firstClassAvailable->setRange(0, 1000);
    firstClassAvailable->setValue(8); // 设置初始值为 8
    firstClassAvailable->setFixedWidth(100); // 设置输入框宽度

    firstClassPrice = new QSpinBox();
    firstClassPrice->setRange(0,100000);
    firstClassPrice->setValue(2000);
    firstClassPrice->setFixedWidth(100); // 设置输入框宽度

    // 提交按钮
    QPushButton *submitButton = new QPushButton("提交");
    submitButton->setFixedWidth(100); // 设置按钮宽度
    submitButton->setFixedHeight(30); // 设置按钮宽度

    // 设置按钮的样式表，背景颜色为浅蓝色
    submitButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4169E1; /* 浅蓝色 */"
        "    color: white; /* 文字颜色为白色 */"
        "    border-radius: 5px; /* 圆角 */"
        "    padding: 5px 10px; /* 内边距 */"
        "}"
        "QPushButton:hover {"
        "    background-color: #00BFFF; /* 悬停时颜色稍深 */"
        "}"
        "QPushButton:pressed {"
        "    background-color: #000080; /* 按下时颜色更深 */"
        "}"
        );

    // 添加控件到布局

    // 航空公司标签和选择框
    QLabel *airlineLabel = new QLabel("航空公司:");
    airlineLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(airlineLabel, 0, 0, Qt::AlignRight);
    layout->addWidget(airlineComboBox, 0, 1, Qt::AlignLeft);

    // 出发地标签和选择框
    QLabel *departureLabel = new QLabel("出发地:");
    departureLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(departureLabel, 1, 0, Qt::AlignRight);
    layout->addWidget(departureCity, 1, 1, Qt::AlignLeft);

    // 目的地标签和选择框
    QLabel *destinationLabel = new QLabel("目的地:");
    destinationLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(destinationLabel, 2, 0, Qt::AlignRight);
    layout->addWidget(destinationCity, 2, 1, Qt::AlignLeft);

    // 出发时间标签和输入框
    QLabel *departureTimeLabel = new QLabel("出发时间:");
    departureTimeLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(departureTimeLabel, 3, 0, Qt::AlignRight);
    layout->addWidget(departureTime, 3, 1, Qt::AlignLeft);

    // 到达时间标签和输入框
    QLabel *arrivalTimeLabel = new QLabel("到达时间:");
    arrivalTimeLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(arrivalTimeLabel, 4, 0, Qt::AlignRight);
    layout->addWidget(arrivalTime, 4, 1, Qt::AlignLeft);

    // 航班编号标签和输入框
    QLabel *flightNumberLabel = new QLabel("航班编号:");
    flightNumberLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(flightNumberLabel, 5, 0, Qt::AlignRight);
    layout->addWidget(flightNumberEdit, 5, 1, Qt::AlignLeft);

    // 飞机型号标签和选择框
    QLabel *airplaneModelLabel = new QLabel("飞机型号:");
    airplaneModelLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(airplaneModelLabel, 6, 0, Qt::AlignRight);
    layout->addWidget(airplaneModel, 6, 1, Qt::AlignLeft);

    // 出发机场标签和输入框
    QLabel *departureAirportLabel = new QLabel("出发机场:");
    departureAirportLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(departureAirportLabel, 7, 0, Qt::AlignRight);
    layout->addWidget(departureAirport, 7, 1, Qt::AlignLeft);

    // 到达机场标签和输入框
    QLabel *arrivalAirportLabel = new QLabel("到达机场:");
    arrivalAirportLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(arrivalAirportLabel, 8, 0, Qt::AlignRight);
    layout->addWidget(arrivalAirport, 8, 1, Qt::AlignLeft);

    // 出发航站楼标签和选择框
    QLabel *departureTerminalLabel = new QLabel("出发航站楼:");
    departureTerminalLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(departureTerminalLabel, 9, 0, Qt::AlignRight);
    layout->addWidget(departureTerminal, 9, 1, Qt::AlignLeft);

    // 到达航站楼标签和选择框
    QLabel *arrivalTerminalLabel = new QLabel("到达航站楼:");
    arrivalTerminalLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(arrivalTerminalLabel, 10, 0, Qt::AlignRight);
    layout->addWidget(arrivalTerminal, 10, 1, Qt::AlignLeft);

    // 经济舱座位容量标签和输入框
    QLabel *economyCapacityLabel = new QLabel("经济舱座位容量:");
    economyCapacityLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(economyCapacityLabel, 11, 0, Qt::AlignRight);
    layout->addWidget(economyCapacity, 11, 1, Qt::AlignLeft);

    // 经济舱剩余座位标签和输入框
    QLabel *economyAvailableLabel = new QLabel("经济舱剩余座位:");
    economyAvailableLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(economyAvailableLabel, 12, 0, Qt::AlignRight);
    layout->addWidget(economyAvailable, 12, 1, Qt::AlignLeft);

    // 经济舱价格标签和输入框
    QLabel *economyPriceLabel = new QLabel("经济舱价格:");
    economyPriceLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(economyPriceLabel, 13, 0, Qt::AlignRight);
    layout->addWidget(economyPrice, 13, 1, Qt::AlignLeft);

    // 商务舱座位容量标签和输入框
    QLabel *businessCapacityLabel = new QLabel("商务舱座位容量:");
    businessCapacityLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(businessCapacityLabel, 14, 0, Qt::AlignRight);
    layout->addWidget(businessCapacity, 14, 1, Qt::AlignLeft);

    // 商务舱剩余座位标签和输入框
    QLabel *businessAvailableLabel = new QLabel("商务舱剩余座位:");
    businessAvailableLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(businessAvailableLabel, 15, 0, Qt::AlignRight);
    layout->addWidget(businessAvailable, 15, 1, Qt::AlignLeft);

    // 商务舱价格标签和输入框
    QLabel *businessPriceLabel = new QLabel("商务舱价格:");
    businessPriceLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(businessPriceLabel, 16, 0, Qt::AlignRight);
    layout->addWidget(businessPrice, 16, 1, Qt::AlignLeft);

    // 头等舱座位容量标签和输入框
    QLabel *firstClassCapacityLabel = new QLabel("头等舱座位容量:");
    firstClassCapacityLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(firstClassCapacityLabel, 17, 0, Qt::AlignRight);
    layout->addWidget(firstClassCapacity, 17, 1, Qt::AlignLeft);

    // 头等舱剩余座位标签和输入框
    QLabel *firstClassAvailableLabel = new QLabel("头等舱剩余座位:");
    firstClassAvailableLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(firstClassAvailableLabel, 18, 0, Qt::AlignRight);
    layout->addWidget(firstClassAvailable, 18, 1, Qt::AlignLeft);

    // 头等舱价格标签和输入框
    QLabel *firstClassPriceLabel = new QLabel("头等舱价格:");
    firstClassPriceLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(firstClassPriceLabel, 19, 0, Qt::AlignRight);
    layout->addWidget(firstClassPrice, 19, 1, Qt::AlignLeft);

    layout->addWidget(submitButton, 20, 0, 1, 2, Qt::AlignCenter); // 提交按钮居中

    // 设置列宽，确保文字和输入框之间的间距更大
    layout->setColumnMinimumWidth(0, 120); // 第一列（文字）宽度
    layout->setColumnMinimumWidth(1, 200); // 第二列（输入框）宽度

    // 初始化机场选择
    connect(departureCity, &QComboBox::currentTextChanged, this, &AddFlightWidget::updateDepartureAirports);
    connect(destinationCity, &QComboBox::currentTextChanged, this, &AddFlightWidget::updateArrivalAirports);
    connect(submitButton, &QPushButton::clicked, this, &AddFlightWidget::submitFlight);

    mainLayout->addLayout(layout);
}

void AddFlightWidget::submitFlight() {

    // 检查所有输入框是否为空，并将未填写的输入框边框颜色设置为淡红色
    bool allFieldsFilled = true;

    // 检查航空公司是否为空
    if (airlineComboBox->currentText().isEmpty()) {
        airlineComboBox->setStyleSheet("border: 2px solid #FFCCCC;"); // 设置边框颜色为淡红色
        allFieldsFilled = false;
    } else {
        airlineComboBox->setStyleSheet(""); // 恢复默认样式
    }

    if (departureCity->currentText().isEmpty()) {
        departureCity->setStyleSheet("border: 2px solid #FFCCCC;");
        allFieldsFilled = false;
    } else {
        departureCity->setStyleSheet(""); // 恢复默认样式
    }

    if (destinationCity->currentText().isEmpty()) {
        destinationCity->setStyleSheet("border: 2px solid #FFCCCC;");
        allFieldsFilled = false;
    } else {
        destinationCity->setStyleSheet("");
    }

    if (departureTime->dateTime().isNull()) {
        departureTime->setStyleSheet("border: 2px solid #FFCCCC;");
        allFieldsFilled = false;
    } else {
        departureTime->setStyleSheet("");
    }

    if (arrivalTime->dateTime().isNull()) {
        arrivalTime->setStyleSheet("border: 2px solid #FFCCCC;");
        allFieldsFilled = false;
    } else {
        arrivalTime->setStyleSheet("");
    }

    if (flightNumberEdit->text().isEmpty()) {
        flightNumberEdit->setStyleSheet("border: 2px solid #FFCCCC;"); // 设置边框颜色为淡红色
        allFieldsFilled = false;
    } else {
        flightNumberEdit->setStyleSheet(""); // 恢复默认样式
    }


    if (airplaneModel->currentText().isEmpty()) {
        airplaneModel->setStyleSheet("border: 2px solid #FFCCCC;");
        allFieldsFilled = false;
    } else {
        airplaneModel->setStyleSheet("");
    }

    if (departureAirport->text().isEmpty()) {
        departureAirport->setStyleSheet("border: 2px solid #FFCCCC;");
        allFieldsFilled = false;
    } else {
        departureAirport->setStyleSheet("");
    }

    if (arrivalAirport->text().isEmpty()) {
        arrivalAirport->setStyleSheet("border: 2px solid #FFCCCC;");
        allFieldsFilled = false;
    } else {
        arrivalAirport->setStyleSheet("");
    }

    if (departureTerminal->currentText().isEmpty()) {
        departureTerminal->setStyleSheet("border: 2px solid #FFCCCC;");
        allFieldsFilled = false;
    } else {
        departureTerminal->setStyleSheet("");
    }

    if (arrivalTerminal->currentText().isEmpty()) {
        arrivalTerminal->setStyleSheet("border: 2px solid #FFCCCC;");
        allFieldsFilled = false;
    } else {
        arrivalTerminal->setStyleSheet("");
    }

    if (economyPrice->text().isEmpty()) {
        economyPrice->setStyleSheet("border: 2px solid #FFCCCC;");
        allFieldsFilled = false;
    } else {
        economyPrice->setStyleSheet("");
    }

    if (businessPrice->text().isEmpty()) {
        businessPrice->setStyleSheet("border: 2px solid #FFCCCC;");
        allFieldsFilled = false;
    } else {
        businessPrice->setStyleSheet("");
    }

    if (firstClassPrice->text().isEmpty()) {
        firstClassPrice->setStyleSheet("border: 2px solid #FFCCCC;");
        allFieldsFilled = false;
    } else {
        firstClassPrice->setStyleSheet("");
    }

    // 如果所有字段都已填写，则继续检查时间
    if (!allFieldsFilled) {
        QMessageBox::warning(this, "错误", "请填写完必要信息！");
        return; // 阻止数据导入数据库
    }

    // 检查出发地和到达地是否相同
    if (departureCity->currentText() == destinationCity->currentText()) {
        QMessageBox::warning(this, "错误", "出发地和到达地不能相同，请重新输入！");
        departureCity->setStyleSheet("border: 2px solid #FFCCCC;");
        destinationCity->setStyleSheet("border: 2px solid #FFCCCC;");
        return; // 阻止数据导入数据库
    } else {
        departureCity->setStyleSheet("");
        destinationCity->setStyleSheet("");
    }

    // 获取当前的 QDateTime 并将其秒和毫秒设为 0，以确保只比较到分钟
    QDateTime roundedArrival = arrivalTime->dateTime();
    roundedArrival.setTime(QTime(roundedArrival.time().hour(), roundedArrival.time().minute(), 0, 0));

    QDateTime roundedDeparture = departureTime->dateTime();
    roundedDeparture.setTime(QTime(roundedDeparture.time().hour(), roundedDeparture.time().minute(), 0, 0));

    if (roundedArrival <= roundedDeparture) {
        QMessageBox::warning(this, "时间错误", "到达时间必须在出发时间之后，请重新输入！");
        // 设置边框颜色
        departureTime->setStyleSheet("border: 2px solid #FFCCCC;");
        arrivalTime->setStyleSheet("border: 2px solid #FFCCCC;");
        return; // 阻止数据导入数据库
    } else {
        // 恢复默认样式
        departureTime->setStyleSheet("");
        arrivalTime->setStyleSheet("");
    }

    // 检查经济舱、商务舱、头等舱的剩余座位是否大于座位容量
    if (economyAvailable->value() > economyCapacity->value()) {
        QMessageBox::warning(this, "错误", "经济舱剩余座位不能大于座位容量！");
        economyAvailable->setStyleSheet("border: 2px solid #FFCCCC;");
        return; // 阻止数据导入数据库
    } else {
        economyAvailable->setStyleSheet("");
    }

    if (businessAvailable->value() > businessCapacity->value()) {
        QMessageBox::warning(this, "错误", "商务舱剩余座位不能大于座位容量！");
        businessAvailable->setStyleSheet("border: 2px solid #FFCCCC;");
        return; // 阻止数据导入数据库
    } else {
        businessAvailable->setStyleSheet("");
    }

    if (firstClassAvailable->value() > firstClassCapacity->value()) {
        QMessageBox::warning(this, "错误", "头等舱剩余座位不能大于座位容量！");
        firstClassAvailable->setStyleSheet("border: 2px solid #FFCCCC;");
        return; // 阻止数据导入数据库
    } else {
        firstClassAvailable->setStyleSheet("");
    }


    // 获取用户输入的数据
    QString airline = airlineComboBox->currentText();
    QString flightNumber =  flightNumberEdit->text();
    QString airplane = airplaneModel->currentText();
    QString departure = departureCity->currentText();
    QString departureAir = departureAirport->text(); // 获取用户输入的出发机场
    QString arrival = destinationCity->currentText();
    QString arrivalAir = arrivalAirport->text(); // 获取用户输入的到达机场
    QString departureTerm = departureTerminal->currentText();
    QString arrivalTerm = arrivalTerminal->currentText();
    QDateTime departTime = departureTime->dateTime();
    QDateTime arriveTime = arrivalTime->dateTime();
    int economyCap = economyCapacity->value();
    int economyAvail = economyAvailable->value();
    double economyP = economyPrice->text().toDouble();
    int businessCap = businessCapacity->value();
    int businessAvail = businessAvailable->value();
    double businessP = businessPrice->text().toDouble();
    int firstClassCap = firstClassCapacity->value();
    int firstClassAvail = firstClassAvailable->value();
    double firstClassP = firstClassPrice->text().toDouble();

    qint64 secondsDifference = departTime.secsTo(arriveTime);
    QTime duration = QTime(0, 0).addSecs(secondsDifference);

    // 判断是否为同日到达（same_day_arrival）
    bool sameDayArrival = (departTime.date() == arriveTime.date());


    if (secondsDifference >= 24 * 3600) {
        QMessageBox::warning(this, "时间错误", "到达时间不能比出发时间晚超过24小时，请重新输入！");
        // 将出发时间和到达时间的边框颜色设置为淡红色
        departureTime->setStyleSheet("border: 2px solid #FFCCCC;");
        arrivalTime->setStyleSheet("border: 2px solid #FFCCCC;");
        return; // 阻止数据导入数据库
    } else {
        // 如果时间正确，恢复默认样式
        departureTime->setStyleSheet("");
        arrivalTime->setStyleSheet("");
    }


    // 插入数据到数据库
    QSqlQuery query;
    query.prepare("INSERT INTO Flights (flight_number, airline, airplane_model, departure_city, departure_airport, arrival_city, arrival_airport, departure_terminal, arrival_terminal, departure_time, arrival_time, economy_seat_capacity, economy_available_seats, economy_price, business_seat_capacity, business_available_seats, business_price, first_class_seat_capacity, first_class_available_seats, first_class_price, duration, same_day_arrival) "
                  "VALUES (:flight_number, :airline, :airplane_model, :departure_city, :departure_airport, :arrival_city, :arrival_airport, :departure_terminal, :arrival_terminal, :departure_time, :arrival_time, :economy_seat_capacity, :economy_available_seats, :economy_price, :business_seat_capacity, :business_available_seats, :business_price, :first_class_seat_capacity, :first_class_available_seats, :first_class_price, :duration, :same_day_arrival)");
    query.bindValue(":flight_number", flightNumber);
    query.bindValue(":airline", airline);
    query.bindValue(":airplane_model", airplane);
    query.bindValue(":departure_city", departure);
    query.bindValue(":departure_airport", departureAir);
    query.bindValue(":arrival_city", arrival);
    query.bindValue(":arrival_airport", arrivalAir);
    query.bindValue(":departure_terminal", departureTerm);
    query.bindValue(":arrival_terminal", arrivalTerm);
    query.bindValue(":departure_time", departTime);
    query.bindValue(":arrival_time", arriveTime);
    query.bindValue(":economy_seat_capacity", economyCap);
    query.bindValue(":economy_available_seats", economyAvail);
    query.bindValue(":economy_price", economyP);
    query.bindValue(":business_seat_capacity", businessCap);
    query.bindValue(":business_available_seats", businessAvail);
    query.bindValue(":business_price", businessP);
    query.bindValue(":first_class_seat_capacity", firstClassCap);
    query.bindValue(":first_class_available_seats", firstClassAvail);
    query.bindValue(":first_class_price", firstClassP);
    query.bindValue(":duration", duration.toString("hh:mm:ss")); // 绑定历时
    query.bindValue(":same_day_arrival", sameDayArrival); // 绑定是否为同日到达

    if (query.exec()) {
        QMessageBox::information(this, "成功", "航班信息已成功添加到数据库！");
        emit flightAdded(); // 发送信号，通知航班已添加
        this->close(); // 关闭窗口
    } else {
        QMessageBox::critical(this, "错误", "无法添加航班信息：" + query.lastError().text());
    }
}

void AddFlightWidget::updateDepartureAirports(const QString &city) {
    departureAirport->clear();
    if (city == "北京") {
        departureAirport->setText("首都国际机场"); // 默认值
    } else if (city == "上海") {
        departureAirport->setText("浦东国际机场"); // 默认值
    } else if (city == "广州") {
        departureAirport->setText("白云国际机场"); // 默认值
    } else if (city == "深圳") {
        departureAirport->setText("宝安国际机场"); // 默认值
    } else if (city == "成都") {
        departureAirport->setText("双流国际机场"); // 默认值
    }
}

void AddFlightWidget::updateArrivalAirports(const QString &city) {
    arrivalAirport->clear();
    if (city == "北京") {
        arrivalAirport->setText("首都国际机场"); // 默认值
    } else if (city == "上海") {
        arrivalAirport->setText("浦东国际机场"); // 默认值
    } else if (city == "广州") {
        arrivalAirport->setText("白云国际机场"); // 默认值
    } else if (city == "深圳") {
        arrivalAirport->setText("宝安国际机场"); // 默认值
    } else if (city == "成都") {
        arrivalAirport->setText("双流国际机场"); // 默认值
    }
}




