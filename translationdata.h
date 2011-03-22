#ifndef TRANSLATIONDATA_H
#define TRANSLATIONDATA_H

#include "translationdatanode.h"
#include <QString>
#include <QMap>

/** The Converter performs the conversion on the application's internal tree
    structure. In order to be able to translate each node of the internal tree the
    Converter retrieves a TranslationData object via the TranslationMapper. The
    Converter passes the name of that node which is currently to be translated as
    key to the TranslationMapper which returns the respective TranslationData
    object from its _outputMap (an associative array). This TranslationData object
    contains information which allow textual replacements on that node's content
    which is currently to be translated.
  */
class TranslationData
{
public:
    /** This is the only constructor which initializes the attributes.
        @author Bjoern
      */
    TranslationData();
private:
    /** The _key is used by the TranslationMapper to store and access the
        TranslationData object in its _outputMap (an associative array).
        @author Bjoern
      */
    QString _key;
    /** This attribute is unused yet.
        @author Bjoern
      */
    QString _from;
    /** This attribute is the target string and can contain a place holder for
        further additions in the translation process.
        @author Bjoern
      */
    QString _to;
    /** This array of TranslationDataNode objects allows inclusion of special
        target document formatting instructions(i.e. "requires" in TEX).
      */
    QList<TranslationDataNode> _requires;
public:
    /** This method returns the value of the _key attribute.
        @author Bjoern
      */
    QString key() const;
    /** This method sets the value of the _key attribute.
        @author Bjoern
      */
    void setKey(QString key);
    /** This method returns the value of the _from attribute.
        @author Bjoern
      */
    QString from() const;
    /** This method sets the value of the _from attribute.
        @author Bjoern
      */
    void setFrom(QString from);
    /** This method returns the value of the _to attribute.
        @author Bjoern
      */
    QString to() const;
    /** This method sets the value of the _to attribute.
        @author Bjoern
      */
    void setTo(QString to);
    /** This method returns the array of TranslationDataNode objects stored in the
        _requires attributes.
        @author Bjoern
      */
    QList<TranslationDataNode> requires() const;
    /** This method adds a TranslationDataNode object to the array of
        TranslationDataNode objects stored in the _requires attribute.
        @author Bjoern
      */
    void addRequiresNode(TranslationDataNode requiresnode);
};

#endif // TRANSLATIONDATA_H
