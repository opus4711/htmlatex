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
    QFileInfo sourceFileInfo;
    void readElement(QDomElement element, CNode* node);
public:
    CNode* read(QString path);
    // constructor
    CDocumentReader();
};

#endif // CDOCUMENTREADER_H
