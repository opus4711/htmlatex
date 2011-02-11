#ifndef CDOCUMENTREADER_H
#define CDOCUMENTREADER_H

#include "cnode.h"
#include <QObject>
#include <QString>
#include <QFile>
#include <QDir>
#include <QDomDocument>
#include <QMessageBox>
#include <QDomNamedNodeMap>
#include <QTextStream>
#include <QMapIterator>

class CDocumentReader
{
private:
    enum FileType { JavaDocHTML, HTML, Tex, Unknown };
    QFileInfo _sourceFileInfo;
    FileType fileType;
    void readElement(QDomElement element, CNode* node);
    CNode* read(QString path);
    void preprocessingHook(QString path);
    void preprocessJavaDocHTML(QString path);
    QString nodeToString(CNode* node, int ebene);
public:
    CNode* read(QString sourcefilepath, QString filefilter);
    QString toString(CNode* root);
    // constructor
    CDocumentReader();
};

#endif // CDOCUMENTREADER_H
