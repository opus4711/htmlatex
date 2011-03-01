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
    QMap<QString,CTranslationData> outputMap;
public:
    void createInputElementMap(QString inputfilepath);
    void createOutputElementMap(QString outputfilepath);
    // Constructor
    CTranslationMapper();
};

#endif // CTRANSLATIONMAPPER_H
