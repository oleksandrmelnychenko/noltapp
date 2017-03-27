#include "WindowController.h"
#include <QDebug>

WindowController::WindowController()
{
   CreateLoginWindow();

   connect(mLoginWindow, SIGNAL(buttonLoginClicked()), this, SLOT(CreateMainWindow()));
}

void WindowController::CreateLoginWindow()
{
    mLoginWindow = new LoginWindow();
    mLoginWindow->show();
}

void WindowController::CreateMainWindow()
{
    if(mLoginWindow->IsAutorised())
    {
        delete mLoginWindow;
        mLoginWindow = nullptr;

        mMainWindow = new MainWindow();
        mMainWindow->show();
    }
}
