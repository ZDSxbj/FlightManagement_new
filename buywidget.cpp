#include "buywidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include<QMessageBox>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include<QSqlQuery>
#include <QInputDialog>

//乘机人card的类的实现
PassengerWidget::PassengerWidget(QWidget *parent)
    : QWidget(parent)
{

    // 序号
    indexLabel = new QLabel(this);
    indexLabel->setStyleSheet("font-size: 30px; font-weight: bold;");

    // 设置标签
    QLabel *nameLabel = new QLabel("姓名:", this);
    nameLabel->setStyleSheet("font-size: 16px;");  // 设置字体大小

    QLabel *idCardLabel = new QLabel("身份证:", this);
    idCardLabel->setStyleSheet("font-size: 16px;");

    QLabel *phoneLabel = new QLabel("电话号码:", this);
    phoneLabel->setStyleSheet("font-size: 16px;");

    // 设置输入框
    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("请输入姓名");
    nameEdit->setStyleSheet("font-size: 14px;");  // 输入框字体大小
    nameEdit->setFixedHeight(27);  // 设置输入框高度

    idCardEdit = new QLineEdit(this);
    idCardEdit->setPlaceholderText("请输入身份证");
    idCardEdit->setStyleSheet("font-size: 14px;");
    idCardEdit->setFixedHeight(27);

    phoneEdit = new QLineEdit(this);
    phoneEdit->setPlaceholderText("请输入电话号码");
    phoneEdit->setStyleSheet("font-size: 14px;");
    phoneEdit->setFixedHeight(27);

    nameEdit->setFixedWidth(230);
    idCardEdit->setFixedWidth(230);
    phoneEdit->setFixedWidth(230);
    // 按钮
    confirmBtn = new QPushButton("确认", this);
    deleteBtn = new QPushButton("删除", this);
    // 设置按钮样式
    confirmBtn->setStyleSheet(R"(
    QPushButton {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #7F7EFF, stop:1 #9E8CFE); /* 渐变紫色背景 */
        color: white; /* 字体颜色为白色 */
        border-radius: 10px; /* 圆角按钮，边角更小 */
        font-size: 14px; /* 较小字体 */
        font-weight: bold; /* 字体加粗 */
        padding: 5px 10px; /* 较小内边距 */
        width: 60px; /* 按钮最小宽度 */
        border: none; /* 去除边框 */
    }
    QPushButton:hover {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #9E8CFE, stop:1 #BCA4FF); /* 悬停时更亮的渐变色 */
    }
    QPushButton:pressed {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #6D6CFF, stop:1 #8E7AFE); /* 按下时更深的渐变色 */
    }
)");

    deleteBtn->setStyleSheet(R"(
    QPushButton {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FFA07A, stop:1 #FF7F7F); /* 渐变浅红色背景 */
        color: white; /* 字体颜色为白色 */
        border-radius: 10px; /* 圆角按钮，边角更小 */
        font-size: 14px; /* 较小字体 */
        font-weight: bold; /* 字体加粗 */
        padding: 5px 10px; /* 较小内边距 */
        width: 60px; /* 按钮最小宽度 */
        border: none; /* 去除边框 */
    }
    QPushButton:hover {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FF7F7F, stop:1 #FF6F6F); /* 悬停时更亮的浅红色 */
    }
    QPushButton:pressed {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FF6F6F, stop:1 #FF5F5F); /* 按下时更深的红色 */
    }
)");
    // 布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addStretch(1);
    topLayout->addWidget(indexLabel);
     topLayout->addStretch(3);
    QGridLayout *inputLayout = new QGridLayout();
    inputLayout->addWidget(nameLabel, 0, 0);
    inputLayout->addWidget(nameEdit, 0, 1);
    inputLayout->addWidget(idCardLabel, 1, 0);
    inputLayout->addWidget(idCardEdit, 1, 1);
    inputLayout->addWidget(phoneLabel, 2, 0);
    inputLayout->addWidget(phoneEdit, 2, 1);

    topLayout->addLayout(inputLayout);
    topLayout->addStretch(3);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(confirmBtn);
    buttonLayout->addWidget(deleteBtn);

    mainLayout->addLayout(topLayout);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    // 设置固定高度为 200px

    setFixedHeight(180);
}

