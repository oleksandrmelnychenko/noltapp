#ifndef OFFICELINEEDIT_H
#define OFFICELINEEDIT_H

#include <QLineEdit>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>

class OfficeLineEdit : public QLineEdit
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
    OfficeLineEdit(QWidget *parent = 0) : QLineEdit(parent){}
};

#endif // OFFICELINEEDIT_H
