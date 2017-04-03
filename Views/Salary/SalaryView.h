#ifndef SALARYFORM_H
#define SALARYFORM_H

#include <QWidget>
#include <QMdiSubWindow>

namespace Ui {
    class SalaryForm;
}

class SalaryView : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit SalaryView(QWidget *parent = 0);
    ~SalaryView();

private:
    Ui::SalaryForm *ui;
};

#endif // SALARYFORM_H
