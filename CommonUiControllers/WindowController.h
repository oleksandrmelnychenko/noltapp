#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTROLLER_H

#include <QObject>
#include <QDesktopWidget>

#include "Windows/Login/LoginWindow.h"
#include "Windows/Main/MainWindow.h"

class WindowController : public QObject
{
    Q_OBJECT

public:    
    WindowController(int width, int height);

    void CreateLoginWindow();

private:
    void setCenterOfApplication(QWidget* widget);

protected slots:
    void CreateMainWindow();

private:
    LoginWindow *mLoginWindow;
    MainWindow *mMainWindow;

    int mHeight;
    int mWidth;
};

#endif // WINDOWCONTROLLER_H
