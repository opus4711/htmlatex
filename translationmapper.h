#ifndef TRANSLATIONMAPPER_H
#define TRANSLATIONMAPPER_H

#include "translationdata.h"
#include "settings.h"
#include "documentreaderdata.h"
#include <QObject>
#include <QFile>
#include <QDomDocument>
#include <QString>
#include <QMap>
#include <iostream>

/** This class processes the input and output definition files to procure data
    structures which meet the needs of the DocumentReader and Converter classes.
    Hence it creates a DocumentReaderData object stored in the _documentReference
    attribute which describes how a reference to a subdocument of an input
    document is defined. In addition it creates a key-value-pair data structure
    (an associative array) which holds information about how the relevant nodes
    of the input document are to be translated.
    @author Bjoern
  */
class TranslationMapper : public QObject
{
    Q_OBJECT
public:
    /** This is the only constructor.
        @author Bjoern
      */
    TranslationMapper(QObject *parent = 0);
private:
    /** This attribute contains a DocumentReaderData object which describes how a
        reference to a subdocument of an input document is defined.
        @author Bjoern
      */
    DocumentReaderData _documentReference;
    /** This attribute holds a key-value-pair data structure (an associative array).
        The items of this array can be accessed via a key of the type QString
        (i.e. _outputMap["head"]). The node names of the input document serve as
        keys for this array. The received value is a TranslationData object
        providing information for the Converter which performs textual replacements.
        @author Bjoern
      */
    QMap<QString,TranslationData> _outputMap;
public:
    /** This method processes the input definition file to store a DocumentReaderData
        object in the attribute _documentReference.
        @param <inputfilepath> is the file path to the input definition file.
        @author Bjoern
      */
    void createDocumentReaderData(QString inputfilepath);
    /** This method processes the output definition file to populate the attribute
        _outputMap with a TranslationData object for each different node of the
        input document.
        @param <outputfilepath> is the file path to the output definition file.
        @author Bjoern
      */
    void createOutputElementMap(QString outputfilepath);
    /** This method returns the object held by the attribute _documentReference.
        @author Bjoern
      */
    DocumentReaderData getDocumentReference() const;
    /** This method returns the object held by the attribute _outputMap.
        @author Bjoern
      */
    QMap<QString,TranslationData> outputMap() const;
};

#endif // TRANSLATIONMAPPER_H
