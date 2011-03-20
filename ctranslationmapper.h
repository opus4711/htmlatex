#ifndef CTRANSLATIONMAPPER_H
#define CTRANSLATIONMAPPER_H

#include "ctranslationdata.h"
#include "settings.h"
#include "documentreaderdata.h"
#include <QFile>
#include <QDomDocument>
#include <QString>
#include <QMap>
#include <iostream>

class CTranslationMapper
{
private:
    DocumentReaderData* _documentReference;
    QMap<QString,CTranslationData> _outputMap;
public:
    void createDocumentReaderData(QString inputfilepath);
    void createOutputElementMap(QString outputfilepath);
    DocumentReaderData* getDocumentReference() const;
    QMap<QString,CTranslationData> outputMap() const;
    // Constructor
    CTranslationMapper();
    ~CTranslationMapper();
};

#endif // CTRANSLATIONMAPPER_H
