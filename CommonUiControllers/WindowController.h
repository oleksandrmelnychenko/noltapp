#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTROLLER_H

#include <QObject>
#include "Windows/Login/LoginWindow.h"
#include "Windows/Main/MainWindow.h"

class WindowController : public QObject
{
    Q_OBJECT

public:
    WindowController();

    void CreateLoginWindow();

protected slots:
    void CreateMainWindow();

private:
    LoginWindow *mLoginWindow;
    MainWindow *mMainWindow;
};

#endif // WINDOWCONTROLLER_H
