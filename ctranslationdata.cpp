#include "ctranslationdata.h"

CTranslationData::CTranslationData() : _from(""), _to("")
{
    this->_requires = QList<CTranslationDataNode>();
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
QList<CTranslationDataNode> CTranslationData::requires() const
{
    return this->_requires;
};
void CTranslationData::addRequiresNode(CTranslationDataNode requiresnode)
{
    this->_requires.append(requiresnode);
};
