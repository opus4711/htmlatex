#ifndef CCONVERTER_H
#define CCONVERTER_H

#include <QFile>
#include <QString>
#include <QTextStream>
#include "cnode.h"

class CConverter
{
public:
    CConverter(const QString & filepath);
    void convert(CNode* root);
private:
    QFile _file;
//    QTextStream &_stream;
};

#endif // CCONVERTER_H
