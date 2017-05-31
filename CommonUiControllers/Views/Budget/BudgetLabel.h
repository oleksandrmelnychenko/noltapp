#ifndef BUDGETLABEL_H
#define BUDGETLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class BudgetLabel : public QLabel
{
    Q_OBJECT

protected:
    void mousePressEvent(QMouseEvent *e)
    {
        if(e->button() == Qt::LeftButton)
        {
            emit pressIn();
        }
    }

signals:
    void pressIn();

public:
    BudgetLabel(QWidget *parent = 0 ): QLabel(parent){}
};

#endif // BUDGETLABEL_H
