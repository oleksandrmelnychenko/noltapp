#ifndef ADDCOLLEGUEVIEW_H
#define ADDCOLLEGUEVIEW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QVector>
#include <QLabel>
#include <QUuid>
#include <QDate>
#include <QLineEdit>

#include "Entities/PersonEntity.h"

namespace Ui {
    class AddCollegueView;
}

class AddCollegueView : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit AddCollegueView(QWidget *parent = 0);
    ~AddCollegueView();    

    QString getInformationFromLineEdit(QLineEdit *lineEdit);

protected slots:
    void addCollegue();
    void validateLineEditInput(QLineEdit *lineEdit, QString regPatern, bool *isValid);
    void focusIn(QLineEdit *lineEdit);

protected:    
    void SubscribeToFormEvents();
    bool IsLineEditsEmpty();
    bool IsLineEditsValid();

private:
    Ui::AddCollegueView *ui;

    QVector<PersonEntity> mColleguesVector;
    int mCounter = 0;    

    QString mRegName = ("[a-zA-Z0-9_\\-\\.]{1,30}");
    QString mRegEmail = ("([a-zA-Z0-9_\\-\\.]+)@([a-zA-Z0-9_.-])+\\.([a-zA-Z]{2,4}|[0-9]{1,3})");
    QString mRegPhone = ("\\([0-9]{3}\\)\\s[0-9]{3}-[0-9]{2}-[0-9]{2}");  // (097) 231-23-52;

    QString mValidateColor = ("border:1px solid black");
    QString mNotValidateColor = ("border:1px solid red");

    bool isFirstNameValid = false;
    bool isLastNameValid = false;
    bool isEmailValid = false;
    bool isPhoneValid = false;

};

#endif // ADDCOLLEGUEVIEW_H
