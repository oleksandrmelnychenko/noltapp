#include "AnimationController.h"
#include <QDebug>

AnimationController::AnimationController()
{

}

void AnimationController::labelAnimationByY(QLabel *label, int animationDuration, int y)
{
    qDebug() << label->y();
    QPropertyAnimation* animation = new QPropertyAnimation(label,"geometry");
    animation->setDuration(animationDuration);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setEndValue(QRect(label->x(), y, label->width(), label->height()));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
