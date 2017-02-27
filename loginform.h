#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QMessageBox>
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

private:
    Ui::LoginForm *ui;

    QString mLogin = "a";
    QString mPassword = "1";
    MainWindow* mMainWindow;
};

#endif // LOGINFORM_H
