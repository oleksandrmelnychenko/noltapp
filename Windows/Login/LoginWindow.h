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

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private slots:
    void login();
    //void doLabelLoginAnimation();
    //void doLabelPasswordAnimation();
    void doLabelAnimation(QLabel *label, QLineEdit *lineEdit, int y);
    void lostFocusOnLineEdits();
    void lostFocusOnLineEditsByClickOnPictures();

private:
    Ui::LoginForm *ui;

    QString mLogin = "a";
    QString mPassword = "1";
    MainWindow* mMainWindow;
    AnimationController* mAnimationController;

    int mAnimationDuration = 250;

    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
};

#endif // LOGINFORM_H
