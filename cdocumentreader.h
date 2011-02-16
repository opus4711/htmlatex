#ifndef CDOCUMENTREADER_H
#define CDOCUMENTREADER_H

#include "cnode.h"
#include "cdocumentdata.h"
#include <QString>
#include <QDomDocument>
#include <QDomNamedNodeMap>
#include <QMapIterator>
#include <QStack>

class CDocumentReader
{
private:
    QFileInfo _indexFileInfo;
    CDocumentData::FileType _fileType;
    QStack<CDocumentData*> _documentStack;
    void readElement(QDomElement element, CNode* node);
public:
    CNode* read(QString indexfilepath, CDocumentData::FileType filetype);
    // constructor
    CDocumentReader();
};

#endif // CDOCUMENTREADER_H
