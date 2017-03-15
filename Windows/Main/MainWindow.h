#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Views/Colleagues/ColleaguesView.h"
#include "Views/Office/OfficeView.h"
#include "Views/Salary/SalaryView.h"
#include <QDebug>
#include <QMetaObject>
#include <typeinfo>


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
};

#endif // MAINWINDOW_H
