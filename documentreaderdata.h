#ifndef DOCUMENTREADERDATA_H
#define DOCUMENTREADERDATA_H

#include <QString>

/** This class describes how a reference to a subdocument of an input document
    is defined. Example: In (X)HTML a subdocumet is referenced using the <a> tag
    with its attribute "href". The TranslationMapper creates an instance of
    the DocumentReaderData class using the document definition file. Finally the
    DocumentReader obtains the DocumentReaderData object from the
    TranslationMapper.
    @author Bjoern
  */
class DocumentReaderData
{
public:
    /** This is an empty constructor which initializes the attributes _tagName and
        _urlContainingAttributeName with empty strings.
        @author Bjoern
      */
    DocumentReaderData();
    /** This is the copy constructor.
        @author Bjoern
      */
    DocumentReaderData(const DocumentReaderData& documentreaderdata);
    /** This constructor initializes the attributes _tagName and
        _urlContainingAttributeName with the given string values.
        @param <tagname> contains a XML tag name.
        @param <urlcontainingattributename> contains a XML attribute name.
        @author Bjoern
      */
    DocumentReaderData(QString tagname, QString urlcontainingattributename);
private:
    /** This attribute contains the name of that XML tag which decribes a reference
        to a subdocument in the XML represented input document.
        @author Bjoern
      */
    QString _tagName;
    /** This attribute contains the name of that XML attribute belonging to the
        XML tag specified by _tagName and which holds the file path to a
        subdocument in the XML represented input document.
        @author Bjoern
      */
    QString _urlContainingAttributeName;
public:
    /** This method returns the name of that XML tag which decribes a reference
        to a subdocument in the XML represented input document.
        @author Bjoern
      */
    QString getTagName() const;
    /** This method returns the name of that XML attribute belonging to the
        XML tag specified by _tagName and which holds the file path to a
        subdocument in the XML represented input document.
        @author Bjoern
      */
    QString getUrlContainingAttributeName() const;
};

#endif // DOCUMENTREADERDATA_H
