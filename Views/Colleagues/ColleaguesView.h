#ifndef COLLEAGUESFORM_H
#define COLLEAGUESFORM_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QVector>
#include <QLabel>
#include <QTableWidgetItem>

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
    void SetTableColumnsWidth();    

public slots:    
    void CreateAddCollegueView();   

protected slots:
    void UpdateCurrentCollegues(int row, int column);

signals:
    void clickedNewLabel();
    void updateCurrentCollegues(long);

private:
    Ui::ColleaguesForm *ui;

    QVector<PersonEntity> mColleguesVector;
    PersonEntity mCurrentCollegue;
    int mCounter = 0;    
};

#endif // COLLEAGUESFORM_H
