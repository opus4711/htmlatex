#ifndef CTRANSLATIONMAPPER_H
#define CTRANSLATIONMAPPER_H

#include <QFile>
#include <QDomDocument>
#include <QString>

#include <iostream>

class CTranslationMapper
{
private:
    QString INPUT_JAVADOC_FILEPATH;
    QString OUTPUT_TEX_FILEPATH;
public:
    CTranslationMapper();
};

#endif // CTRANSLATIONMAPPER_H
