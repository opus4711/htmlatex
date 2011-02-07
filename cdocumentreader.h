#ifndef CDOCUMENTREADER_H
#define CDOCUMENTREADER_H

#include "cnode.h"
#include <QObject>
#include <QString>
#include <QFile>
#include <QDomDocument>
#include <QMessageBox>
#include <QDomNamedNodeMap>

class CDocumentReader
{
private:
    void readElement(QDomElement element, CNode* node);
public:
    CNode* read(QString path);
    // constructor
    CDocumentReader();
};

#endif // CDOCUMENTREADER_H
