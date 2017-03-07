#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "colleaguesform.h"
#include "officeform.h"
#include "salaryform.h"
#include <QDebug>
#include <QMetaObject>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected slots:
    void createColleaguesForm();
    void createOfficeForm();
    void createSalaryForm();
    void deleteMdiSubForm(QMdiSubWindow *form);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;    

    QMdiSubWindow* mCurrentMdiSubForm = 0;
    ColleaguesForm* mColleaguesForm = 0 ;
    OfficeForm* mOfficeForm = 0;
    SalaryForm* mSalaryForm = 0;

};

#endif // MAINWINDOW_H
