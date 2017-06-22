#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include <QIcon>
#include <QPushButton>
#include <QFont>

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent, Qt::FramelessWindowHint | Qt::Window | Qt::CustomizeWindowHint),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    ui->lblIncorrectLogin->hide();

    mAnimationController = new AnimationController();

    setUpShadow();

    subscribeToFormEvents();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

bool LoginWindow::isMousePointerInFrame()
{
    return (mMouseClickXCoordinate >= mFrameStartPointX && mMouseClickXCoordinate <= mFrameWidth &&
            mMouseClickYCoordinate >= mFrameStartPointY && mMouseClickYCoordinate <= mFrameHeight);
}

void LoginWindow::clearFocusOfLineEdits()
{
    ui->txtLogin->clearFocus();
    ui->txtPassword->clearFocus();
}

void LoginWindow::setUpShadow()
{
    setAttribute(Qt::WA_TranslucentBackground);

    CustomShadowEffect  *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(5.0);
    bodyShadow->setDistance(1.0);
    bodyShadow->setColor(QColor(9,146,177));

    ui->lblPictureCat->setGraphicsEffect(bodyShadow);
}

bool LoginWindow::isLineEditEmpty(const QLineEdit *lineEdit)
{
    return (QString(lineEdit->text()).isEmpty());
}

void LoginWindow::setLabelsPosition(const QLineEdit *lineEdit, QLabel *label, int labelsStartPointY, int labelsEndPointY)
{
    if(isLineEditEmpty(lineEdit))
    {
        mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsStartPointY);
    }
    else
    {
        mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsEndPointY);
    }
}

void LoginWindow::subscribeToFormEvents()
{
    setLabelsPosition(ui->txtLogin, ui->lblLogin, mlblLoginStartPointY, mlblLoginEndPointY);
    setLabelsPosition(ui->txtPassword, ui->lblPassword, mlblPasswordStartPointY, mlblPasswordEndPointY);

    connect(ui->btnLogin, SIGNAL(clicked()), this, SLOT(login()));
    connect(ui->btnQuit, SIGNAL(clicked()), this, SLOT(close()));

    connect(ui->lblPictureCat, SIGNAL(inFocus()), this, SLOT(lostFocusOnLineEditsByClickOnPictures()));
    connect(ui->lblPictureNolt, SIGNAL(inFocus()), this,SLOT(lostFocusOnLineEditsByClickOnPictures()));

    connect(ui->txtLogin, SIGNAL(outFocus()), this, SLOT(lostFocusOnLineEditLogin()));
    connect(ui->txtPassword, SIGNAL(outFocus()), this, SLOT(lostFocusOnLineEditPassword()));

    connect(ui->lblLogin, &LoginLabels::inFocus, this,[this]{setFocusOnLineEdit(ui->txtLogin);});
    connect(ui->lblPassword, &LoginLabels::inFocus, this,[this]{setFocusOnLineEdit(ui->txtPassword);});

    connect(ui->txtLogin, &LoginLineEdits::inFocus, this,[this]{doLabelAnimation(ui->lblLogin, mlblLoginEndPointY);});
    connect(ui->txtPassword, &LoginLineEdits::inFocus, this,[this]{doLabelAnimation(ui->lblPassword, mlblPasswordEndPointY);});
}

bool LoginWindow::IsAutorised()
{
    return mIsAutorised;
}

void LoginWindow::login()
{
    QString inputLogin = ui->txtLogin->text();
    QString inputPassword = ui->txtPassword->text();

    if(inputLogin == mLogin && inputPassword == mPassword)
    {        
        mIsAutorised = true;
        emit buttonLoginClicked();
    }
    else
    {
       ui->lblIncorrectLogin->show();       
    }
}

void LoginWindow::setFocusOnLineEdit(QLineEdit *lineEdint)
{
    lineEdint->setFocus();
}

void LoginWindow::doLabelAnimation(QLabel *label, int labelsYCoordinate)
{
    mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsYCoordinate);
    ui->lblIncorrectLogin->hide();
}

void LoginWindow::lostFocusOnLineEditLogin()
{
    setLabelsPosition(ui->txtLogin, ui->lblLogin, mlblLoginStartPointY, mlblLoginEndPointY);
}

void LoginWindow::lostFocusOnLineEditPassword()
{
    setLabelsPosition(ui->txtPassword, ui->lblPassword, mlblPasswordStartPointY, mlblPasswordEndPointY);
}

void LoginWindow::lostFocusOnLineEditsByClickOnPictures()
{
    clearFocusOfLineEdits();
}

void LoginWindow::mousePressEvent(QMouseEvent *event)
{
    mMouseClickXCoordinate = event->x();
    mMouseClickYCoordinate = event->y();
}

void LoginWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(isMousePointerInFrame())
    {
        clearFocusOfLineEdits();
        move(event->globalX()-mMouseClickXCoordinate,event->globalY()-mMouseClickYCoordinate);
    }
}

void LoginWindow::mouseReleaseEvent(QMouseEvent*)
{
   mMouseClickXCoordinate = 0;
   mMouseClickYCoordinate = 0;
}


