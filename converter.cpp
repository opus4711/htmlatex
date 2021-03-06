#include "converter.h"

Converter::Converter(QObject *parent, TranslationMapper* translationmapper)
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
Node* Converter::_cursor = 0;
void Converter::convert(const QString filepath, Node* tree, DocumentData::FileType filetype)
{
    if (!tree)
    {
        std::cerr << tr("error - CConverter.convert() : tree == 0").toStdString() << std::endl;
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
        }
        i++;
        emit updateProgressBar((int)((double)i / (double)nodecount * 100.0));
    }
    std::cerr << "Converter.convert(): cursor.count: " << _cursor->getCount() << std::endl;
    if (Settings::DEBUG)
        std::cerr << "Content: " << _cursor->getContent().toStdString() << std::endl;

    /*
    QString convertedtext(tree->content());
    for (int i = 0; i < _parts.count(); i++)
        convertedtext += _parts.at(i);
        */

    // ERNSTER CODE !!!
    // save conversion output to file
    if (filetype == DocumentData::Tex)
    {
        QFile file(filepath);
        if (!file.open(QFile::WriteOnly | QFile::Text))
        {
            if (Settings::DEBUG)
            {
                std::cerr << tr("MainWindow._saveAs() - can't write to file: path: ").toStdString()
                        << filepath.toStdString() << std::endl;
            }
        }
        else
        {
            QTextStream stream(&file);
            stream.setCodec("UTF-8");
            stream << _cursor->getContent().toLatin1();
            file.close();
            if (Settings::DEBUG)
                std::cerr << tr("Converter.convert() saved to TEX file").toStdString() << std::endl;
        }
    }
    else if (filetype == DocumentData::PDF)
    {
        Settings settings;
        // invoke external program and write the output to a file
        QString command = settings.getValue("latexpath") + " " + filepath;
        if (Settings::DEBUG)
        {
            std::cerr << tr("Converter.convert() save to PDF:\ncommand: ").toStdString()
                    << command.toAscii().data() << std::endl;
        }
        int errorcode = system(command.toAscii().data());
        if (errorcode == 0)
        {
            if (Settings::DEBUG)
                std::cerr << tr("Converter.convert() saved to PDF file").toStdString() << std::endl;
        }
        else
        {
            if (Settings::DEBUG)
                std::cerr << tr("Converter.convert() en error occurred saving to PDF file: error code ").toStdString()
                << QString::number(errorcode).toStdString() << std::endl;
        }
    }
    else
        std::cerr << tr("Converter.convert(): file not saved - unknown file type").toStdString() << std::endl;
    emit updateTextEdit(_cursor->getContent());
    emit updateProgressBar(0);
};
Node * Converter::getLeaf(Node* node)
{
    Node * result = node;
    while (result->firstChild() != 0)
        result = result->firstChild();
    return result;
};
bool Converter::consume(Node * node)
{
    Node *parent = node->getParent();
    if (!parent)
    {
        if (Settings::DEBUG)
        {
            std::cerr << "Converter.consume(): root node found. node.getName(): "
                    << node->getName().toStdString() << std::endl;
        }
        return false;
    }
    QString parentcontent = parent->getContent();//_replace(parent);
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
    //std::cerr << "node: " << node->getName().toStdString() << " parentcontent: " << parentcontent.toStdString() << std::endl;
    parent->removeChild(node);
    _cursor = getLeaf(parent);
    return true;
};
bool Converter::isLeaf(Node * node)
{
    return (node->getCount() == 0);
};
QMap<QString,QString> Converter::getAttributes(Node * node)
{
    return node->getAttributes();
};
QString Converter::getContent(Node * node)
{
    return node->getContent();
};
QString Converter::getName(Node * node)
{
    return node->getName();
};
Node * Converter::_getNextSibling()
{
    // Demo-Code
    Node* result = 0;
    Node* parent = _cursor->getParent();
    int index = parent->indexOf(_cursor);
    // next sibling's index is (index + 1)
    if (index + 1 < parent->getCount())
        result = parent->childAt(index + 1);
    // _cursor = result; ?
    return result;
};
Node * Converter::_getNextChild()
{
    // Demo-Code
    return _cursor->nextChild();
};
Node * Converter::_getNextNode()
{
   // if cursor has sibling return _getNextSibling
   // elseif cursor has children return _getNextChild
    //else
    return 0;
};
qint64 Converter::_getTreeLevel()
{
    // Demo-Code
    // return the greatest distance of a node to the root node
    return _root->getTreeLevel();
};
QString Converter::_peekParent(qint32 distance)
{
    // if distance < current->layer()
    //   return the parent node <distance> hops up the tree
    // Demo-Code
    return QString("");
};
QBool Converter::_isEmpty()
{
    // Demo-Code
    return QBool(false);
};
QBool Converter::_isEmptyContent()
{
    // Demo-Code
    return QBool(_cursor->getContent().isEmpty());
};
void Converter::removeToken()
{
};
void Converter::_write(QString content, qint32 part)
{
};
qint64 Converter::_tryMatch(QString pattern)
{
    // Demo-Code
    return 0;
};
QString Converter::_replace(Node* node)
{
    QString result("");
    TranslationData data = _translationMapper->outputMap()[node->getName()];
    QString to = data.to();
    //std::cerr << "to: " << "?"<< to.toStdString() << "?" << std::endl;
    //std::cerr << "content: " << node->content().toStdString() << std::endl;
    QList<TranslationDataNode> datanodes = data.requires();
    TranslationDataNode datanode;
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
int Converter::match(QString content, QString pattern)
{
    if (!content.isEmpty())
        return content.indexOf(pattern, 0, Qt::CaseSensitive);
    return -1;
};
