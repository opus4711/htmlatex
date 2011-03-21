#ifndef TRANSLATIONMAPPER_H
#define TRANSLATIONMAPPER_H

#include "translationdata.h"
#include "settings.h"
#include "documentreaderdata.h"
#include <QFile>
#include <QDomDocument>
#include <QString>
#include <QMap>
#include <iostream>

class TranslationMapper
{
public:
    TranslationMapper();
private:
    DocumentReaderData _documentReference;
    QMap<QString,TranslationData> _outputMap;
public:
    void createDocumentReaderData(QString inputfilepath);
    void createOutputElementMap(QString outputfilepath);
    DocumentReaderData getDocumentReference() const;
    QMap<QString,TranslationData> outputMap() const;
};

#endif // TRANSLATIONMAPPER_H
