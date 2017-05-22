#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include <QPropertyAnimation>
#include <QRect>
#include <QLabel>
#include <QDebug>

class AnimationController
{
public:
    AnimationController(){}

    void labelAnimationByY(QLabel *label, int animationDuration, int labelsYCoordinate)
    {
        QPropertyAnimation* animation = new QPropertyAnimation(label,"geometry");        
        animation->setDuration(animationDuration);
        animation->setEasingCurve(QEasingCurve::Linear);
        animation->setEndValue(QRect(label->x(), labelsYCoordinate, label->width(), label->height()));
        animation->start(QAbstractAnimation::DeleteWhenStopped);       
    }
};

#endif // ANIMATIONCONTROLLER_H
