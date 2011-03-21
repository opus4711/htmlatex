#ifndef CONVERTER_H
#define CONVERTER_H

#include "cnode.h"
#include "translationmapper.h"
#include "settings.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QDir>
#include <QObject>
#include <iostream>

/** This class converts the QDomDocument-Tree to a textfile
  * by performing the conversions descibed in the 'Output-Definition'-XML file.
  * @author Bjoern Bass
  * @version 0.1
  */
class Converter : public QObject
{
    Q_OBJECT
signals:
    void updateTextEdit(QString text);
    void updateProgressBar(int percentage);
public:
    // TODO take parameter for the output-XML-file
    /**Constructor
      * @param <filepath> where to write the output
      * @param <root> the root-node of the QDomDocument to convert from
      * TODO: @param <parts> the number of parts that are needed for the conversion
      * use enum{start=0, content=1, end=2} (change the XML aliases to numbers)
      */
    Converter(QObject* parent, TranslationMapper* translationmapper);
    /** converts to QString and writes the output file
      * @param <qint32> the number of parts in the outputDocument
      */
    void convert(const QString filepath, CNode* root);
private:
    /*****FIELDS*****/
    // outputfile
    QFile _file;
    // outputfilestream
    QTextStream _stream;
    // the root node
    CNode * _root;
    TranslationMapper* _translationMapper;
    // the active node
    static CNode * _cursor;
    QString _errormessage;
    qint32 _noOfParts;
    QStringList replacementMarks;

    // the compiler assigns values for start, content and end
    enum DocumentPosition { start, content, end };

    // QStringList-Beispiele: _parts << "meinString"; _parts.insert(0, "ersterString");
    // _parts.append("meinString") entspricht dem "<<"-operator
    QStringList _parts;

    /*****METHODS*****/
    // retrieves the first leaf of the tree
    CNode * getLeaf(CNode* node = _cursor);
    // Is the node a leaf?
    bool isLeaf(CNode * node = _cursor);
    // returns the node's attributes
    QMap<QString,QString> getAttributes(CNode * node = _cursor);
    // returnt the node's content
    QString getContent(CNode * node = _cursor);
    // returns the node's name
    QString getName(CNode * node = _cursor);
    // Writes the information of the current (leaf) node into the parent, deletes
    // the active node and sets the cursor to the next leaf.
    bool consume(CNode * node = _cursor);
    int match(QString content, QString pattern);

    // QBool isLeaf(CNode * node = _cursor)
    // consume
    // // QMap<QString, QString> getAttributes()
    // // QString getContent()
    // // QString getName()

    // gets the next sibling
    CNode * _getNextSibling();
    // gets the next child
    CNode * _getNextChild();
    // get the next node in the tree
    // if no siblings left it gets the next child
    CNode * _getNextNode();
    // get the Level ot the current node
    qint64 _getTreeLevel();
    // gets the key of the parent node <distance> levels up the tree
    QString _peekParent(qint32 distance);
    // true if string is empty
    QBool _isEmpty();
    // true if content is empty
    QBool _isEmptyContent();
    // removes token "----CONTENT----"
    void removeToken();
    /* true if started as GUI
     only necessary if the view(Editor part of the GUI)
     or a progressbar has to receive extra information
     */
    //QBool isGUI();

    // delete node and set cursor to the next node
    void _consume();
    // writes <content> at the end of the desired <part>
    void _write(QString content, qint32 part);
    // returns offset if <pattern> is found otherwise returns "-1"
    qint64 _tryMatch(QString pattern);
    // replaces place holder with the content of the current node
    QString _replace(CNode* node = _cursor);
};

#endif // CONVERTER_H
