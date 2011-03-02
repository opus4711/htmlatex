#ifndef CTRANSLATIONDATANODE_H
#define CTRANSLATIONDATANODE_H

#include <QString>
#include <QMap>

class CTranslationDataNode
{
private:
    QString _name;
    QString _content;
    QMap<QString,QString> _attributes;
public:
    QString name() const;
    void setName(QString name);
    QString content() const;
    void setContent(QString content);
    QMap<QString,QString> attributes() const;
    void setAttributes(QMap<QString,QString> attributes);
    // Constructor
    CTranslationDataNode(QString name);
};

#endif // CTRANSLATIONDATANODE_H
