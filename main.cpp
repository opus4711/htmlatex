#include <QtGui/QApplication>
#include <QtCore/QCoreApplication>

#include "mainwindow.h"
#include "cconsole.h"
#include "constants.h"

bool DEBUG = false;
int main(int argc, char* argv[])
{
    /* 0 = executable's name
       1 = source file path
       2 = source file type
       3 = target file path
       4 = target file type
       5 = "-g" or "--gui"
    */
    // open the GUI if argument "-g" or "--gui" is given
    bool showgui = false;
    for (int i = 0; i < argc; i++)
    {
        if ((QString(argv[i]).toLower() == "-g")
            | (QString(argv[i]).toLower() == "--gui"))
        {
            showgui = true;
            break;
        }
    }
    if (showgui)
    {
        QApplication a(argc, argv);
        MainWindow w(argc, argv, 0);
        w.show();
        return a.exec();
    }
    else if (argc == 1)
        std::cerr << "the argument \"-g\" or \"--gui\" launches the GUI\n"
                << "\"-h\" or \"--help\" shows some examples\n"
                << "for further information read the \"README\" file" << std::endl;
    else if (argc == 2)
    {
        if ((QString(argv[1]).toLower() == "-h")
            | (QString(argv[1]).toLower() == "--help"))
        {
            QString helpstring("Examples with GUI:\n\nopen file initially:\n\nhtmlatex index.html javadoc -g\nhtmlatex index.html --gui javadoc");
            helpstring += "\n\nconvert file initially:\n\nhtmlatex -g index.html javadoc mytexoutput.tex tex\nhtmlatex index.html javadoc --gui mytexoutput.tex tex";
            helpstring += "\n\nExample with console:\n\nconvert file:\n\nhtmlatex index.html javadoc mytexoutput.tex tex";
            std::cerr << helpstring.toStdString() << std::endl;
        }
    }
    else
    {
        QCoreApplication a(argc, argv);
        CConsole console(argc, argv);
        exit(0);
        return a.exec();
    }
};
