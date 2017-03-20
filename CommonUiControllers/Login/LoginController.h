#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QPropertyAnimation>
#include <QRect>

class LoginController
{
public:
    LoginController();

    void labelAnimation(QObject *object, int animationDuration, int x, int y, int width, int height);
};

#endif // LOGINCONTROLLER_H
