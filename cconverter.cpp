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
    int nodecount = (int)tree->getTreeNodeCount();
    int i = 0;
    while (consume())
    {
        if (Settings::DEBUG)
        {
            //std::cerr << "CConverter.convert() - while():\n\ti: " << i << std::endl;
            i++;
            emit updateProgressBar((int)((double)i / (double)nodecount * 100.0));
        }
    }
    std::cerr << "Converter.convert(): cursor.content: " << _cursor->getContent().toStdString() << std::endl;
    std::cerr << "Converter.convert(): cursor.count: " << _cursor->getCount() << std::endl;

    /*
    QString convertedtext(tree->content());
    for (int i = 0; i < _parts.count(); i++)
        convertedtext += _parts.at(i);
        */
    emit updateTextEdit(_cursor->getContent());
    emit updateProgressBar(0);
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
    return (node->getCount() == 0);
};
QMap<QString,QString> CConverter::getAttributes(CNode * node)
{
    return node->getAttributes();
};
QString CConverter::getContent(CNode * node)
{
    return node->getContent();
};
QString getName(CNode * node)
{
    return node->getName();
};
bool CConverter::consume(CNode * node)
{
    CNode *parent = node->getParent();
    if (!parent)
    {
        std::cerr << "ENDE -- Converter.consume(): node.name: " << node->getName().toStdString() << std::endl;
        return false;
    }
    QString parentcontent = _replace(parent);
    //std::cerr << "parentcontent: " << parentcontent.toStdString() << std::endl;
    QString childcontent = _replace();
    for (int i = 0; i < replacementMarks.count(); i++)
    {
        int index = match(parentcontent, replacementMarks.at(i));
        //std::cerr << "index: " << index << std::endl;
        if (index > 0)
        {
            if (replacementMarks.at(i) == "----CONTENT----")
                parentcontent.insert(index, childcontent);
            else if (replacementMarks.at(i) == "----TEXT----")
                parentcontent.insert(index, childcontent);
            // else: eventuell fuer weitere marker
        }
        else
            parentcontent.append(childcontent);
    }
    parent->setContent(parentcontent);
    std::cerr << "node: " << node->getName().toStdString() << " parentcontent: " << parentcontent.toStdString() << std::endl;
    parent->removeChild(node);
    _cursor = getLeaf(parent);
    return true;
};
CNode * CConverter::_getNextSibling()
{
    // Demo-Code
    CNode* result = 0;
    CNode* parent = _cursor->getParent();
    int index = parent->indexOf(_cursor);
    // next sibling's index is (index + 1)
    if (index + 1 < parent->getCount())
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
    return _root->getTreeLevel();
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
    return QBool(_cursor->getContent().isEmpty());
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
QString CConverter::_replace(CNode* node)
{
    QString result("");
    CTranslationData data = _translationMapper->outputMap()[node->getName()];
    QString to = data.to();
    //std::cerr << "to: " << "?"<< to.toStdString() << "?" << std::endl;
    //std::cerr << "content: " << node->content().toStdString() << std::endl;
    QList<CTranslationDataNode> datanodes = data.requires();
    CTranslationDataNode datanode;
    for (int j = 0; j < datanodes.count(); j++)
    {
        datanode = datanodes.at(j);
        //datanode.name()
    }
    for (int i = 0; i < replacementMarks.count(); i++)
        result = to.replace(replacementMarks.at(i), node->getContent());
    //std::cerr << "_replace: result: " << result.toStdString() << std::endl;
    return result;
};
int CConverter::match(QString content, QString pattern)
{
    if (!content.isEmpty())
        return content.indexOf(pattern, 0, Qt::CaseSensitive);
    return -1;
};