void PassengerWidget::setLabel(int index)
{
    // 设置 indexLabel 显示序号
    indexLabel->setText(QString::number(index));
}



//购买页面的定义
BuyWidget::BuyWidget(FlightData data,int type,QWidget *parent)
    : type(type),data(data), QWidget(parent),
    topFrame(new QFrame(this)),
    headerLabel(new QLabel("购票界面", topFrame)),
    addPassengerButton(new QPushButton("+新增乘计人", this)),
    scrollArea(new QScrollArea(this)),
    scrollWidget(new QWidget(scrollArea)),
    scrollLayout(new QVBoxLayout(scrollWidget)),
    totalPriceLabel(new QLabel("共需支付: 0 元", this)),  // 初始化总价标签
    payButton(new QPushButton("支付", this)),
    cancelButton(new QPushButton("取消", this)),
    bottomLayout(new QHBoxLayout())
{
    curUser="12345678";
    // 输出修改后的值
    qDebug() << "Modified curUser:" << curUser;
    switch (type) {
    case 1:
        seatPrice=data.economy_price;
        break;
    case 2:
        seatPrice=data.business_price;
        break;
    case 3:
        seatPrice=data.first_class_price;
        break;
    }
    resize(600,700);
    // 主垂直布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

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

    // “+新增乘车人”按钮
    addPassengerButton->setFixedWidth(110);  // 可以根据需要调整宽度

    addPassengerButton->setFixedHeight(25); // 设置固定高度，保证按钮看起来协调
    addPassengerButton->setStyleSheet(
        "QPushButton {"
        "font-size: 12px;"                // 字体大小
        "border-radius: 8px;"             // 圆角按钮
        "background: white;"              // 背景为白色
        "text-align: center;"
            "}"      // 文本居中
        "QPushButton:hover {"
        "background: #F5F5FF;"            // 鼠标悬停时背景变为浅紫
        "color: #4A47A3;"                 // 字体颜色变为深紫
        "border-color: #4A47A3;"          // 边框颜色变为深紫
        "}"
        "QPushButton:pressed {"
        "background: #E0E0FF;"            // 按下时背景变为淡紫色
        "color: #333399;"                 // 字体颜色变为更深的紫色
        "border-color: #333399;"          // 边框颜色变为更深的紫色
        "}"
        );
    addPassenger(); //一开始的时候就应该有一个填写乘机人信息
    connect(addPassengerButton, &QPushButton::clicked, this, &BuyWidget::addPassenger);
    mainLayout->addWidget(addPassengerButton, 0, Qt::AlignLeft);

    // 可滚动的乘车人列表区域
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    mainLayout->addWidget(scrollArea);

    // 支付和取消按钮的水平布局

    bottomLayout->addWidget(totalPriceLabel, 1, Qt::AlignLeft);  // 左侧添加总价标签
    bottomLayout->addWidget(payButton, 0, Qt::AlignRight);
    bottomLayout->addWidget(cancelButton, 0, Qt::AlignRight);
    payButton->setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FFC75F, stop:1 #FFA45B);" // 渐变橙黄色背景
        "color: white;" // 字体颜色为白色
        "border-radius: 15px;" // 圆角按钮，半径调整为15px
        "font-size: 14px;" // 字体稍小，14px
        "font-weight: bold;" // 字体加粗
        "padding: 8px 16px;" // 较小的内边距
        "min-width: 60px;" // 按钮最小宽度更小
        "border: none;" // 去除边框
        "}"
        "QPushButton:hover {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FFD56B, stop:1 #FFB56A);" // 悬停时更亮的橙黄色渐变
        "}"
        "QPushButton:pressed {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #E6A55C, stop:1 #D98E57);" // 按下时更深的橙黄色渐变
        "}"
        );

    cancelButton->setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #B0B0B0, stop:1 #A0A0A0);" // 渐变灰色背景
        "color: white;" // 字体颜色为白色
        "border-radius: 15px;" // 圆角按钮，半径调整为15px
        "font-size: 14px;" // 字体稍小，14px
        "font-weight: bold;" // 字体加粗
        "padding: 8px 16px;" // 较小的内边距
        "min-width: 60px;" // 按钮最小宽度更小
        "border: none;" // 去除边框
        "}"
        "QPushButton:hover {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #D1D1D1, stop:1 #C0C0C0);" // 悬停时更亮的灰色渐变
        "}"
        "QPushButton:pressed {"
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #A8A8A8, stop:1 #8F8F8F);" // 按下时更深的灰色渐变
        "}"
        );
    totalPriceLabel->setStyleSheet(
        "QLabel {"
        "color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FF7F29, stop:1 #FF9A3D);" // 明显的渐变效果
        "font-size: 20px;" // 字体大小适中
        "font-weight: bold;" // 字体加粗
        "border-radius: 15px;" // 圆角效果
        "padding: 10px;" // 适度的内边距
        "}"
        );
    connect(payButton, &QPushButton::clicked, this, &BuyWidget::onPayButtonClicked);
    // 点击取消按钮时关闭当前窗口
    connect(cancelButton, &QPushButton::clicked, this, &QWidget::deleteLater);
    mainLayout->addLayout(bottomLayout);
}

