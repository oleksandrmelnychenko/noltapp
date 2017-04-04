#ifndef COLLEAGUESLINEEDITD_H
#define COLLEAGUESLINEEDITD_H

#include <QLineEdit>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>

class ColleaguesLineEditd : public QLineEdit
{
    Q_OBJECT

protected:
    void focusOutEvent(QFocusEvent *e)
    {
        QLineEdit::focusOutEvent(e);
        emit outFocus();
    }

signals:
    void outFocus();

public:
    ColleaguesLineEditd(QWidget *parent = 0) : QLineEdit(parent){}

};

#endif // COLLEAGUESLINEEDITD_H
