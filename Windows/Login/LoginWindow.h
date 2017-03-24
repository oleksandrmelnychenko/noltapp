#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QLineEdit>
#include <QGraphicsDropShadowEffect>
#include "Windows/Main/MainWindow.h"
#include "Windows/CustomShadoweffect.h"
#include "CommonUiControllers/AnimationController.h"

namespace Ui {
    class LoginForm;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
private:
    bool isMousePointerInFrame();
    void clearFocusOfLineEdits();
    void setUpShadow();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void login();    
    void setFocusOnLineEdit(QLineEdit* lineEdint);
    void doLabelAnimation(QLabel *label, int y);
    void lostFocusOnLineEditLogin();
    void lostFocusOnLineEditPassword();
    void lostFocusOnLineEditsByClickOnPictures();

private:
    Ui::LoginForm *ui;

    QString mLogin = "a";
    QString mPassword = "1";
    MainWindow* mMainWindow;
    AnimationController* mAnimationController;

    int mFrameStartPoinX = 5;
    int mFrameStartPoinY = 5;
    int mFrameWidth = 498;
    int mFrameHeight = 21;

    int mAnimationDuration = 250;

    int mMouseClickXCoordinate;
    int mMouseClickYCoordinate;
};

#endif // LOGINFORM_H
