#ifndef DOCUMENTREADER_H
#define DOCUMENTREADER_H

#include "node.h"
#include "documentdata.h"
#include "translationmapper.h"
#include "settings.h"
#include <QObject>
#include <QString>
#include <QDomDocument>
#include <QDomNamedNodeMap>
#include <QMapIterator>
#include <QStack>
#include <QDir>

#include <iostream>

class DocumentReader : public QObject
{
    Q_OBJECT
private:
    QFileInfo _indexFileInfo;
    DocumentData::FileType _fileType;
    QStack<DocumentData*> _documentStack;
    TranslationMapper* _translationMapper;
    bool _includeSubDocuments;
    void readElement(QDomElement element, Node* node);
public:
    Node* read(QString indexfilepath, DocumentData::FileType filetype);
    // constructor
    DocumentReader(TranslationMapper* translationmapper);
};

#endif // DOCUMENTREADER_H
