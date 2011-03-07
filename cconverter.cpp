#include "cconverter.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include "cnode.h"

CConverter::CConverter(const QString & filepath)
{
    this->_file(filepath);
//    this->_stream(&_file);
//    _stream.setCodec("UTF-8");
}

void CConverter::convert(CNode* root)
{
    //    root->file
    //    root->node->
//    _stream << "schreiben...";
}
