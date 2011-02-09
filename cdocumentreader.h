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

class CDocumentReader
{
private:
    enum FileType { JavaDocHTML, HTML, Tex, Unknown };
    QFileInfo _sourceFileInfo;
    FileType fileType;
    void readElement(QDomElement element, CNode* node);
    CNode* read(QString path);
    void hook(QString path);
public:
    CNode* read(QString sourcefilepath, QString filefilter);
    // constructor
    CDocumentReader();
};

#endif // CDOCUMENTREADER_H
