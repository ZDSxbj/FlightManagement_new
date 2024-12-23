#ifndef FORGET_H
#define FORGET_H

#include <QDialog>

namespace Ui {
class Forget;
}

class Forget : public QDialog
{
    Q_OBJECT

public:
    explicit Forget(QWidget *parent = nullptr);
    ~Forget();

private:
    Ui::Forget *ui;
};

#endif // FORGET_H
