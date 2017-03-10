#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent, Qt::FramelessWindowHint | Qt::Window | Qt::CustomizeWindowHint),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    connect(ui->btnLogin, SIGNAL(clicked()), this, SLOT(login()));
    connect(ui->btnQuit, SIGNAL(clicked()), this, SLOT(close()));

    ui->lineEditLogin->installEventFilter(this);
    ui->lineEditPassword->installEventFilter(this);
    ui->labelLogin->installEventFilter(this);
    ui->labelPassword->installEventFilter(this);
    ui->labelPictureCat->installEventFilter(this);
    ui->labelPictureNolt->installEventFilter(this);


    ui->labelIncorrectLogin->hide();

    if(!QString(ui->lineEditLogin->text()).isEmpty())
    {
       ui->labelLogin->setGeometry(92, 314, 120, 14);
    }
    if(!QString(ui->lineEditPassword->text()).isEmpty())
    {
       ui->labelPassword->setGeometry(92, 360, 120, 13);
    }
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::login()
{
    QString inputLogin = ui->lineEditLogin->text();
    QString inputPassword = ui->lineEditPassword->text();

    if(inputLogin == mLogin && inputPassword == mPassword)
    {
        hide();
        mMainWindow = new MainWindow(this);
        mMainWindow->show();
    }
    else
    {
       ui->labelIncorrectLogin->show();
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
        if(object == ui->lineEditLogin || object == ui->labelLogin)
        {
            labelAnimation(ui->labelLogin, 250, 92, 314, 120, 14 );
            ui->labelIncorrectLogin->hide();
        }
        if(object == ui->lineEditPassword || object == ui->labelPassword)
        {
            labelAnimation(ui->labelPassword, 250, 92, 360, 120, 13);
            ui->labelIncorrectLogin->hide();
        }
    }
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(object == ui->labelLogin)
        {
            labelAnimation(ui->labelLogin, 250, 92, 314, 120, 13);
            ui->labelIncorrectLogin->hide();
            ui->lineEditLogin->setFocus();
        }
        if(object == ui->labelPassword)
        {
            labelAnimation(ui->labelPassword, 250, 92, 360, 120, 13);
            ui->labelIncorrectLogin->hide();
            ui->lineEditPassword->setFocus();
        }
        if(object == ui->labelPictureCat || object == ui->labelPictureNolt)
        {
           if(QString(ui->lineEditLogin->text()).isEmpty())
           {
              labelAnimation(ui->labelLogin, 250, 92, 332, 120, 13);

           }
           if(QString(ui->lineEditPassword->text()).isEmpty())
           {
              labelAnimation(ui->labelPassword, 250, 92, 378, 120, 13);

           }
           ui->lineEditPassword->clearFocus();
           ui->lineEditLogin->clearFocus();
        }
    }
    if(event->type() == QEvent::FocusOut)
    {
        if(object == ui->lineEditLogin && QString(ui->lineEditLogin->text()).isEmpty())
        {
            labelAnimation(ui->labelLogin, 250, 92, 332, 120, 13);
        }
        if(object == ui->lineEditPassword && QString(ui->lineEditPassword->text()).isEmpty())
        {
            labelAnimation(ui->labelPassword, 250, 92, 378, 120, 13);
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


