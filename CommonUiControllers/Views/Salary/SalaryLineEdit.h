#ifndef SALARYLINEEDIT_H
#define SALARYLINEEDIT_H

#include <QLineEdit>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>

class SalaryLineEdit : public QLineEdit
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
    SalaryLineEdit(QWidget *parent = 0) : QLineEdit(parent){}
};

#endif // SALARYLINEEDIT_H
