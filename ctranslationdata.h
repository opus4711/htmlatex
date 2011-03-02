#ifndef CTRANSLATIONDATA_H
#define CTRANSLATIONDATA_H

#include <QString>
#include <QMap>

class CTranslationData
{
private:
    QString _from;
    QString _to;
    QMap<QString,QString> _requires;
public:
    QString from() const;
    void setFrom(QString from);
    QString to() const;
    void setTo(QString to);
    QMap<QString,QString> requires() const;
    void setRequires(QMap<QString,QString> requires);
    // Constructor
    CTranslationData();
};

#endif // CTRANSLATIONDATA_H
