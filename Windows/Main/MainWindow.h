#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Views/Colleagues/ColleaguesView.h"
#include "Views/Colleagues/AddCollegueView.h"
#include "Views/Colleagues/UpdateCollegueView.h"
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
    void SetPressButtonStyleSheet(QPushButton *pressedButton, QPushButton *secondButton, QPushButton *thirdButton);
    bool isMousePointerInFrame();

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);

protected slots:
    void createColleaguesView();
    void createAddColeagueView();
    void createUpdateColleagueView(long id);

    void createOfficeView();
    void createSalaryView();
    void deleteMdiSubForm(QMdiSubWindow *form);
    void collapseMainWindow();

    void UpdateColleagueRequestStatus(const QString& status);
    void UpdateColleagueDeleteRequestStatus(const QString& status);
    void AddColleagueRequestStatus(const QString& status);
    void setlblRequestStatusVisibleToFalse();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    const int mFrameStartPointX = 170;
    const int mFrameStartPointY = 0;
    const int mFrameWidth = 1111;
    const int mFrameHeight = 21;

    int mMouseClickXCoordinate;
    int mMouseClickYCoordinate;

    QMdiSubWindow* mCurrentMdiSubForm = 0;

    int mlbRequestStatusForlUpdateColleagueXPosition = 1061;
    int mlbRequestStatusForlUpdateColleagueYPosition = 630;
    int mlbRequestStatusForlUpdateColleagueWidth = 240;
    int mlbRequestStatusForlUpdateColleagueHeight = 31;

    int mlblRequestStatusForAddColleagueXPosition = 1037;
    int mlblRequestStatusForAddColleagueYPosition = 630;
    int mlblRequestStatusForAddColleagueWidth = 265;
    int mlblRequestStatusForAddColleagueHeight = 31;

    int mlblRequestStatusForDeleteColleagueXPosition = 1065;
    int mlblRequestStatusForDeleteColleagueYPosition = 630;
    int mlblRequestStatusForDeleteColleagueWidth = 240;
    int mlblRequestStatusForDeleteColleagueHeight = 31;
};

#endif // MAINWINDOW_H
