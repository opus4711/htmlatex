#include <QtGui/QApplication>
#include <QtCore/QCoreApplication>

#include "mainwindow.h"
#include "cconsole.h"
#include "settings.h"
#include <QString>
#include <QTranslator>
#include <QTextCodec>

int main(int argc, char* argv[])
{
    /* 0 = executable's name
       1 = source file path
       2 = source file type
       3 = target file path
       4 = target file type
       x = "-g" or "--gui"
       y = "-v" or "--verbose"
    */
    QStringList arguments;
    QStringList options;
    for (int i = 1; i < argc; i++)
    {
        QString argument(argv[i]);
        argument = argument.toLower();
        if (argument.startsWith('-'))
            options << argument;
        else
            arguments << argument;
    }
    // open the GUI if argument "-g" or "--gui" is given
    if ((bool)options.contains("-g")
        | (bool)options.contains("--gui"))
    {
        QApplication a(argc, argv);
        MainWindow w(arguments, options, 0);
        w.show();
        return a.exec();
    }
    else if (argc == 1)
        std::cerr << "usage: htmlatex INPUTFILE FORMAT INPUTDEFINITION OUTPUTFILE FORMAT OUTPUTDEFINITION [-g|--gui]\n"
                << "  e.g. htmlatex index.html javadoc input_javadoc.xml manual.tex tex output_tex.xml -g\n"
                << "\t-g, --gui \tLaunch the GUI\n"
                << "\t-h, --help \tShow some examples\n"
                << "\t-v, --verbose \tVerbose mode\n"
                << "\t-lang=de, -lang=en \tSets the language to German or English\n\n"
                << "\tSee the \"README\" file for further information." << std::endl;
    else if (argc == 2)
    {
        if ((bool)options.contains("-h")
            | (bool)options.contains("--help"))
        {
            QString helpstring("Examples with GUI:\n\nopen file initially:\n\nhtmlatex index.html javadoc -g\nhtmlatex index.html --gui javadoc");
            helpstring += "\n\nconvert file initially:\n\nhtmlatex -g index.html javadoc mytexoutput.tex tex\nhtmlatex index.html javadoc --gui mytexoutput.tex tex";
            helpstring += "\n\nExample with console:\n\nconvert file:\n\nhtmlatex index.html javadoc mytexoutput.tex tex";
            std::cerr << helpstring.toStdString() << std::endl;
        }
    }
    else
    {
        Settings settings;
        if ((bool)options.contains("-v")
            | (bool)options.contains("--verbose"))
        {
            settings.setValue("verbose", "1");
            std::cerr << "verbose mode" << std::endl;
        }
        else
            settings.setValue("verbose", "0");
        if ((bool)options.contains("-lang=de")
            | (bool)options.contains("-lang=en"))
        {
            if ((bool)options.contains("-lang=de"))
            {
                settings.setValue("language", QString::number((int)QLocale::Germany));
                std::cerr << "language set to German" << std::endl;
            }
            else
            {
                settings.setValue("language", QString::number((int)QLocale::C));
                std::cerr << "language set to English" << std::endl;
            }
        }
        QCoreApplication a(argc, argv);
        // Set translation environment for the application texts
        QLocale::Country language = (QLocale::Country)settings.getValue("language").toInt();
        QTranslator translator;
        if (language == QLocale::Germany)
            translator.load(QString("htmlatex_de.qm"));
        else
            translator.load(QString("htmlatex_en.qm"));
        a.installTranslator(&translator);
        QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
        CConsole console(arguments, options);
        // Invoke external program and write the output to a file
//        system("ping -c 4 192.168.1.1>>ping_test.txt");
        exit(0);
        return a.exec();
    }
};
