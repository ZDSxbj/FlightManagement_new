#ifndef EVALUATIONDIALOG_H
#define EVALUATIONDIALOG_H

#include <QDialog>
#include <QRadioButton>
#include <QPushButton>

class EvaluationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EvaluationDialog(QWidget *parent = nullptr);
    ~EvaluationDialog();

    QString getEvaluation() const;

private slots:
    void onSubmitButtonClicked();

private:
    QRadioButton *verySatisfiedButton;
    QRadioButton *satisfiedButton;
    QRadioButton *averageButton;
    QRadioButton *unsatisfiedButton;
    QPushButton *submitButton;
    QString evaluation;  // 用于存储评价结果
};

#endif // EVALUATIONDIALOG_H
