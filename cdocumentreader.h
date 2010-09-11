#ifndef CDOCUMENTREADER_H
#define CDOCUMENTREADER_H

#include "cnode.h"
#include <QObject>
#include <QString>
#include <QFile>
#include <QDomDocument>
#include <QMessageBox>

class CDocumentReader
{
public:
    CNode* read(QString path);
    // constructor
    CDocumentReader();
};

#endif // CDOCUMENTREADER_H
