#ifndef SALARYLABEL_H
#define SALARYLABEL_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>

class SalaryLabel : public QLabel
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
    SalaryLabel(QWidget *parent = 0) : QLabel(parent) {}
};

#endif // SALARYLABEL_H
