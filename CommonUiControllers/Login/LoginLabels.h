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
    void mousePressEvent(QMouseEvent *e);
    // add focusout event

signals:
    void inFocus();

public:
    LoginLabels(QWidget *parent =0);
};

#endif // LOGINLABELS_H
