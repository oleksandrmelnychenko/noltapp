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

class ColleaguesView : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit ColleaguesView(QWidget *parent = 0);
    ~ColleaguesView();
private:
    void LoadData();

public slots:
    void DoSmthWithObject(int row, int column);
    void CreateAddCollegueView();

signals:
    void clickedNewLabel();

private:
    Ui::ColleaguesForm *ui;

    QVector<PersonEntity> mColleguesVector;
    PersonEntity mCurrentCollegue;
    int mCounter = 0;
};

#endif // COLLEAGUESFORM_H
