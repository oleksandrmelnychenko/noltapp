#include "LoginController.h"

LoginController::LoginController()
{

}

void LoginController::labelAnimation(QObject *object, int animationDuration,
                                     int x, int y, int width, int height)
{
    QPropertyAnimation* animation = new QPropertyAnimation(object,"geometry");
    animation->setDuration(animationDuration);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setEndValue(QRect(x, y, width, height));
    animation->start(QAbstractAnimation::DeleteWhenStopped);

}
