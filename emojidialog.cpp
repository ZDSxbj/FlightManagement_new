#include "emojidialog.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QFile>
#include <QStyleFactory>

EmojiDialog::EmojiDialog(QWidget *parent) : QDialog(parent)
{
    setupUI();
}

void EmojiDialog::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QGridLayout *gridLayout = new QGridLayout();
    const QStringList emojis = {"😍", "😊", "😂", "😎", "🤗", "🤔", "🥳", "🤩", "🤔", "😉","🥲","🤣","😇","🙂","🙃","😉","😌","🥰","😋","🥺"};

    for (int i = 0; i < emojis.size(); ++i) {
        QPushButton *button = new QPushButton(emojis[i], this);
        button->setFixedSize(64, 64);  // 增加按钮的尺寸
        button->setStyleSheet(
            "QPushButton {"
            "   font-size: 24pt;"
            "   border: 1px solid #ccc;"
            "   border-radius: 8px;"
            "   background-color: #f0f0f0;"
            "   padding: 0;"
            "}"
            "QPushButton:hover {"
            "   background-color: #e0e0e0;"
            "}"
            "QPushButton:pressed {"
            "   background-color: #d0d0d0;"
            "}"
            );
        connect(button, &QPushButton::clicked, this, &EmojiDialog::onEmojiButtonClicked);
        gridLayout->addWidget(button, i / 5, i % 5);
    }

    layout->addLayout(gridLayout);
    setLayout(layout);
    setWindowTitle("请选择您的表情");

    // 设置对话框的背景颜色
    setStyleSheet("background-color: #ffffff;");

    // 设置对话框的最小尺寸
    setMinimumSize(400, 400);
}

void EmojiDialog::onEmojiButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        emit emojiSelected(button->text());
    }
    close();
}
