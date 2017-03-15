#ifndef SALARYFORM_H
#define SALARYFORM_H

#include <QWidget>
#include <QMdiSubWindow>

namespace Ui {
    class SalaryForm;
}

class SalaryForm : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit SalaryForm(QWidget *parent = 0);
    ~SalaryForm();

private:
    Ui::SalaryForm *ui;
};

#endif // SALARYFORM_H
