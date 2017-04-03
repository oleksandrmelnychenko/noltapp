#ifndef COLLEAGUESFORM_H
#define COLLEAGUESFORM_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QVector>
#include <QLabel>

#include "Entities/PersonEntity.h"

namespace Ui {
    class ColleaguesForm;
}

class ColleaguesForm : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit ColleaguesForm(QWidget *parent = 0);
    ~ColleaguesForm();

public slots:   
    void LoadData();
    void DoSmthWithObject(int row, int column);

private:
    Ui::ColleaguesForm *ui;

    QVector<PersonEntity> mColleguesVector;
    PersonEntity mCurrentCollegue;
    int mCounter = 0;
};

#endif // COLLEAGUESFORM_H
