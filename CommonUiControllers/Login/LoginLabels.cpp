#include "LoginLabels.h"
#include <QLineEdit>

void LoginLabels::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {        
        emit inFocus();
    }
}

LoginLabels::LoginLabels(QWidget* parent) : QLabel(parent)
{

}
