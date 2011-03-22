#ifndef TRANSLATIONDATANODE_H
#define TRANSLATIONDATANODE_H

#include <QString>
#include <QMap>

/** The TranslationMapper processes the input and output definition files and
    creates TranslationData objects which hold an array of TranslationDataNode
    objects. This class describes a XML node of the output definition file which
    allows inclusion of special target document formatting instructions (i.e.
    "requires" in TEX).
    @author Bjoern
  */
class TranslationDataNode
{
public:
    /** This is the only constructor which initializes the attributes.
        @author Bjoern
      */
    TranslationDataNode();
private:
    /** This is the name of the XML node describing a special target document
        formatting instruction (i.e. "requires" in TEX).
        @author Bjoern
      */
    QString _name;
    /** This is the content of the XML node describing a special target document
        formatting instruction (i.e. "requires" in TEX).
        @author Bjoern
      */
    QString _content;
    /** This is an associative array holding the attributes of the XML node
        describing a special target document formatting instruction (i.e.
        "requires" in TEX).
        @author Bjoern
      */
    QMap<QString,QString> _attributes;
public:
    /** This method returns the name of the XML node describing a special target
        document formatting instruction (i.e. "requires" in TEX).
        @author Bjoern
      */
    QString name() const;
    /** This method sets the name of the XML node describing a special target
        document formatting instruction (i.e. "requires" in TEX).
        @author Bjoern
      */
    void setName(QString name);
    /** This method returns the content of the XML node describing a special target
        document formatting instruction (i.e. "requires" in TEX).
        @author Bjoern
      */
    QString content() const;
    /** This method sets the content of the XML node describing a special target
        document formatting instruction (i.e. "requires" in TEX).
        @author Bjoern
      */
    void setContent(QString content);
    /** This method returns an associative array holding the attributes of the XML
        node describing a special target document formatting instruction (i.e.
        "requires" in TEX).
        @author Bjoern
      */
    QMap<QString,QString> attributes() const;
    /** This method adds an attribute to the associative array holding the
        attributes of the XML node describing a special target document formatting
        instruction (i.e. "requires" in TEX).
        @author Bjoern
      */
    void addAttribute(QString name, QString value);
};

#endif // TRANSLATIONDATANODE_H
