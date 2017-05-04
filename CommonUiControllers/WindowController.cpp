#include "WindowController.h"
#include <QDebug>

WindowController::WindowController(int width, int height): mWidth(width), mHeight(height)
{
   CreateLoginWindow();

   connect(mLoginWindow, SIGNAL(buttonLoginClicked()), this, SLOT(CreateMainWindow()));
}

void WindowController::CreateLoginWindow()
{
    mLoginWindow = new LoginWindow();
    mLoginWindow->show();
}

void WindowController::setCenterOfApplication(QWidget *widget)
{
    QSize size = widget->size();

    int mw = size.width();
    int mh = size.height();
    int centerW = (mWidth-mw)/2;
    int centerH = (mHeight-mh)/2;
    widget->move(centerW, centerH);
}

void WindowController::CreateMainWindow()
{
    if(mLoginWindow->IsAutorised())
    {
        delete mLoginWindow;
        mLoginWindow = nullptr;

        mMainWindow = new MainWindow();
        setCenterOfApplication(mMainWindow);
        mMainWindow->show();
    }
}