BuyWidget::~BuyWidget() {}


//设置总劲儿的函数
void BuyWidget::setPayment()
{
    // 计算总价格
    int passengerCount = passengerSet.size(); // 获取乘机人集合中的人数
    double totalPrice = passengerCount * seatPrice; // 总金额 = 人数 * 每座位价格

    // 设置到 QLabel 中
    totalPriceLabel->setText(QString("总金额: %1 元").arg(totalPrice, 0, 'f', 2)); // 保留两位小数

    qDebug() << "总金额已更新:" << totalPrice;
}
//删除按钮绑定的函数
void BuyWidget::removePassenger(PassengerWidget *passenger)
{
    // 检查是否已验证（输入框是否被禁用）
    if (!passenger->nameEdit->isEnabled()) {
        // 构造 PassengerInfo 对象
        PassengerInfo info{
                           passenger->nameEdit->text().trimmed(),
                           passenger->idCardEdit->text().trimmed(),
                           passenger->phoneEdit->text().trimmed()};

        // 从 set 中移除该乘机人
        if (passengerSet.remove(info)) {
            qDebug() << "已从乘机人集合中移除:" << info.name;
            setPayment();
        }
    }

    // 从数组中移除乘机人
    passengerWidgets.removeOne(passenger);

    // 删除该控件
    delete passenger;

    // 更新乘车人列表显示
    updatePassengerList();

    qDebug() << "删除乘机人，当前总人数:" << passengerWidgets.size();
}


