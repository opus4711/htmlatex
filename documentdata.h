#ifndef DOCUMENTDATA_H
#define DOCUMENTDATA_H

#include "cnode.h"
#include "settings.h"
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>
#include <iostream>

class DocumentData
{
public:
    enum FileType { JavaDocHTML, HTML, Tex, Unknown };
private:
    QFileInfo _fileInfo;
    CNode* _node;
    QString _text;
    FileType _fileType;
    bool _preprocessed;
    void preprocessingHook();
    void preprocessHTML();
    bool isPreprocessed() const;
public:
    QFileInfo fileInfo() const;
    CNode* node() const;
    QString text();
    FileType fileType() const;
    QFileInfo indexFileInfo() const;
    // Constructor
    DocumentData(QFileInfo fileinfo, CNode* node, FileType filetype);
};

#endif // DOCUMENTDATA_H
