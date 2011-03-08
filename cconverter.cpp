#include "cconverter.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include "cnode.h"
#include <QDir>
#include <iostream>

CConverter::CConverter(const QString &filepath, CNode &root)
{
    QFile file(filepath);

    if (!file.open(QFile::WriteOnly))
    {
        std::cerr << "Cannot open file for writing: "
                << qPrintable(file.errorString()) << std::endl;
     return;
    }

    // nothing sinnvoll here
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    stream << "Ausgabe von Testwerten...leider nichts wichtiges dabei..."<< "\n"
            << "root.content()\t" << root.content() << "\n"
            << "root.name()\t" << root.name() << "\n"
            << "root.layer()\t" << root.layer() << "\n"
            << "root.count()\t" << root.count() << "\n";
}

void CConverter::convert(qint32 outputParts)
{

}
