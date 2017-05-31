#ifndef BUDGETLEINEEDIT_H
#define BUDGETLEINEEDIT_H

#include <QLineEdit>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>

class BudgetLineEdit : public QLineEdit
{
    Q_OBJECT

protected:
    void focusInEvent(QFocusEvent *e)
    {
        QLineEdit::focusInEvent(e);
        emit inFocus();
    }

    void focusOutEvent(QFocusEvent *e)
    {
        QLineEdit::focusOutEvent(e);
        emit outFocus();
    }

signals:
    void outFocus();
    void inFocus();

public:
    BudgetLineEdit(QWidget *parent = 0) : QLineEdit(parent){}
};

#endif // BUDGETLEINEEDIT_H
