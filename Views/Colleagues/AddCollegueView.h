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

public slots:
    void AddCollegue();
    bool validateFirstName();
    bool validateLastName();
    bool validateEmail();
    bool validatePhone();

private:
    Ui::AddCollegueView *ui;

    QVector<PersonEntity> mColleguesVector;
    int mCounter = 0;
};

#endif // ADDCOLLEGUEVIEW_H
