#include <QtGui/QApplication>
#include <QtCore/QCoreApplication>

#include "mainwindow.h"
#include "cconsole.h"

int main(int argc, char* argv[])
{
    /* 0 = executable's name
       1 = source file path
       2 = source file type
       3 = target file path
       4 = target file type
       5 = "-g" or "--gui"
    */
    // open the GUI either if no further arguments are given or the last argument
    // is "-g" or "--gui"
    if ((argc == 1)
        | (QString(argv[argc - 1]).toLower() == "-g")
        | (QString(argv[argc - 1]).toLower() == "--gui"))
    {
        QApplication a(argc, argv);
        MainWindow w(argc, argv, 0);
        w.show();
        return a.exec();
    }
    else
    {
        QCoreApplication a(argc, argv);
        CConsole console(argc, argv);
        exit(0);
        return a.exec();
    }
};
