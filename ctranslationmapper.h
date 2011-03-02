#ifndef CTRANSLATIONMAPPER_H
#define CTRANSLATIONMAPPER_H

#include "ctranslationdata.h"
#include <QFile>
#include <QDomDocument>
#include <QString>
#include <QMap>

#include <iostream>

class CTranslationMapper
{
private:
    QMap<QString,CTranslationData> _outputMap;
public:
    void createInputElementMap(QString inputfilepath);
    void createOutputElementMap(QString outputfilepath);
    QMap<QString,CTranslationData> outputMap() const;
    // Constructor
    CTranslationMapper();
};

#endif // CTRANSLATIONMAPPER_H