//确定按钮绑定的函数
bool BuyWidget::validatePassengerInfo(PassengerWidget *passenger) {

    QString name = passenger->nameEdit->text().trimmed();
    QString idCard = passenger->idCardEdit->text().trimmed();
    QString phone = passenger->phoneEdit->text().trimmed();

    if (name.isEmpty() || idCard.isEmpty() || phone.isEmpty()) {
        QMessageBox::warning(this, "警告", "请填写完整且正确的信息！");
        return false;
    }

    // 在数据库中查询
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :name AND ID_card = :idCard AND phone = :phone");
    query.bindValue(":name", name);
    query.bindValue(":idCard", idCard);
    query.bindValue(":phone", phone);

    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "查询失败，请检查数据库连接！");
        return false;
    }

    if (query.next()) {
        // 检查是否已在 passengerSet 中
        PassengerInfo info{name, idCard, phone};
        if (passengerSet.contains(info)) {
            QMessageBox::warning(this, "警告", "请勿重复添加乘机人！");
            return false;
        }
        // 从数据库中的 Orders 查找是否已有相同航班的购票记录
        QSqlQuery orderQuery;
        orderQuery.prepare("SELECT * FROM Orders WHERE realname = :realname AND flight_number = :flightNumber AND departure_time = :departureTime");
        orderQuery.bindValue(":realname", name); // 当前用户的姓名
        orderQuery.bindValue(":flightNumber", data.flight_number); // 当前航班编号（QString）
        orderQuery.bindValue(":departureTime", data.departure_time); // 当前航班出发时间（QDateTime）

        if (!orderQuery.exec()) {
            QMessageBox::critical(this, "错误", "查询航班订单失败，请检查数据库连接！");
            return false;
        }

        if (orderQuery.next()) { // 如果查询结果有记录
            QMessageBox::warning(this, "警告", QString("用户 %1 已购买过此次航班机票！").arg(name));
            return false;
        }
        // 添加到 passengerSet
        passengerSet.insert(info);

        // 禁用输入框，防止继续编辑
        passenger->nameEdit->setEnabled(false);
        passenger->idCardEdit->setEnabled(false);
        passenger->phoneEdit->setEnabled(false);

        QMessageBox::information(this, "成功", "用户验证成功！");
        setPayment();
        return true;
    } else {
        QMessageBox::warning(this, "警告", "未找到匹配的用户，请检查输入信息！");
        return false;
    }
}


// 添加乘机人的操作
void BuyWidget::addPassenger()
{
    // 创建新的 PassengerWidget
    PassengerWidget *newPassenger = new PassengerWidget( this);

    // 绑定删除按钮的点击事件
    connect(newPassenger->deleteBtn, &QPushButton::clicked, this, [=]() {
        removePassenger(newPassenger);
    });
    // 绑定确认按钮的点击事件
    connect(newPassenger->confirmBtn, &QPushButton::clicked, this, [=]() {


        // 调用验证函数
        validatePassengerInfo(newPassenger);
    });

    // 将新乘机人控件添加到数组中
    passengerWidgets.append(newPassenger);

    // 更新乘车人列表显示
    updatePassengerList();

    qDebug() << "新增乘机人，当前总人数:" << passengerWidgets.size();
}

// 更新乘车人列表显示
void BuyWidget::updatePassengerList()
{
    // 清空当前显示的所有乘机人
    for (auto widget : scrollLayout->children()) {
        QWidget *child = qobject_cast<QWidget*>(widget);
        if (child) {
            scrollLayout->removeWidget(child);
            delete child;
        }
    }
    // 设置控件向上对齐
    scrollLayout->setAlignment(Qt::AlignTop);

    // 设置控件之间的间隔
    scrollLayout->setSpacing(10);  // 设置间隔为 10px，可以根据需求调整
    // 将数组中的每个 PassengerWidget 添加到布局中，并设置其序号
    for (int i = 0; i < passengerWidgets.size(); ++i) {
        PassengerWidget *passenger = passengerWidgets[i];
        passenger->setLabel(i + 1);  // 设置序号，从 1 开始
        scrollLayout->addWidget(passenger);
    }
}



// 实现购买的逻辑，后面改签的时候可能会用，功能是一个一个加的所以代码堆的跟屎山一样

