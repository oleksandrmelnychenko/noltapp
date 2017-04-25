#ifndef UPDATECOLLEGUEVIEW_H
#define UPDATECOLLEGUEVIEW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

#include "Repositories/ColleagueOperationRepository.h"
#include "Entities/PersonEntity.h"

namespace Ui {
    class UpdateCollegueView;
}

class UpdateCollegueView : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit UpdateCollegueView(QWidget *parent = 0, long id = 0);
    ~UpdateCollegueView();

protected slots:
    void ResultFromRequest(QJsonObject *result);
    void UpdateCollegue();

private:
    Ui::UpdateCollegueView *ui;

    ColleagueOperationRepository *mRepository;
    QJsonObject mJsonObject;    
};

#endif // UPDATECOLLEGUEVIEW_H
