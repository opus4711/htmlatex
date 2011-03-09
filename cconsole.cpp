#include "cconsole.h"
#include "cconverter.h"

/** This class performs the format conversion via console input and output.
  * @author Bjoern Kaiser
  */
CConsole::CConsole(int argc, char* argv[])
{
    performInitialOperations(argc, argv);
};
CConsole::~CConsole()
{
};
void CConsole::performInitialOperations(int argc, char* argv[])
{
    /* 0 = executable's name
       1 = source file path
       2 = source file type
       3 = target file path
       4 = target file type
       5 = "-g" or "--gui"
    */
    if (argc == 5)
    {
        QString sourcefilepath(argv[1]);
        QString filetypestring(argv[2]);
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
        QString targetfilepath(argv[3]);
        filetypestring = QString(argv[4]);
        file.setFileName(targetfilepath);
        if (file.open(QFile::WriteOnly))
        {
            CDocumentData::FileType filetype = CDocumentData::Unknown;
            if (filetypestring.toLower() == "tex")
                filetype = CDocumentData::Tex;
            // root - converting...
            CConverter* converter = new CConverter(targetfilepath, root);
//            converter->convert();
            std::cout << tr("Perform conversion  --> success").toStdString() << std::endl;
        }
        else
            std::cout << tr("I/O error - can't write to file: ").toStdString()
                    << targetfilepath.toStdString() << std::endl;
    }
    else
        std::cout << tr("Error - unexpected number of arguments.").toStdString() << std::endl;
};
