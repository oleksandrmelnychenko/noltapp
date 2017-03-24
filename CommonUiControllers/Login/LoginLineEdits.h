#ifndef LOGINLINEEDITS_H
#define LOGINLINEEDITS_H

#include <QLineEdit>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>

class LoginLineEdits : public QLineEdit
{
    Q_OBJECT

protected:
    void focusInEvent(QFocusEvent* e)
    {
        QLineEdit::focusInEvent(e);
        emit inFocus();
    }

    void focusOutEvent(QFocusEvent *e)
    {
        QLineEdit::focusOutEvent(e);
        emit outFocus();
    }

    void mousePressEvent(QMouseEvent *e)
    {
        if(e->button() == Qt::LeftButton)
        {
            emit inFocus();
        }
    }

signals:
    void inFocus();
    void outFocus();

public:
    LoginLineEdits(QWidget *parent =0) : QLineEdit(parent){}
};

#endif // LOGINLINEEDITS_H
