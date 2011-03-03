#include "ctranslationdatanode.h"

CTranslationDataNode::CTranslationDataNode() : _name(""),
    _content("")
{
    this->_attributes = QMap<QString,QString>();
};
QString CTranslationDataNode::name() const
{
    return this->_name;
};
void CTranslationDataNode::setName(QString name)
{
    this->_name = name;
};
QString CTranslationDataNode::content() const
{
    return this->_content;
};
void CTranslationDataNode::setContent(QString content)
{
    this->_content = content;
};
QMap<QString,QString> CTranslationDataNode::attributes() const
{
    return this->_attributes;
};
void CTranslationDataNode::addAttribute(QString name, QString value)
{
    this->_attributes[name] = value;
};