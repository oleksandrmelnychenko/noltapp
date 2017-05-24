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

private:    
    void SetTableColumnsWidth();
    void SetTableColumnOptions();

    void OutputColleagues(QJsonObject *result);

protected slots:
    void CreateAddCollegueView();
    void UpdateCurrentCollegues(int row, int column);

signals:
    void clickedNewLabel();
    void updateCurrentCollegues(long);

private:
    Ui::ColleaguesForm *ui;

    ColleagueService *mColleagueService;   
};

#endif // COLLEAGUESFORM_H
