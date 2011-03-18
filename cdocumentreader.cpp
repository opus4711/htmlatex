#include "cdocumentreader.h"
#include "constants.h"

/** This class creates a tree representation of a given document.
  @author Bjoern Kaiser
  */
CDocumentReader::CDocumentReader()
{
    _fileType = CDocumentData::Unknown;
};
/** This method
  * @param filetype contains the file filter string selected previously.
  * @author Bjoern Kaiser
  */
CNode* CDocumentReader::read(QString indexfilepath,
                             CDocumentData::FileType filetype)
{
    _fileType = filetype;
    _indexFileInfo = QFileInfo(indexfilepath);
    // start reading the whole document tree
    CNode* root = new CNode(0, "html", 0);
    // add the index document to the stack of documents
    _documentStack.push(new CDocumentData(_indexFileInfo, root, _fileType));
    // begin processing the documents stored on the document stack
    while(!_documentStack.isEmpty())
    {
        CDocumentData* documentdata = _documentStack.pop();
        QDomDocument doc;
        QString errorStr = "";
        int errorLine = -1;
        int errorColumn = -1;
        if (doc.setContent(documentdata->text().toLatin1(),
                           false,
                           &errorStr,
                           &errorLine,
                           &errorColumn))
        {
            if (doc.documentElement().tagName().toLower() == "html")
                readElement(doc.documentElement(), documentdata->node());
            else
            {
                std::cerr << "Error in CDocumentReader::read()"
                        << std::endl << "\tat \"if (doc.setContent())\" returned false;"
                        << std::endl << "\tFile name: "
                        << documentdata->fileInfo().filePath().toStdString()
                        << std::endl << "\tError message: <html>-tag not found"
                        << std::endl;
            }
        }
        else
        {
            std::cerr << "Error in CDocumentReader::read()"
                    << std::endl << "\tat doc.setContent() returned false;"
                    << std::endl << "\tFile name: "
                    << documentdata->fileInfo().filePath().toStdString()
                    << std::endl << "\tError message: "
                    << std::endl << errorStr.toStdString() << " line="
                    << std::endl << QString::number(errorLine).toStdString()
                    << std::endl << "\tColumn=" << QString::number(errorColumn).toStdString()
                    << std::endl;
        }
        delete documentdata;
    }
    return root;
};
void CDocumentReader::readElement(QDomElement element, CNode* node)
{
    for (int i = 0; i < element.childNodes().count(); i++)
    {
        if (element.childNodes().at(i).nodeName().toLower() == "#text")
            node->setContent(element.childNodes().at(i).nodeValue());
        else
        {
            CNode* new_node = new CNode(node,
                                        element.childNodes().at(i).nodeName().toLower(),
                                        node->getLayer() + 1);
            node->addChild(new_node);
            QDomNamedNodeMap attributes = element.childNodes().at(i).attributes();
            if (element.childNodes().at(i).nodeName().toLower() == "font")
                new_node->addAttribute("size", attributes.namedItem("size").nodeValue());
            else if (element.childNodes().at(i).nodeName().toLower() == "td")
            {
                new_node->addAttribute("align", attributes.namedItem("align").nodeValue());
                new_node->addAttribute("valign", attributes.namedItem("valign").nodeValue());
                new_node->addAttribute("width", attributes.namedItem("width").nodeValue());
            }
            else if (element.childNodes().at(i).nodeName().toLower() == "tr")
                new_node->addAttribute("bgcolor", attributes.namedItem("bgcolor").nodeValue());
            else if (element.childNodes().at(i).nodeName().toLower() == "th")
            {
                new_node->addAttribute("align", attributes.namedItem("align").nodeValue());
                new_node->addAttribute("colspan", attributes.namedItem("colspan").nodeValue());
            }
            else if (element.childNodes().at(i).nodeName().toLower() == "a")
            {
                if (DEBUG)
                {
                    std::cerr << "#\tReadElement - 'a': \n#\t\tindexFileInfo.absPath: "
                            << _indexFileInfo.absolutePath().toStdString()
                            << std::endl << "#\t\thref: "
                            << new_node->getAttributes()["href"].toStdString() << std::endl;
                }
                new_node->addAttribute("href", attributes.namedItem("href").nodeValue());
                // compose absolute file path
                QFileInfo myfileinfo;
                if (QFileInfo(_indexFileInfo.absolutePath() + new_node->getAttributes()["href"]).exists())
                    // unix
                    myfileinfo = QFileInfo(_indexFileInfo.absolutePath()
                                           + new_node->getAttributes()["href"]);
                else
                    // windows
                    myfileinfo = QFileInfo(_indexFileInfo.absolutePath()
                                           + QDir::separator() + new_node->getAttributes()["href"]);
                _documentStack.push(new CDocumentData(myfileinfo, new_node, _fileType));
               if(DEBUG)
                {
                   std::cerr << "# CDocumentReader::readElement()"
                           << std::endl << "#\tat \"if (element.childNodes()"
                           << ".at(i).nodeName().toLower() == \"a\")\" returned true"
                           << std::endl << "#\tfound subdocument href="
                           << new_node->getAttributes()["href"].toStdString() << std::endl;
                }
            }
            QDomElement new_element = element.childNodes().at(i).toElement();
            readElement(new_element, new_node);
        }
    }
};
void CDocumentReader::setTranslationMapper(CTranslationMapper* translationmapper)
{
    this->_translationMapper = translationmapper;
};
