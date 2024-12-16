#include "flightmngwidget.h"

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
