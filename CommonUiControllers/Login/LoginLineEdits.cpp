#include "LoginLineEdits.h"

void LoginLineEdits::focusInEvent(QFocusEvent *e)
{
    QLineEdit::focusInEvent(e);
    emit inFocus();
}

void LoginLineEdits::focusOutEvent(QFocusEvent *e)
{
    QLineEdit::focusOutEvent(e);
    emit outFocus();
}

void LoginLineEdits::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {        
        emit inFocus();
    }
}

LoginLineEdits::LoginLineEdits(QWidget *parent) : QLineEdit(parent)
{

}
