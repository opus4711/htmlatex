#ifndef DOCUMENTREADER_H
#define DOCUMENTREADER_H

#include "node.h"
#include "documentdata.h"
#include "translationmapper.h"
#include "settings.h"
#include <QObject>
#include <QString>
#include <QDomDocument>
#include <QDomNamedNodeMap>
#include <QMapIterator>
#include <QStack>
#include <QDir>

#include <iostream>

class DocumentReader : public QObject
{
    Q_OBJECT
public:
    /** This is the only constructor.
        @param <translationmapper> is used to obtain a DocumentReaderData object
        which mainly describes how a reference to a another document is defined in
        the input document.
        @author Bjoern
      */
    DocumentReader(TranslationMapper* translationmapper);
    /** This method creates a Node tree structure which corresponds to the whole
        input document including its sub documents if desired
        (_includeSubDocuments is set). The nodes of each document are processed
        recursively by the _readElement() method. Whereas the documents
        (sub documents) are processed in an iteration loop by means of the
        _documentStack.
        @param <indexfilepath> contains the absolute file path to the index document.
        @param <filetype> indicates of which type the input document is.
        @author Bjoern
      */
    Node* read(QString indexfilepath, DocumentData::FileType filetype);
private:
    /** The _translationMapper provides two data objects: firstly a
        DocumentReaderData object which is used by the DocumentReader and
        secondly a key-value-pair structure which is used by the Converter.
        @author Bjoern
      */
    TranslationMapper* _translationMapper;
    /** This attribute provides detailed information about the input index file
        such as absolute and relative path etc..
        @author Bjoern
      */
    QFileInfo _indexFileInfo;
    /** This attribute indicates of which type the input document is.
        @author Bjoern
      */
    DocumentData::FileType _fileType;
    /** This stack is populated with DocumentData objects when processing the
        input document. The usage of a stack allows to process the input document
        and its sub documents in an iteration loop instead of a recursion because
        a recursion may raise a stack overflow issue.
        @author Bjoern
      */
    QStack<DocumentData*> _documentStack;
    /** This attribute indicates whether sub documents are included by the
        input document processing or not.
        @author Bjoern
      */
    bool _includeSubDocuments;
    /** This method processes a single document recursively. It adds for each node
        of the input document a corresponding Node object to the application's
        internal tree structure. If a reference to a sub document is found a new
        DocumentData object is generated and pushed on the _documentStack.
        @param <element> is the current parent QDomElement object. Notice that the
        _readElement() method performs a recursion to process a single document.
        @param <node> is a pointer pointing to the very Node object of the
        application's internal tree structure to which currently generated Node
        objects will be added. Notice that the _readElement() method performs a
        recursion to process a single document.
        @author Bjoern
      */
    void _readElement(QDomElement element, Node* node);
};

#endif // DOCUMENTREADER_H
