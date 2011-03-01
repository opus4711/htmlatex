#include "ctranslationmapper.h"

CTranslationMapper::CTranslationMapper()
{
};
void CTranslationMapper::createInputElementMap(QString inputfilepath)
{
};
void CTranslationMapper::createOutputElementMap(QString outputfilepath)
{
    outputMap = QMap<QString,CTranslationData>();
    QFile file(outputfilepath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        std::cerr << "\nCTranslationMapper.createOutputElementMap(): file.open() returned false: path: " << outputfilepath.toStdString();
        return;
    }
    // load content of the XML file into "filecontent"
    QString filecontent = QString(file.readAll()).toLatin1();
    file.close();
    QDomDocument doc;
    QString errorMsg = "";
    int errorLine = -1;
    int errorColumn = -1;
    if (doc.setContent(filecontent, &errorMsg, &errorLine, &errorColumn))
        ;
    else
        std::cerr << "\nCTranslationMapper.createOutputElementMap(): doc.setContent returned false: filecontent: " << filecontent.toStdString();
};
