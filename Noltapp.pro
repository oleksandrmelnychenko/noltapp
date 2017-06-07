#-------------------------------------------------
#
# Project created by QtCreator 2017-02-24T13:54:55
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD

TARGET = Noltapp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    Views\Colleagues\ColleaguesView.cpp \
    Windows\CustomShadoweffect.cpp \
    Windows\Login\LoginWindow.cpp \
    Windows\Main\MainWindow.cpp \
    Views\Office\OfficeView.cpp \
    Views\Salary\SalaryView.cpp \
    CommonUiControllers/Login/LoginController.cpp \
    CommonUiControllers/WindowController.cpp \
    Entities/BaseEntity.cpp \
    Entities/PersonEntity.cpp \
    Views/Colleagues/AddCollegueView.cpp \
    Views/Colleagues/UpdateCollegueView.cpp \
    WebServices/ColleagueServices.cpp \
    Repositories/ColleagueOperationRepository.cpp \
    CommonUiControllers/RegexController.cpp \
    Repositories/SalaryOperationRepository.cpp \
    Services/ColleagueService.cpp \
    Services/SalaryServiece.cpp \
    Views/Budget/BudgetView.cpp \
    Repositories/OfficeOpearationRepository.cpp \
    Repositories/BudgetOperationRepository.cpp \
    Services/OfficeService.cpp \
    Services/BudgetService.cpp \
    Views/Budget/CurrentBudgetInformationView.cpp

HEADERS  += \
    Views\Colleagues\ColleaguesView.h \
    Windows\CustomShadoweffect.h \
    Windows\Login\LoginWindow.h \
    Windows\Main\MainWindow.h \
    Views\Office\OfficeView.h \
    Views\Salary\SalaryView.h \
    CommonUiControllers/Login/LoginController.h \
    CommonUiControllers/Login/LoginLabels.h \
    CommonUiControllers/Login/LoginLineEdits.h \
    CommonUiControllers/AnimationController.h \
    CommonUiControllers/WindowController.h \
    Entities/BaseEntity.h \
    Entities/PersonEntity.h \
    Views/Colleagues/AddCollegueView.h \
    CommonUiControllers/Views/Colleagues/ColleaguesLineEditd.h \
    CommonUiControllers/Views/Colleagues/ColleaguesLabel.h \
    CommonUiControllers/Views/Salary/SalaryLabel.h\
    Views/Colleagues/UpdateCollegueView.h \
    WebServices/ColleagueServices.h \
    Repositories/ColleagueOperationRepository.h \
    CommonUiControllers/RegexController.h \
    CommonUiControllers/Views/Salary/SalaryLineEdit.h \
    Repositories/SalaryOperationRepository.h \
    Services/ColleagueService.h \
    Services/SalaryServiece.h \
    CommonUiControllers/Views/Office/OfficeLineEdit.h \
    CommonUiControllers/Views/Office/OfficeLabel.h \
    CommonUiControllers/Views/Budget/BudgetLabel.h \
    Views/Budget/BudgetView.h \
    CommonUiControllers/Views/Budget/BudgetLineEdit.h \
    Repositories/OfficeOpearationRepository.h \
    Repositories/BudgetOperationRepository.h \
    Services/OfficeService.h \
    Services/BudgetService.h \
    Views/Budget/CurrentBudgetInformationView.h \
    CommonUiControllers/Views/Budget/BudgetType.h

FORMS    += \
    Views\Colleagues\ColleaguesView.ui \
    Views\Salary\SalaryView.ui \
    Views\Office\OfficeView.ui \
    Windows\Login\LoginWindow.ui \
    Windows\Main\MainWindow.ui \
    Views/Colleagues/AddCollegueView.ui \
    Views/Colleagues/UpdateCollegueView.ui \
    Views/Budget/BudgetView.ui \
    Views/Budget/CurrentBudgetInformationView.ui

RESOURCES += \
    images.qrc
