#ifndef EMOJIDIALOG_H
#define EMOJIDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>

class EmojiDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EmojiDialog(QWidget *parent = nullptr);

signals:
    void emojiSelected(const QString &emoji);

private slots:
    void onEmojiButtonClicked();

private:
    void setupUI();
};

#endif // EMOJIDIALOG_H
