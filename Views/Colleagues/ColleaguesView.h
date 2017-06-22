#ifndef COLLEAGUESFORM_H
#define COLLEAGUESFORM_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QLabel>
#include <QTableWidgetItem>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

#include "Entities/PersonEntity.h"
#include "Services/ColleagueService.h"

namespace Ui {
    class ColleaguesForm;
}

class ColleaguesView : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit ColleaguesView(QWidget *parent = 0);
    ~ColleaguesView();

private slots:
    void LoadAllColleagues();
    void OutputColleagues(QJsonObject *result);

private:    
    void SetBusyIndicator();
    void SetTableColumnsWidth();
    void SetTableColumnOptions();    

protected slots:
    void CreateAddCollegueView();
    void UpdateCurrentCollegues(int row, int);

signals:
    void clickedNewLabel();
    void updateCurrentCollegues(long);

private:
    Ui::ColleaguesForm *ui;

    QMovie *mMovie;    
};

#endif // COLLEAGUESFORM_H
