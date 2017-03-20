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
    void focusInEvent(QFocusEvent* e);
    void focusOutEvent(QFocusEvent *e);
    void mousePressEvent(QMouseEvent *e);

signals:
    void inFocus();
    void outFocus();

public:
    LoginLineEdits(QWidget *parent =0);
};

#endif // LOGINLINEEDITS_H
