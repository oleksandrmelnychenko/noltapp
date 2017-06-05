#ifndef CURRENTBUDGETINFORMATIONVIEW_H
#define CURRENTBUDGETINFORMATIONVIEW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QLineEdit>

namespace Ui {
    class CurrentBudgetInformationView;
}

class CurrentBudgetInformationView : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit CurrentBudgetInformationView(QWidget *parent = 0, long id = 0);
    ~CurrentBudgetInformationView();

private:
    Ui::CurrentBudgetInformationView *ui;

    QJsonObject mJsonObject;

    long mId;
};

#endif // CURRENTBUDGETINFORMATIONVIEW_H
