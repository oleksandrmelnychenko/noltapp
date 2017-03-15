#ifndef OFFICEFORM_H
#define OFFICEFORM_H

#include <QWidget>
#include <QMdiSubWindow>

namespace Ui {
    class OfficeForm;
}

class OfficeForm : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit OfficeForm(QWidget *parent = 0);
    ~OfficeForm();

private:
    Ui::OfficeForm *ui;
};

#endif // OFFICEFORM_H
