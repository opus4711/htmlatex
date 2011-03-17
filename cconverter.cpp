#include "cconverter.h"

CConverter::CConverter(QObject *parent, CTranslationMapper* translationmapper)
    : QObject(parent), _errormessage(""), _noOfParts(0)
{
    _root = 0;
    _translationMapper = translationmapper;
    replacementMarks << "----CONTENT----" << "----TEXT----";

    /* test match()
    QString cont = "0123Justus456789";
    QString pattern = "Justus";
    int i = match(cont, pattern);
    std::cerr << "Converter: i: " << QString::number(i).toStdString() << "\n";
    end test */
};
CNode* CConverter::_cursor = 0;
void CConverter::convert(const QString filepath, CNode* tree)
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
    // consume
    if (!tree)
    {
        std::cerr << "error - CConverter.convert() : tree == 0" << std::endl;
        return;
    }
    _cursor = getLeaf(tree);
    int i = 0;
    while (consume())
    {
        if (DEBUG)
        {
            std::cerr << "CConverter.convert() - while():\n\ti: " << i << std::endl;
            i++;
        }
    }

    /*
    QString convertedtext(tree->content());
    for (int i = 0; i < _parts.count(); i++)
        convertedtext += _parts.at(i);
        */
    QString convertedtext = "jede menge text ü ä ß";
    emit updateTextEdit(convertedtext);
};
CNode * CConverter::getLeaf(CNode* node)
{
    CNode * result = node;
    while (result->firstChild() != 0)
        result = result->firstChild();
    return result;
};
bool CConverter::isLeaf(CNode * node)
{
    return (node->count() == 0);
};
QMap<QString,QString> CConverter::getAttributes(CNode * node)
{
    return node->attributes();
};
QString CConverter::getContent(CNode * node)
{
    return node->content();
};
QString getName(CNode * node)
{
    return node->name();
};
bool CConverter::consume(CNode * node)
{
    CNode *parent = node->parent();
    if (!parent)
    {
        std::cerr << "ENDE -- Converter.consume(): node.name: " << node->name().toStdString() << std::endl;
        return false;
    }
    std::cerr << "Converter.consume(): node.name: " << node->name().toStdString() << std::endl;
    QString parentcontent = parent->content();
    for (int i = 0; i < replacementMarks.count(); i++)
    {

        int index = match(parentcontent, replacementMarks.at(i));
        if (replacementMarks.at(i) == "----CONTENT----")
            parentcontent.insert(index, node->content());
        else if (replacementMarks.at(i) == "----TEXT----")
            parentcontent.insert(index, node->content());;

    }
    parent->removeChild(node);
    _cursor = getLeaf(parent);
    return true;
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
int CConverter::match(QString content, QString pattern)
{
    return content.indexOf(pattern, Qt::CaseSensitive);
};
