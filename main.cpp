#include <QApplication>
#include <QObject>
#include <CommonUiControllers/WindowController.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDesktopWidget* desktop = QApplication::desktop();
    WindowController wc(desktop->width(), desktop->height());

    return a.exec();
}
