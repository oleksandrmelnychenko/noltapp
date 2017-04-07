#ifndef UPDATECOLLEGUEVIEW_H
#define UPDATECOLLEGUEVIEW_H

#include <QWidget>
#include <QMdiSubWindow>

namespace Ui {
    class UpdateCollegueView;
}

class UpdateCollegueView : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit UpdateCollegueView(QWidget *parent = 0, long id = 0);
    ~UpdateCollegueView();

private:
    Ui::UpdateCollegueView *ui;

    long mIdUpdatedCollegue;
};

#endif // UPDATECOLLEGUEVIEW_H
