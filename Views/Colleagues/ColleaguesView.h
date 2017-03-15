#ifndef COLLEAGUESFORM_H
#define COLLEAGUESFORM_H

#include <QWidget>
#include <QMdiSubWindow>

namespace Ui {
    class ColleaguesForm;
}

class ColleaguesForm : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit ColleaguesForm(QWidget *parent = 0);
    ~ColleaguesForm();

private:
    Ui::ColleaguesForm *ui;
};

#endif // COLLEAGUESFORM_H
