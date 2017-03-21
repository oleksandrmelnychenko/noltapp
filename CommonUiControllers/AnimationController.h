#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include <QPropertyAnimation>
#include <QRect>
#include <QLabel>

class AnimationController
{
public:
    AnimationController();

    void labelAnimationByY(QLabel *label, int animationDuration, int y);
};

#endif // ANIMATIONCONTROLLER_H
