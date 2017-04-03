#ifndef ADDCOLLEGUEVIEW_H
#define ADDCOLLEGUEVIEW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QVector>
#include <QLabel>
#include <QUuid>
#include <QDate>

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
    QUuid getNetUiId();
    QString getFirstName();
    QString getLastName();
    QString getEmail();
    QString getPhone();


public slots:
    void AddCollegue();

private:
    Ui::AddCollegueView *ui;

    QVector<PersonEntity> mColleguesVector;
    int mCounter = 0;
};

#endif // ADDCOLLEGUEVIEW_H
