#ifndef OFFICEFORM_H
#define OFFICEFORM_H

#include <QWidget>
#include <QMdiSubWindow>

namespace Ui {
    class OfficeForm;
}

class OfficeView : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit OfficeView(QWidget *parent = 0);
    ~OfficeView();

private:
    Ui::OfficeForm *ui;
};

#endif // OFFICEFORM_H
