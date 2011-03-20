#ifndef DOCUMENTREADERDATA_H
#define DOCUMENTREADERDATA_H

#include <QString>

class DocumentReaderData
{
private:
    QString _tagName;
    QString _urlContainingAttributeName;
public:
    QString getTagName() const;
    QString getUrlContainingAttributeName() const;
    DocumentReaderData(QString tagname, QString urlcontainingattributename);
};

#endif // DOCUMENTREADERDATA_H
