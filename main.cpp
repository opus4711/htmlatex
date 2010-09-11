#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
};
