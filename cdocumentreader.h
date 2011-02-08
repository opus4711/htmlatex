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

class CDocumentReader
{
private:
    QFileInfo _sourceFileInfo;
    void readElement(QDomElement element, CNode* node);
    CNode* read(QString path);
public:
    CNode* read();
    // constructor
    CDocumentReader(QString path);
};

#endif // CDOCUMENTREADER_H
