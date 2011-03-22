#ifndef DOCUMENTDATA_H
#define DOCUMENTDATA_H

#include "node.h"
#include "settings.h"
#include <QObject>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>
#include <iostream>

/** This class provides a well-formed XML representation of a single input document.
    @author Bjoern
  */
class DocumentData : public QObject
{
    Q_OBJECT
public:
    enum FileType { JavaDocHTML, HTML, Tex, PDF, Unknown };
    /** This is the only constructor. It returns an object created from a QFileInfo
        object which holds detailed information about a single input document such
        as its absolute file path. The text() method returns a well-formed XML
        representation of the input document taking the file type into account.
        The application's internal tree structure is supposed to represent a whole
        input document including its subdocuments. So a Node object is used by
        the DocumentReader to determine where to add the subdocument represented
        by this class (DocumentData).
        @param <fileinfo> holds detailed information about the input document.
        @param <node> is the corresponding parent node in the application's
        internal tree structure.
        @param <filetype> indicates the file typ of the input document (i.e.
        JavaDoc HTML).
        @author Bjoern
      */
    DocumentData(QFileInfo fileinfo, Node* node, FileType filetype);
private:
    /** This attribute contains a well-formed XML representation of the underlying
        input document.
        @author Bjoern
      */
    QString _text;
    /** This attribute holds detailed information about the input document.
        @author Bjoern
      */
    QFileInfo _fileInfo;
    /** This attribute contains the file type of the input document (i.e. JavaDoc
        HTML).
        @author Bjoern
      */
    FileType _fileType;
    /** The application's internal tree structure is supposed to represent a whole
        input document including its subdocuments. So the Node object is used by
        the DocumentReader to determine where to add the subdocument represented
        by this class (DocumentData).
        @author Bjoern
      */
    Node* _node;
    /** This attribute indicates whether or not the input document has already
        been preprocessed by the appropriate preprocessing method.
        @author Bjoern
      */
    bool _preprocessed;
    /** This hook-method calls all preprocessing methods.
        @author Bjoern
      */
    void _preprocessingHook();
    /** This method changes the specified HTML-file in order to gain well-formed
        XML (XHTML).
        @author Bjoern
      */
    void _preprocessHTML();
public:
    /** This method returns a well-formed XML representation of the underlying
        input document.
        @author Bjoern
      */
    QString text();
    /** This method returns a QFileInfo object which holds detailed information
        about the input document.
        @author Bjoern
      */
    QFileInfo fileInfo() const;
    /** The application's internal tree structure is supposed to represent a whole
        input document including its subdocuments. So the Node object is used by
        the DocumentReader to determine where to add the subdocument represented
        by this class (DocumentData).
        @author Bjoern
      */
    Node* node() const;
};

#endif // DOCUMENTDATA_H
