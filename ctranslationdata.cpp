#include "ctranslationdata.h"

CTranslationData::CTranslationData()
{
};
QString CTranslationData::from() const
{
    return this->_from;
};
void CTranslationData::setFrom(QString from)
{
    this->_from = from;
};
QString CTranslationData::to() const
{
    return this->_to;
};
void CTranslationData::setTo(QString to)
{
    this->_to = to;
};
QMap<QString,QString> CTranslationData::requires() const
{
    return this->_requires;
};
void CTranslationData::setRequires(QMap<QString, QString> requires)
{
    this->_requires = requires;
};
