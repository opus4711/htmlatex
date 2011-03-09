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
};
void CConverter::convert(qint32 outputParts)
{

};
CNode * CConverter::_getNextSibling()
{
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
    return _cursor->nextChild();
};
CNode * CConverter::_getNextNode()
{
    return 0;
};
qint64 CConverter::_getTreeLevel()
{
    // return the greatest distance of a node to the root node
    return _root->treeLevel();
};
QString CConverter::_peekParent(qint32 distance)
{
    return QString("");
};
QBool CConverter::_isEmpty()
{
    return QBool(false);
};
QBool CConverter::_isEmptyContent()
{
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
    return 0;
};
void CConverter::_replace (QString from, QString to)
{
};
