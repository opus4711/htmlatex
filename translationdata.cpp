#include "translationdata.h"

TranslationData::TranslationData() : _key(""),  _from(""), _to("")
{
    this->_requires = QList<TranslationDataNode>();
};
QString TranslationData::from() const
{
    return this->_from;
};
void TranslationData::setFrom(QString from)
{
    this->_from = from;
};
QString TranslationData::key() const
{
    return this->_key;
};
void TranslationData::setKey(QString key)
{
    this->_key = key;
};
QString TranslationData::to() const
{
    return this->_to;
};
void TranslationData::setTo(QString to)
{
    this->_to = to;
};
QList<TranslationDataNode> TranslationData::requires() const
{
    return this->_requires;
};
void TranslationData::addRequiresNode(TranslationDataNode requiresnode)
{
    this->_requires.append(requiresnode);
};
