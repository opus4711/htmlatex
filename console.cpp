#include "console.h"
#include "cconverter.h"

Console::Console(QStringList arguments, QStringList options)
{
    _performInitialOperations(arguments, options);
};
Console::~Console()
{
};
/* This method processes the application's startup arguments and performs the
   conversion by means of a DocumentReader and Converter object.
   */
void Console::_performInitialOperations(QStringList arguments, QStringList options)
{
    /* arguments:
       0 = source file path
       1 = source file type
       2 = input definition file path
       3 = target file path
       4 = target file type
       5 = output definition file path
    */
    if (arguments.count() == 6)
    {
        CTranslationMapper* translationmapper = new CTranslationMapper;
        QString sourcefilepath(arguments.at(0));
        QString filetypestring(arguments.at(1));
        QString inputdefinitionfilepath(arguments.at(2));
        translationmapper->createDocumentReaderData(inputdefinitionfilepath);
        QFile file(sourcefilepath);
        CNode* root = 0;
        if (file.exists())
        {
            CDocumentData::FileType filetype = CDocumentData::Unknown;
            if (filetypestring.toLower() == "javadoc")
                filetype = CDocumentData::JavaDocHTML;
            CDocumentReader* reader = new CDocumentReader(translationmapper);
            root = reader->read(sourcefilepath, filetype);
            delete reader;
            std::cout << tr("Read source file(s) --> success").toStdString() << std::endl;
        }
        else
        {
            file.close();
            std::cout << tr("I/O error - the source file doesn't exit: ").toStdString()
                    << sourcefilepath.toStdString() << std::endl;
            return;
        }
        file.close();
        QString targetfilepath(arguments.at(3));
        filetypestring = QString(arguments.at(4));
        QString outputdefinitionfilepath(arguments.at(5));
        translationmapper->createOutputElementMap(outputdefinitionfilepath);
        file.setFileName(targetfilepath);
        if (file.open(QFile::WriteOnly))
        {
            CDocumentData::FileType filetype = CDocumentData::Unknown;
            if (filetypestring.toLower() == "tex")
                filetype = CDocumentData::Tex;
            // root - converting...
            CConverter* converter = new CConverter(this, translationmapper);
            converter->convert(targetfilepath, root);
            std::cout << tr("Perform conversion  --> success").toStdString() << std::endl;
            delete converter;
        }
        else
            std::cout << tr("I/O error - can't write to file: ").toStdString()
                    << targetfilepath.toStdString() << std::endl;
        delete translationmapper;
    }
    else
    {
        std::cout << tr("Error - unexpected number of arguments.").toStdString() << std::endl;
        std::cerr << "usage: htmlatex INPUTFILE FORMAT INPUTDEFINITION OUTPUTFILE FORMAT OUTPUTDEFINITION [-g|--gui]\n"
                << "  e.g. htmlatex index.html javadoc input_javadoc.xml manual.tex tex output_tex.xml -g\n"
                << "\t-g, --gui \tLaunch the GUI\n"
                << "\t-h, --help \tShow some examples\n\n"
                << "\tSee the \"README\" file for further information." << std::endl;
    }
};
