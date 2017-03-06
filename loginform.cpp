#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    connect(ui->btnLogin, SIGNAL(clicked()), this, SLOT(login()));

    ui->lineEditLogin->installEventFilter(this);
    ui->lineEditPassword->installEventFilter(this);
    ui->labelLogin->installEventFilter(this);
    ui->labelPassword->installEventFilter(this);

    ui->labelIncorrectLogin->hide();
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
            labelAnimation(ui->labelLogin, 250, 122, 190, 60, 13 );
            ui->labelIncorrectLogin->hide();
        }
        if(object == ui->lineEditPassword || object == ui->labelPassword)
        {
            labelAnimation(ui->labelPassword, 250, 122, 230, 60, 13 );
            ui->labelIncorrectLogin->hide();
        }
    }
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(object == ui->labelLogin)
        {
            labelAnimation(ui->labelLogin, 250, 122, 190, 60, 13 );
            ui->labelIncorrectLogin->hide();
            ui->lineEditLogin->setFocus();
        }
        if(object == ui->labelPassword)
        {
            labelAnimation(ui->labelPassword, 250, 122, 230, 60, 13);
            ui->labelIncorrectLogin->hide();
            ui->lineEditPassword->setFocus();
        }
    }
    if(event->type() == QEvent::FocusOut)
    {
        if(object == ui->lineEditLogin && QString(ui->lineEditLogin->text()).isEmpty())
        {
            labelAnimation(ui->labelLogin, 250, 122, 208, 60, 13);
        }
        if(object == ui->lineEditPassword && QString(ui->lineEditPassword->text()).isEmpty())
        {
            labelAnimation(ui->labelPassword, 250, 122, 248, 60, 13 );
        }
    }
    return false;
}


