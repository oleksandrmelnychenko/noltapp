#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include <QIcon>
#include <QPushButton>

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent, Qt::FramelessWindowHint | Qt::Window | Qt::CustomizeWindowHint),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);   
    mAnimationController = new AnimationController();

    connect(ui->lblPictureCat, SIGNAL(inFocus()), this,
            SLOT(lostFocusOnLineEditsByClickOnPictures()));
    connect(ui->lblPictureNolt, SIGNAL(inFocus()), this,
            SLOT(lostFocusOnLineEditsByClickOnPictures()));
    connect(ui->txtLogin, SIGNAL(outFocus()), this, SLOT(lostFocusOnLineEdits()));
    connect(ui->txtPassword, SIGNAL(outFocus()), this, SLOT(lostFocusOnLineEdits()));
    connect(ui->btnLogin, SIGNAL(clicked()), this, SLOT(login()));
    connect(ui->btnQuit, SIGNAL(clicked()), this, SLOT(close()));

    connect(ui->lblLogin, &LoginLabels::inFocus, this,
            [this]{setFocusOnLineEdit(ui->txtLogin);});
    connect(ui->lblPassword, &LoginLabels::inFocus, this,
            [this]{setFocusOnLineEdit(ui->txtPassword);});

    connect(ui->txtLogin, &LoginLineEdits::inFocus, this,
            [this]{doLabelAnimation(ui->lblLogin, 314);});
    connect(ui->txtPassword, &LoginLineEdits::inFocus, this,
            [this]{doLabelAnimation(ui->lblPassword, 360);});

    ui->lblIncorrectLogin->hide();

    if(!QString(ui->txtLogin->text()).isEmpty())
    {
       ui->lblLogin->setGeometry(92, 314, 120, 13);       
    }
    if(!QString(ui->txtPassword->text()).isEmpty())
    {
       ui->lblPassword->setGeometry(92, 360, 120, 13);
    }

    setAttribute(Qt::WA_TranslucentBackground);

    CustomShadowEffect  *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(35.0);
    bodyShadow->setDistance(5.0);
    bodyShadow->setColor(QColor(9,146,177));    
    ui->lblPictureCat->setGraphicsEffect(bodyShadow);    
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::login()
{
    QString inputLogin = ui->txtLogin->text();
    QString inputPassword = ui->txtPassword->text();

    if(inputLogin == mLogin && inputPassword == mPassword)
    {
        hide();
        mMainWindow = new MainWindow(this);
        mMainWindow->show();
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

void LoginWindow::doLabelAnimation(QLabel *label, int y)
{
    mAnimationController->labelAnimationByY(label, mAnimationDuration, y);
    ui->lblIncorrectLogin->hide();    
}

void LoginWindow::lostFocusOnLineEdits() // or two methods to txlLogin and txtPassword
{
    if(QString(ui->txtLogin->text()).isEmpty())
    {
       mAnimationController->labelAnimationByY(ui->lblLogin, mAnimationDuration, 332);       
    }
    if(QString(ui->txtPassword->text()).isEmpty())
    {
       mAnimationController->labelAnimationByY(ui->lblPassword, mAnimationDuration, 378);       
    }
}

void LoginWindow::lostFocusOnLineEditsByClickOnPictures()
{
    ui->txtLogin->clearFocus();
    ui->txtPassword->clearFocus();
}

void LoginWindow::mousePressEvent(QMouseEvent *event)
{
    //ui->txtLogin->clearFocus();
    //ui->txtPassword->clearFocus();
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void LoginWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(m_nMouseClick_X_Coordinate >= 5 && m_nMouseClick_X_Coordinate <= 498 &&
            m_nMouseClick_Y_Coordinate >= 5 && m_nMouseClick_Y_Coordinate <= 21)
    {
        ui->txtLogin->clearFocus();
        ui->txtPassword->clearFocus();
        move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
    }
}

void LoginWindow::mouseReleaseEvent(QMouseEvent *event)
{
   m_nMouseClick_X_Coordinate = 0;
   m_nMouseClick_Y_Coordinate = 0;
}


