#ifndef TRANSLATIONDATANODE_H
#define TRANSLATIONDATANODE_H

#include <QString>
#include <QMap>

class TranslationDataNode
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
    void addAttribute(QString name, QString value);
    /** Constructor */
    TranslationDataNode();
};

#endif // TRANSLATIONDATANODE_H
