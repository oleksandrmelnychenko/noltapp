#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include <QIcon>
#include <QPushButton>

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent, Qt::FramelessWindowHint | Qt::Window | Qt::CustomizeWindowHint),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    connect(ui->btnLogin, SIGNAL(clicked()), this, SLOT(login()));
    connect(ui->btnQuit, SIGNAL(clicked()), this, SLOT(close()));   

    ui->txtLogin->installEventFilter(this);
    ui->txtPassword->installEventFilter(this);
    ui->lblLogin->installEventFilter(this);
    ui->lblPassword->installEventFilter(this);
    ui->lblPictureCat->installEventFilter(this);
    ui->lblPictureNolt->installEventFilter(this);

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

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::login()
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

void LoginForm::labelAnimation(QObject *object, int animationDuration, int x, int y, int width, int height)
{
    QPropertyAnimation* animation = new QPropertyAnimation(object,"geometry");
    animation->setDuration(animationDuration);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setEndValue(QRect(x, y, width, height));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

bool LoginForm::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::FocusIn)
    {
        if(object == ui->txtLogin || object == ui->lblLogin)
        {
            labelAnimation(ui->lblLogin, 250, 92, 314, 120, 13 );
            ui->lblIncorrectLogin->hide();
        }
        if(object == ui->txtPassword || object == ui->lblPassword)
        {
            labelAnimation(ui->lblPassword, 250, 92, 360, 120, 13);
            ui->lblIncorrectLogin->hide();
        }
    }
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(object == ui->lblLogin)
        {
            labelAnimation(ui->lblLogin, 250, 92, 314, 120, 13);
            ui->lblIncorrectLogin->hide();
            ui->txtLogin->setFocus();
        }
        if(object == ui->lblPassword)
        {
            labelAnimation(ui->lblPassword, 250, 92, 360, 120, 13);
            ui->lblIncorrectLogin->hide();
            ui->txtPassword->setFocus();
        }
        if(object == ui->lblPictureCat || object == ui->lblPictureNolt)
        {
           if(QString(ui->txtLogin->text()).isEmpty())
           {
              labelAnimation(ui->lblLogin, 250, 92, 332, 120, 13);

           }
           if(QString(ui->txtPassword->text()).isEmpty())
           {
              labelAnimation(ui->lblPassword, 250, 92, 378, 120, 13);

           }
           ui->txtPassword->clearFocus();
           ui->txtLogin->clearFocus();
        }
    }
    if(event->type() == QEvent::FocusOut)
    {
        if(object == ui->txtLogin && QString(ui->txtLogin->text()).isEmpty())
        {
            labelAnimation(ui->lblLogin, 250, 92, 332, 120, 13);
        }
        if(object == ui->txtPassword && QString(ui->txtPassword->text()).isEmpty())
        {
            labelAnimation(ui->lblPassword, 250, 92, 378, 120, 13);
        }
    }
    return false;
}

void LoginForm::mousePressEvent(QMouseEvent *event)
{
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();    
}

void LoginForm::mouseMoveEvent(QMouseEvent *event)
{
    if(m_nMouseClick_X_Coordinate >= 0 && m_nMouseClick_X_Coordinate <= 497 &&
            m_nMouseClick_Y_Coordinate >=0 && m_nMouseClick_Y_Coordinate <= 30)
    {
        move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
    }
}


