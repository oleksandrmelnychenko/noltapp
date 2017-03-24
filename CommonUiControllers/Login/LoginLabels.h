#ifndef LOGINLABELS_H
#define LOGINLABELS_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>

class LoginLabels : public QLabel
{
    Q_OBJECT

protected:    
    void mousePressEvent(QMouseEvent *e)
    {
        if(e->button() == Qt::LeftButton)
        {
            emit inFocus();
        }
    }

signals:
    void inFocus();

public:
    LoginLabels(QWidget *parent =0) : QLabel(parent){}
};

#endif // LOGINLABELS_H
