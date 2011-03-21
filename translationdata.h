#ifndef TRANSLATIONDATA_H
#define TRANSLATIONDATA_H

#include "translationdatanode.h"
#include <QString>
#include <QMap>

class TranslationData
{
private:
    QString _key;
    QString _from;
    QString _to;
    QList<TranslationDataNode> _requires;
public:
    QString key() const;
    void setKey(QString key);
    QString from() const;
    void setFrom(QString from);
    QString to() const;
    void setTo(QString to);
    QList<TranslationDataNode> requires() const;
    void addRequiresNode(TranslationDataNode requiresnode);
    /** Constructor */
    TranslationData();
};

#endif // TRANSLATIONDATA_H
