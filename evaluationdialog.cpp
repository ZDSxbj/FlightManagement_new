#include "evaluationdialog.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

EvaluationDialog::EvaluationDialog(QWidget *parent) :
    QDialog(parent),
    verySatisfiedButton(nullptr),
    satisfiedButton(nullptr),
    averageButton(nullptr),
    unsatisfiedButton(nullptr),
    submitButton(nullptr),
    evaluation("")
{
    // 创建单选按钮
    verySatisfiedButton = new QRadioButton("很满意", this);
    satisfiedButton = new QRadioButton("满意", this);
    averageButton = new QRadioButton("一般", this);
    unsatisfiedButton = new QRadioButton("不满意", this);

    // 创建提交按钮
    submitButton = new QPushButton("提交", this);
    submitButton->setFixedWidth(100);  // 设置提交按钮的宽度为 100 像素

    // 设置窗口标题
    setWindowTitle("请作出评价");

    // 设置样式表
    setStyleSheet(
        "QDialog {"
        "    background-color: #f0f0f0; /* 背景颜色 */"
        "    border: 1px solid #ccc; /* 边框 */"
        "    border-radius: 5px; /* 边框圆角 */"
        "    padding: 20px; /* 内边距 */"
        "}"
        "QLabel {"
        "    color: #333; /* 文字颜色 */"
        "    font-size: 16px; /* 字体大小 */"
        "}"
        "QRadioButton {"
        "    color: #333; /* 文字颜色 */"
        "    font-size: 16px; /* 字体大小 */"
        "    margin: 5px 0; /* 选项间的垂直间距 */"
        "}"
        "QPushButton {"
        "    background-color: #6A5ACD; /* 按钮背景颜色 */"
        "    color: white; /* 按钮文字颜色 */"
        "    border: none; /* 按钮边框 */"
        "    border-radius: 5px; /* 按钮圆角 */"
        "    padding: 10px 20px; /* 按钮内边距 */"
        "    font-size: 16px; /* 字体大小 */"
        "}"
        "QPushButton:hover {"
        "    background-color: #BA55D3; /* 鼠标悬停时的背景颜色 */"
        "}"
        "QPushButton:pressed {"
        "    background-color: #6543A4; /* 按下时的背景颜色 */"
        "}"
        );

    // 设置布局
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // 创建一个垂直布局用于单选按钮
    QVBoxLayout *radioButtonLayout = new QVBoxLayout;
    radioButtonLayout->addWidget(verySatisfiedButton);
    radioButtonLayout->addWidget(satisfiedButton);
    radioButtonLayout->addWidget(averageButton);
    radioButtonLayout->addWidget(unsatisfiedButton);
    radioButtonLayout->addStretch();  // 添加一个伸缩空间，使按钮与下方的提交按钮之间有更多空间

    // 创建一个水平布局用于居中单选按钮
    QHBoxLayout *centerLayout = new QHBoxLayout;
    centerLayout->addStretch();  // 左侧伸缩空间
    centerLayout->addLayout(radioButtonLayout);  // 添加单选按钮布局
    centerLayout->addStretch();  // 右侧伸缩空间

    // 创建一个垂直布局用于提交按钮
    QVBoxLayout *submitButtonLayout = new QVBoxLayout;
    submitButtonLayout->addStretch();  // 上方伸缩空间
    submitButtonLayout->addWidget(submitButton);  // 添加提交按钮
    submitButtonLayout->addStretch();  // 下方伸缩空间

    // 创建一个水平布局用于居中提交按钮
    QHBoxLayout *submitCenterLayout = new QHBoxLayout;
    submitCenterLayout->addStretch();  // 左侧伸缩空间
    submitCenterLayout->addLayout(submitButtonLayout);  // 添加提交按钮布局
    submitCenterLayout->addStretch();  // 右侧伸缩空间

    // 将所有布局添加到主布局中
    mainLayout->addLayout(centerLayout);  // 添加居中单选按钮布局
    mainLayout->addLayout(submitCenterLayout);  // 添加居中提交按钮布局

    setLayout(mainLayout);

    // 调整对话框的大小
    setFixedSize(400, 250);  // 设置固定大小为 400x250 像素

    // 连接信号和槽
    connect(submitButton, &QPushButton::clicked, this, &EvaluationDialog::onSubmitButtonClicked);
}

EvaluationDialog::~EvaluationDialog()
{
}

QString EvaluationDialog::getEvaluation() const
{
    return evaluation;
}

void EvaluationDialog::onSubmitButtonClicked()
{
    // 检查是否有选项被选中
    if (!verySatisfiedButton->isChecked() && !satisfiedButton->isChecked() &&
        !averageButton->isChecked() && !unsatisfiedButton->isChecked()) {
        // 如果没有选项被选中，弹出提示窗口
        QMessageBox::warning(this, "提示", "请做出选择");
        return;
    }

    // 根据用户选择设置评价
    if (verySatisfiedButton->isChecked()) {
        evaluation = "很满意";
    } else if (satisfiedButton->isChecked()) {
        evaluation = "满意";
    } else if (averageButton->isChecked()) {
        evaluation = "一般";
    } else if (unsatisfiedButton->isChecked()) {
        evaluation = "不满意";
    }

    // 显示提交成功消息框
    QMessageBox::information(this, "提交成功", "提交成功，感谢您的反馈");

    // 接受对话框并关闭
    accept();
}
