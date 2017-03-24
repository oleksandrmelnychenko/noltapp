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
    bool isLineEditEmpty(const QLineEdit *lineEdit);
    void setLabelsPosition(const QLineEdit *lineEdit, QLabel *label, int labelsStartPointY, int labelsEndPointY);
    void subscribeToFormEvents();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void login();    
    void setFocusOnLineEdit(QLineEdit *lineEdint);
    void doLabelAnimation(QLabel *label, int labelsYCoordinate);
    void lostFocusOnLineEditLogin();
    void lostFocusOnLineEditPassword();
    void lostFocusOnLineEditsByClickOnPictures();

private:
    Ui::LoginForm *ui;

    const QString mLogin = "a";
    const QString mPassword = "1";
    MainWindow* mMainWindow;

    AnimationController* mAnimationController;
    int mAnimationDuration = 250;

    const int mlblLoginStartPointY = 332;
    const int mlblLoginEndPointY = 314;
    const int mlblPasswordStartPointY = 378;
    const int mlblPasswordEndPointY = 360;

    const int mFrameStartPointX = 5;
    const int mFrameStartPointY = 5;
    const int mFrameWidth = 500;
    const int mFrameHeight = 21;

    int mMouseClickXCoordinate;
    int mMouseClickYCoordinate;
};

#endif // LOGINFORM_H
