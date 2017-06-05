#ifndef CURRENTBUDGETINFORMATIONVIEW_H
#define CURRENTBUDGETINFORMATIONVIEW_H

#include <QWidget>

namespace Ui {
    class CurrentBudgetInformationView;
}

class CurrentBudgetInformationView : public QWidget
{
    Q_OBJECT

public:
    explicit CurrentBudgetInformationView(QWidget *parent = 0);
    ~CurrentBudgetInformationView();

private:
    Ui::CurrentBudgetInformationView *ui;
};

#endif // CURRENTBUDGETINFORMATIONVIEW_H
