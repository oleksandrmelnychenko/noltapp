#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Windows/CustomShadoweffect.h>
#include "Views/Colleagues/ColleaguesView.h"
#include "Views/Colleagues/AddCollegueView.h"
#include "Views/Colleagues/UpdateCollegueView.h"
#include "Views/Budget/BudgetView.h"
#include "Views/Budget/CurrentBudgetInformationView.h"
#include "Views/Office/OfficeView.h"
#include "Views/Salary/SalaryView.h"
#include <QDebug>
#include <QMetaObject>
#include <typeinfo>
#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void SetPressButtonStyleSheet(QPushButton *pressedButton, QPushButton *secondButton,
                                  QPushButton *thirdButton, QPushButton *fourthButton);
    bool isMousePointerInFrame();

    void setUpShadow();

    void SubscribeToFormEvents();

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent*);

protected slots:
    void createColleaguesView();
    void createAddColeagueView();
    void createUpdateColleagueView(long id);

    void createOfficeView();
    void createSalaryView();

    void createBudgetView();
    void createCurrentBudgetInformationView(long id);
    void deleteMdiSubForm(QMdiSubWindow *form);
    void collapseMainWindow();

    void UpdateColleagueRequestStatus(const QString& status);
    void UpdateColleagueDeleteRequestStatus(const QString& status);
    void AddColleagueRequestStatus(const QString& status);
    void UpdateSalaryStatus(const QString& status);
    void DoPaymentStatus(const QString& status);
    void SetBudgetStatus(const QString& status);
    void DoOfficeExpansesStatus(const QString& status);
    void setlblRequestStatusVisibleToFalse();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    const int mFrameStartPointX = 175;
    const int mFrameStartPointY = 5;
    const int mFrameWidth = 1111;
    const int mFrameHeight = 21;

    int mMouseClickXCoordinate;
    int mMouseClickYCoordinate;

    QMdiSubWindow* mCurrentMdiSubForm = 0;

    // requests message geometry
    int mlbRequestStatusYPosition = 630;
    int mlbRequestStatusHeight = 31;

    int mlbRequestStatusForlUpdateColleagueXPosition = 1061;    
    int mlbRequestStatusForlUpdateColleagueWidth = 240;    

    int mlblRequestStatusForAddColleagueXPosition = 1037;   
    int mlblRequestStatusForAddColleagueWidth = 265;    

    int mlblRequestStatusForDeleteColleagueXPosition = 1065;    
    int mlblRequestStatusForDeleteColleagueWidth = 240;    

    int mlblRequestStatusForUpdateSalaryXPosition = 1018;
    int mlblRequestStatusForUpdateSalaryWidth = 290;

    int mlblRequestStatusForDoPaymentXPosition = 1108;
    int mlblRequestStatusForDoPaymentWidth = 240;

    int mlblRequestStatusSetBudgetXPosition = 1059;
    int mlblRequestStatusSetBudgetWidth = 260;

    int mlblRequestStatusDoOfficeExpansesStatusXPosition = 1009;
    int mlblRequestStatusDoOfficeExpansesStatusWidth = 300;


};

#endif // MAINWINDOW_H
