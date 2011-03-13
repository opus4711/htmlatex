#include "cconsole.h"
#include "cconverter.h"

/** This class performs the format conversion via console input and output.
  * @author Bjoern Kaiser
  */
CConsole::CConsole(QStringList arguments, QStringList options)
{
    performInitialOperations(arguments, options);
};
CConsole::~CConsole()
{
};
void CConsole::performInitialOperations(QStringList arguments, QStringList options)
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
        translationmapper->createInputElementMap(inputdefinitionfilepath);
        QFile file(sourcefilepath);
        CNode* root = 0;
        if (file.exists())
        {
            CDocumentData::FileType filetype = CDocumentData::Unknown;
            if (filetypestring.toLower() == "javadoc")
                filetype = CDocumentData::JavaDocHTML;
            CDocumentReader* reader = new CDocumentReader;
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
            CConverter* converter = new CConverter(targetfilepath, root, translationmapper);
            // converter->convert();
            std::cout << tr("Perform conversion  --> success").toStdString() << std::endl;
            delete converter;
        }
        else
            std::cout << tr("I/O error - can't write to file: ").toStdString()
                    << targetfilepath.toStdString() << std::endl;
        delete translationmapper;
    }
    else
        std::cout << tr("Error - unexpected number of arguments.").toStdString() << std::endl;
};
