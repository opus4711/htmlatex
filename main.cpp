#include <QtGui/QApplication>
#include <QtCore/QCoreApplication>
#include <QTranslator>
#include <QTextCodec>

#include "mainwindow.h"
#include "cconsole.h"
#include "constants.h"

bool DEBUG = true;
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
        // Set translation environment for the application texts
        QString locale = QLocale::system().name();
        QTranslator translator;
        translator.load(QString("htmlatex_") + locale);
        a.installTranslator(&translator);
        QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
        MainWindow w(argc, argv, 0);
        w.show();
        return a.exec();
    }
    else if (argc == 1)
        std::cerr << "usage: htmlatex INPUTFILE FORMAT INPUTDEFINITION OUTPUTFILE FORMAT OUTPUTDEFINITION [-g|--gui]\n"
                << "  e.g. htmlatex index.html javadoc input_javadoc.xml manual.tex tex output_tex.xml -g\n"
                << "\t-g, --gui \tLaunch the GUI\n"
                << "\t-h, --help \tShow some examples\n\n"
                << "\tSee the \"README\" file for further information." << std::endl;
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
        // Set translation environment for the application texts
        QString locale = QLocale::system().name();
        QTranslator translator;
        translator.load(QString("htmlatex_") + locale);
        a.installTranslator(&translator);
        QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
        CConsole console(argc, argv);
        // Invoke external program and write the output to a file
//        system("ping -c 4 192.168.1.1>>ping_test.txt");
        exit(0);
        return a.exec();
    }
};
