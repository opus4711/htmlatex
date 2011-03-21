#include "translationdatanode.h"

TranslationDataNode::TranslationDataNode() : _name(""),
    _content("")
{
    this->_attributes = QMap<QString,QString>();
};
QString TranslationDataNode::name() const
{
    return this->_name;
};
void TranslationDataNode::setName(QString name)
{
    this->_name = name;
};
QString TranslationDataNode::content() const
{
    return this->_content;
};
void TranslationDataNode::setContent(QString content)
{
    this->_content = content;
};
QMap<QString,QString> TranslationDataNode::attributes() const
{
    return this->_attributes;
};
void TranslationDataNode::addAttribute(QString name, QString value)
{
    this->_attributes[name] = value;
};
