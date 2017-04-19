#ifndef COLLEAGUESLABEL_H
#define COLLEAGUESLABEL_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>

class ColleaguesLabel : public QLabel
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
    ColleaguesLabel(QWidget *parent = 0 ): QLabel(parent){}
};

#endif // COLLEAGUESLABEL_H
