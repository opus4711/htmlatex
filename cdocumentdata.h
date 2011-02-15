#ifndef CDOCUMENTDATA_H
#define CDOCUMENTDATA_H

#include "cnode.h"
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QUrl>
#include <QMessageBox>

class CDocumentData
{
public:
    enum FileType { JavaDocHTML, HTML, Tex, Unknown };
private:
    QUrl _url;
    CNode* _node;
    QString _text;
    QFileInfo _indexFileInfo;
    FileType _fileType;
    bool _preprocessed;
    void preprocessingHook();
    void preprocessHTML();
    bool isPreprocessed() const;
public:
    QUrl url() const;
    CNode* node() const;
    QString text();
    FileType fileType() const;
    QFileInfo indexFileInfo() const;
    // Constructor
    CDocumentData(QUrl url, CNode* node, QFileInfo indexfileinfo, FileType filetype);
};

#endif // CDOCUMENTDATA_H
