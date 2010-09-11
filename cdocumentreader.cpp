#include "cdocumentreader.h"

CDocumentReader::CDocumentReader()
{
};
CNode* CDocumentReader::read(QString path)
{
    QDomDocument doc;
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox msg(QMessageBox::Warning, QObject::tr("Error"), QObject::tr("IO-Error"));
        msg.exec();
        return 0;
    }
    QString errorStr = "";
    int errorLine = -1;
    int errorColumn = -1;
    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn))
    {
        QMessageBox msg(QMessageBox::Warning, QObject::tr("Error"), errorStr);
        msg.exec();
        return 0;
    }
    QDomElement docroot = doc.documentElement();
    if (docroot.tagName().toLower() != QString("html"))
    {
        QMessageBox msg(QMessageBox::Warning, QObject::tr("Error - No valid HTML file."), QObject::tr("The root element <html> is missing."));
        msg.exec();
        return 0;
    }
    // begin reading...
    CNode* root = new CNode(0);
    return root;
};
