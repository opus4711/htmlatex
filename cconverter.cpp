#include "cconverter.h"

CConverter::CConverter(QObject *parent, CTranslationMapper* translationmapper)
    : QObject(parent), _errormessage(""), _noOfParts(0)
{
    _root = 0;
    _translationMapper = translationmapper;
    _cursor = 0;
};
void CConverter::convert(const QString filepath, CNode* root)
{
    /*
    _file.setFileName(filepath);
    _root = root;
    if (!_file.open(QFile::WriteOnly))
    {
        std::cerr << "Cannot open file for writing: "
                << qPrintable(_file.errorString()) << std::endl;
        return;
    }
    // TODO : ist _stream instanziiert?
    _stream.setDevice(&_file);
    _stream.setCodec("UTF-8");
    // converting...
    */
    CNode * CConverter::getLeaf()
     {
        CNode * result = _cursor;
         while (result->firstChild()!=0)
             result = result->firstChild();
     }

    // QBool isLeaf(CNode * node = _cursor)
    // consume
    // // QMap<QString, QString> getAttributes()
    // // QString getContent()
    // // QString getName()
    if()
    QString convertedtext("");
    for (int i = 0; i < _parts.count(); i++)
        convertedtext += _parts.at(i);
    convertedtext = "jede menge text ü ä ß";
    emit updateTextEdit(convertedtext);
};
CNode * CConverter::_getNextSibling()
{
    // Demo-Code
    CNode* result = 0;
    CNode* parent = _cursor->parent();
    int index = parent->indexOf(_cursor);
    // next sibling's index is (index + 1)
    if (index + 1 < parent->count())
        result = parent->childAt(index + 1);
    // _cursor = result; ?
    return result;
};
CNode * CConverter::_getNextChild()
{
    // Demo-Code
    return _cursor->nextChild();
};
CNode * CConverter::_getNextNode()
{
    if(_cursor->parent() == 0)
        _cursor
   // if cursor has sibling return _getNextSibling
   // elseif cursor has children return _getNextChild
    //else
    return 0;
};
qint64 CConverter::_getTreeLevel()
{
    // Demo-Code
    // return the greatest distance of a node to the root node
    return _root->treeLevel();
};
QString CConverter::_peekParent(qint32 distance)
{
    // if distance < current->layer()
    //   return the parent node <distance> hops up the tree
    // Demo-Code
    return QString("");
};
QBool CConverter::_isEmpty()
{
    // Demo-Code
    return QBool(false);
};
QBool CConverter::_isEmptyContent()
{
    // Demo-Code
    return QBool(_cursor->content().isEmpty());
};
void CConverter::removeToken()
{
};
void CConverter::_consume()
{
};
void CConverter::_write(QString content, qint32 part)
{
};
qint64 CConverter::_tryMatch(QString pattern)
{
    // Demo-Code
    return 0;
};
void CConverter::_replace(QString from, QString to)
{
};
