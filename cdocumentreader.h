#ifndef CDOCUMENTREADER_H
#define CDOCUMENTREADER_H

#include "cnode.h"
#include <QObject>
#include <QString>
#include <QFile>
#include <QDir>
#include <QDomDocument>
#include <QMessageBox>
#include <QDomNamedNodeMap>
#include <QTextStream>
#include <QMapIterator>
#include <QStack>

class CDocumentReader
{
    // Aggregate
private:
    class DocumentData
    {
    public:
        QString path;
        CNode* node;
        DocumentData() {};
        DocumentData(QString path, CNode* node)
        {
            this->path = path;
            this->node = node;
        };
    };
private:
    enum FileType { JavaDocHTML, HTML, Tex, Unknown };
    QFileInfo _sourceFileInfo;
    FileType fileType;
    QStack<DocumentData> documentStack;
    void readElement(QDomElement element, CNode* node);
    CNode* read(QString path);
    void preprocessingHook(QString path);
    void preprocessJavaDocHTML(QString path);
    QString nodeToString(CNode* node, int ebene);
public:
    CNode* read(QString sourcefilepath, QString filefilter);
    QString toString(CNode* root);
    // constructor
    CDocumentReader();
};

#endif // CDOCUMENTREADER_H
