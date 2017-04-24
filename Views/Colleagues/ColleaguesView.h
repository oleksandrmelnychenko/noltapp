#ifndef COLLEAGUESFORM_H
#define COLLEAGUESFORM_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QVector>
#include <QLabel>
#include <QTableWidgetItem>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

#include "Entities/PersonEntity.h"
#include "Repositories/ColleagueOperationRepository.h"

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

public slots:    
    void CreateAddCollegueView();


protected slots:
    void UpdateCurrentCollegues(int row, int column);

    void ResultFromRequest(QJsonObject *result);

signals:
    void clickedNewLabel();
    void updateCurrentCollegues(long);

private:
    Ui::ColleaguesForm *ui;

    ColleagueOperationRepository *mRepository;    
    int mCounter = 0;    
};

#endif // COLLEAGUESFORM_H
