#include "documentreaderdata.h"

DocumentReaderData::DocumentReaderData(QString tagname, QString urlcontainingattributename)
{
    this->_tagName = tagname;
    this->_urlContainingAttributeName = urlcontainingattributename;
};
QString DocumentReaderData::getTagName() const
{
    return this->_tagName;
};
QString DocumentReaderData::getUrlContainingAttributeName() const
{
    return this->_urlContainingAttributeName;
};
