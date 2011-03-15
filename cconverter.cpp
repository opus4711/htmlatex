#include "cconverter.h"

CConverter::CConverter(const QString filepath, CNode* root,
                       CTranslationMapper* translationmapper)
    : _file(filepath), _errormessage(""), _noOfParts(0)
{
    _root = root;
    _translationMapper = translationmapper;
    _cursor = 0;
    if (!_file.open(QFile::WriteOnly))
    {
        std::cerr << "Cannot open file for writing: "
                << qPrintable(_file.errorString()) << std::endl;
        return;
    }

    // nothing sinnvoll here
    _stream.setDevice(&_file);
    _stream.setCodec("UTF-8");
    _stream << "Ausgabe von Testwerten...leider nichts wichtiges dabei..." << "\n"
            << "root.content()\t" << root->content() << "\n"
            << "root.name()\t" << root->name() << "\n"
            << "root.layer()\t" << root->layer() << "\n"
            << "root.count()\t" << root->count() << "\n";
    // die Daten werden erst in die Datei geschrieben nach dem Schließen
    _file.close();
    // Demo-Code
    // create demo nodes
    CNode* table = new CNode(0, "table", 0);
    CNode* requireschild = new CNode(table, "requires", 1);
    CNode* locationchild = new CNode(requireschild, "location", 2);
    locationchild->addAttribute("position", "start");
    requireschild->addChild(locationchild);
    table->addChild(requireschild);
    // demo nodes created
    CTranslationData translationdata = _translationMapper->outputMap()[table->name()];
    QString from(translationdata.from());
    QString to(translationdata.to());
    std::cerr << std::endl << "from: " << from.toStdString() << std::endl
            << "to: " << to.toStdString() << std::endl;
    for (int i = 0; i < translationdata.requires().count(); i++)
    {
        CTranslationDataNode ctranslationdatanode = translationdata.requires().at(i);
        if (ctranslationdatanode.name() == "location")
        {
            QString position(ctranslationdatanode.attributes()["position"]);
            std::cerr << std::endl << "<location position=\"?\"> contains: "
                    << position.toStdString() << std::endl;
        }
    }
};
void CConverter::convert(qint32 outputParts)
{
    QString convertedtext("");
    for (int i = 0; i < _parts.count(); i++)
        convertedtext += _parts.at(i);
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
