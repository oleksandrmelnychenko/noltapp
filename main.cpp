#include <QApplication>
#include <QObject>
#include <CommonUiControllers/WindowController.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WindowController wc;

    return a.exec();
}
