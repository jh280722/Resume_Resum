#include "mainwindow.h"

#include <QApplication>
#include <QtGlobal>
#include <QDesktopWidget>
float DPI;
int main(int argc, char *argv[])
{

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    DPI = (a.desktop()->logicalDpiX()/96.0);
    MainWindow w;
    w.show();
    return a.exec();
}
