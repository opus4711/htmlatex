#ifndef CDOCUMENTREADER_H
#define CDOCUMENTREADER_H

#include "cnode.h"
#include "cdocumentdata.h"
#include "ctranslationmapper.h"
#include "settings.h"
#include <QString>
#include <QDomDocument>
#include <QDomNamedNodeMap>
#include <QMapIterator>
#include <QStack>
#include <QDir>

#include <iostream>

class CDocumentReader
{
private:
    QFileInfo _indexFileInfo;
    CDocumentData::FileType _fileType;
    QStack<CDocumentData*> _documentStack;
    CTranslationMapper* _translationMapper;
    void readElement(QDomElement element, CNode* node);
public:
    CNode* read(QString indexfilepath, CDocumentData::FileType filetype);
    // constructor
    CDocumentReader(CTranslationMapper* translationmapper);
};

#endif // CDOCUMENTREADER_H