//注意顺序
//1、检查乘机人是否为空和乘机人是否超过剩余座位
//2、检查密码是否正确
//3、检查余额是否足够
//4、更新剩余座位和余额
//5、插入订单和交易记录
void BuyWidget::onPayButtonClicked() {
    // 检查乘机人是否为空
    if (passengerSet.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("乘机人不能为空，请先添加乘机人！"));
        return;
    }

    int availableSeats = 0;
    // 查询剩余座位数,本来在下面的函数里有这个功能，但是没有好好工作，所以又强制加了一遍
    QSqlQuery flightQuery;
    flightQuery.prepare("SELECT economy_available_seats, business_available_seats, first_class_available_seats "
                        "FROM flights WHERE flight_number = :flightNumber AND departure_time = :departureTime");
    flightQuery.bindValue(":flightNumber", data.flight_number);
    flightQuery.bindValue(":departureTime", data.departure_time);
    if (!flightQuery.exec() || !flightQuery.next()) {
        QMessageBox::critical(this, tr("错误"), tr("查询航班信息失败！"));
        return;
    }
    switch (type) {
    case 1:  // Economy class
        availableSeats = flightQuery.value("economy_available_seats").toInt();
        break;
    case 2:  // Business class
        availableSeats = flightQuery.value("business_available_seats").toInt();
        break;
    case 3:  // First class
        availableSeats = flightQuery.value("first_class_available_seats").toInt();
        break;
    default:
        QMessageBox::critical(this, tr("错误"), tr("无效的舱位类型！"));
        return;
    }
    qDebug() << "当前乘机人数量：" << passengerSet.size()<<" 剩余座位"<<availableSeats;
    // 检查座位是否足够
    if (passengerSet.size() > availableSeats) {
        QMessageBox::warning(this, tr("警告"), tr("乘机人数超过剩余座位数！"));
        return;
    }


    // 获取支付密码
    bool ok;
    QString password = QInputDialog::getText(this, tr("支付密码"), tr("请输入支付密码："), QLineEdit::Password, "", &ok);
    if (!ok || password.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("支付密码不能为空！"));
        return;
    }

    // 查询用户余额
    QSqlQuery query;
    query.prepare("SELECT balance FROM users WHERE ID_card = :idCard AND password = :password");
    query.bindValue(":idCard", curUser);
    query.bindValue(":password", password);
    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, tr("错误"), tr("支付密码错误或查询失败！"));
        return;
    }




    double balance = query.value("balance").toDouble();
    double totalCost = passengerSet.size() * seatPrice; // 总费用
    if (balance < totalCost) {
        QMessageBox::warning(this, tr("警告"), tr("余额不足，请充值后再支付！"));
        return;
    }

    // 更新航班座位数
    if (!updateFlightSeats()) return;  // 更新航班座位失败
    // 执行支付和更新操作
    if (!processPayment(totalCost)) return; // 扣款失败或查询航班失败

    // 在支付之前，插入订单信息
    if (!createOrders()) {
        return; // 如果插入订单失败，终止支付
    }




    // 获取用户名并记录交易
    if (!recordTransaction(totalCost)) return; // 记录交易失败

    QMessageBox::information(this, tr("成功"), tr("支付成功！"));
    isPay = true;
    isbuy=true;
    this->deleteLater();  // 关闭当前窗口
}

// 创建订单：遍历乘机人信息，并插入订单
bool BuyWidget::createOrders() {
    // 获取当前时间作为订单时间
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    for (const PassengerInfo &passenger : passengerSet) {
        QSqlQuery orderQuery;
        orderQuery.prepare("INSERT INTO Orders (Id_card, realname, flight_number, seat_class, price, status, departure_time, order_date) "
                           "VALUES (:idCard, :realname, :flightNumber, :seatClass, :price, :status, :departureTime, :orderDate)");
        orderQuery.bindValue(":idCard", curUser);
        orderQuery.bindValue(":realname", passenger.name);  // 乘机人姓名
        orderQuery.bindValue(":flightNumber", data.flight_number);
        orderQuery.bindValue(":seatClass", getSeatClassString(type));  // 获取舱位等级字符串
        orderQuery.bindValue(":price", seatPrice);
        orderQuery.bindValue(":status", "upcoming");  // 设置订单状态为 upcoming
        orderQuery.bindValue(":departureTime", data.departure_time);
        orderQuery.bindValue(":orderDate", currentDateTime);  // 设置订单日期为当前时间

        if (!orderQuery.exec()) {
            QMessageBox::critical(this, tr("错误"), tr("插入订单失败！"));
            return false;
        }
    }
    return true;
}

