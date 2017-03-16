#-------------------------------------------------
#
# Project created by QtCreator 2017-02-24T13:54:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    CommonUiControllers/Login/EventFilters/LabelsEventFilters.cpp \
    CommonUiControllers/Login/EventFilters/LineEditsEventFilters.cpp

HEADERS  += \
    Views\Colleagues\ColleaguesView.h \
    Windows\CustomShadoweffect.h \
    Windows\Login\LoginWindow.h \
    Windows\Main\MainWindow.h \
    Views\Office\OfficeView.h \
    Views\Salary\SalaryView.h \
    CommonUiControllers/Login/LoginController.h \
    CommonUiControllers/Login/EventFilters/LabelsEventFilters.h \
    CommonUiControllers/Login/EventFilters/LineEditsEventFilters.h

FORMS    += \
    Views\Colleagues\ColleaguesView.ui \
    Views\Salary\SalaryView.ui \
    Views\Office\OfficeView.ui \
    Windows\Login\LoginWindow.ui \
    Windows\Main\MainWindow.ui

RESOURCES += \
    images.qrc
