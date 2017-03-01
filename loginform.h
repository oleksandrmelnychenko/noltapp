#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QPropertyAnimation>
#include "mainwindow.h"

namespace Ui {
    class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

    bool eventFilter(QObject *object, QEvent *event);

private slots:
    void login();  
    void labelAnimation(QObject *object, int animationDuration, int x, int y, int width, int height);

private:
    Ui::LoginForm *ui;

    QString mLogin = "a";
    QString mPassword = "1";
    MainWindow* mMainWindow;
};

#endif // LOGINFORM_H
