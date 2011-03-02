#ifndef CTRANSLATIONDATA_H
#define CTRANSLATIONDATA_H

#include "ctranslationdatanode.h"
#include <QString>
#include <QMap>

class CTranslationData
{
private:
    QString _from;
    QString _to;
    QList<CTranslationDataNode> _requires;
public:
    QString from() const;
    void setFrom(QString from);
    QString to() const;
    void setTo(QString to);
    QList<CTranslationDataNode> requires() const;
    void addRequiresNode(CTranslationDataNode requiresnode);
    // Constructor
    CTranslationData();
};

#endif // CTRANSLATIONDATA_H
