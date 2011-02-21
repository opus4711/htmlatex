#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>

#include "mainwindow.h"
#include <QMessageBox>

int main(int argc, char* argv[])
{
    // argc[0] contains the executable's name
    if (argc == 1)
    {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }
    else
    {
        QCoreApplication a(argc, argv);
        return a.exec();
    }
};
