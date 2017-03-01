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

bool LoginForm::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::FocusIn)
    {
        if(object == ui->lineEditLogin || qobject_cast<QLabel*>(object) == ui->labelLogin)
        {            
           ui->labelLogin->setGeometry(122,190,60,13);
           ui->labelIncorrectLogin->hide();
        }
        if(object == ui->lineEditPassword || object == ui->labelPassword)
        {
            ui->labelPassword->setGeometry(122, 230, 60, 13);
            ui->labelIncorrectLogin->hide();
        }
    }
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(object == ui->labelLogin)
        {
           ui->labelLogin->setGeometry(122,190,60,13);
           ui->lineEditLogin->setFocus();
        }
        if(object == ui->labelPassword)
        {
            ui->labelPassword->setGeometry(122, 230, 60, 13);
            ui->lineEditPassword->setFocus();
        }
    }
    if(event->type() == QEvent::FocusOut)
    {
        if(object == ui->lineEditLogin && QString(ui->lineEditLogin->text()).isEmpty())
        {
            ui->labelLogin->setGeometry(122,208,60,13);
        }
        if(object == ui->lineEditPassword && QString(ui->lineEditPassword->text()).isEmpty())
        {
            ui->labelPassword->setGeometry(122, 248, 60, 13);
        }
    }
    return false;
}


