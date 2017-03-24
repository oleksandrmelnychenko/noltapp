#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include <QPropertyAnimation>
#include <QRect>
#include <QLabel>

class AnimationController
{
public:
    AnimationController(){}

    void labelAnimationByY(QLabel *label, int animationDuration, int y)
    {
        QPropertyAnimation* animation = new QPropertyAnimation(label,"geometry");
        animation->setDuration(animationDuration);
        animation->setEasingCurve(QEasingCurve::Linear);
        animation->setEndValue(QRect(label->x(), y, label->width(), label->height()));
        animation->start(QAbstractAnimation::DeleteWhenStopped);
        qDebug() << label << label->y();
    }
};

#endif // ANIMATIONCONTROLLER_H
