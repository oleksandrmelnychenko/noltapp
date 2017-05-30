#ifndef OFFICELABEL_H
#define OFFICELABEL_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>

class OfficeLabel : public QLabel
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
    OfficeLabel(QWidget *parent = 0 ): QLabel(parent){}
};

#endif // OFFICELABEL_H
