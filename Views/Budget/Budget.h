#ifndef BUDGET_H
#define BUDGET_H

#include <QWidget>

namespace Ui {
    class Budget;
}

class Budget : public QWidget
{
    Q_OBJECT

public:
    explicit Budget(QWidget *parent = 0);
    ~Budget();

private:
    Ui::Budget *ui;
};

#endif // BUDGET_H