// 获取座舱类型的字符串
QString BuyWidget::getSeatClassString(int seatType) {
    switch (seatType) {
    case 1:
        return "economy";
    case 2:
        return "business";
    case 3:
        return "first_class";
    default:
        return "unknown";
    }
}

// 执行支付操作：更新用户余额
bool BuyWidget::processPayment(double totalCost) {
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE users SET balance = balance - :totalCost WHERE ID_card = :idCard");
    updateQuery.bindValue(":totalCost", totalCost);
    updateQuery.bindValue(":idCard", curUser);
    return updateQuery.exec();
}

// 更新航班座位数
bool BuyWidget::updateFlightSeats() {
    QSqlQuery flightQuery;
    flightQuery.prepare("SELECT economy_available_seats, business_available_seats, first_class_available_seats FROM flights WHERE flight_number = :flightNumber AND departure_time = :departureTime");
    flightQuery.bindValue(":flightNumber", data.flight_number);
    flightQuery.bindValue(":departureTime", data.departure_time);
    if (!flightQuery.exec() || !flightQuery.next()) {
        QMessageBox::critical(this, tr("错误"), tr("查询航班信息失败！"));
        return false;
    }

    int economySeats = flightQuery.value("economy_available_seats").toInt();
    int businessSeats = flightQuery.value("business_available_seats").toInt();
    int firstClassSeats = flightQuery.value("first_class_available_seats").toInt();
    int seatsToReduce = passengerSet.size();

    // 根据舱位类型更新座位
    switch (type) {
    case 1: return updateSeatCount("economy_available_seats", economySeats, seatsToReduce);
    case 2: return updateSeatCount("business_available_seats", businessSeats, seatsToReduce);
    case 3: return updateSeatCount("first_class_available_seats", firstClassSeats, seatsToReduce);
    default:
        QMessageBox::critical(this, tr("错误"), tr("无效的舱位类型！"));
        return false;
    }
}

// 更新指定舱位的座位数
bool BuyWidget::updateSeatCount(const QString &columnName, int &seats, int seatsToReduce) {
    if (seats < seatsToReduce) {
        QMessageBox::warning(this, tr("警告"), tr("%1座位不足！").arg(columnName));
        return false;
    }

    seats -= seatsToReduce;
    QSqlQuery updateQuery;
    updateQuery.prepare(QString("UPDATE flights SET %1 = :seats WHERE flight_number = :flightNumber AND departure_time = :departureTime").arg(columnName));
    updateQuery.bindValue(":seats", seats);
    updateQuery.bindValue(":flightNumber", data.flight_number);
    updateQuery.bindValue(":departureTime", data.departure_time);

    return updateQuery.exec();
}

// 记录支付交易
bool BuyWidget::recordTransaction(double amount) {
    QSqlQuery userQuery;
    userQuery.prepare("SELECT username FROM users WHERE ID_card = :idCard");
    userQuery.bindValue(":idCard", curUser);
    if (!userQuery.exec() || !userQuery.next()) {
        QMessageBox::critical(this, tr("错误"), tr("获取用户名失败！"));
        return false;
    }

    QString username = userQuery.value("username").toString();
    QSqlQuery transactionQuery;
    transactionQuery.prepare("INSERT INTO wallet_transactions (username, transaction_type, amount, transaction_time, flight_number, departure_city, destination_city, ID_card) "
                             "VALUES (:username, 'Buy', :amount, CURRENT_TIMESTAMP, :flightNumber, :departureCity, :destinationCity, :IDCard)");
    transactionQuery.bindValue(":username", username);
    transactionQuery.bindValue(":amount", amount);
    transactionQuery.bindValue(":flightNumber", data.flight_number);
    transactionQuery.bindValue(":departureCity", data.departure_city);
    transactionQuery.bindValue(":destinationCity", data.arrival_city);
    transactionQuery.bindValue(":IDCard", curUser);

    return transactionQuery.exec();
}
