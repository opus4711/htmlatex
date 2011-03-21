#include "documentreader.h"

/** This class creates a tree representation of a given document.
  @author Bjoern
  */
DocumentReader::DocumentReader(TranslationMapper* translationmapper)
{
    _fileType = DocumentData::Unknown;
    _translationMapper = translationmapper;
    Settings settings;
    _includeSubDocuments = (bool)settings.getValue("includesubdocuments").toInt();
};
/** This method
  * @param filetype contains the file filter string selected previously.
  * @author Bjoern
  */
Node* DocumentReader::read(QString indexfilepath,
                             DocumentData::FileType filetype)
{
    if (_translationMapper == 0)
    {
        if (Settings::DEBUG)
            std::cerr << "DocumentReader.read() : _translationMapper is 0" << std::endl;
        return 0;
    }
    Settings settings;
    _includeSubDocuments = (bool)settings.getValue("includesubdocuments").toInt();
    _fileType = filetype;
    _indexFileInfo = QFileInfo(indexfilepath);
    // start reading the whole document tree
    Node* root = new Node(0, "html", 0);
    // add the index document to the stack of documents
    _documentStack.push(new DocumentData(_indexFileInfo, root, _fileType));
    // begin processing the documents stored on the document stack
    while(!_documentStack.isEmpty())
    {
        DocumentData* documentdata = _documentStack.pop();
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
void DocumentReader::readElement(QDomElement element, Node* node)
{
    for (int i = 0; i < element.childNodes().count(); i++)
    {
        // The QDomDocument class creates a node named "#text" which contains
        // the node value (content).
        if (element.childNodes().at(i).nodeName().toLower() == "#text")
            node->setContent(element.childNodes().at(i).nodeValue());
        else
        {
            Node* new_node = new Node(node,
                                        element.childNodes().at(i).nodeName().toLower(),
                                        node->getLayer() + 1);
            node->addChild(new_node);
            QDomNamedNodeMap attributes = element.childNodes().at(i).attributes();
            DocumentReaderData documentreference = _translationMapper->getDocumentReference();
            if (element.childNodes().at(i).nodeName().toLower() == documentreference.getTagName())
            {
                if (Settings::DEBUG)
                {
                    std::cerr << tr("#\tReadElement - '").toStdString()
                            << documentreference.getTagName().toStdString()
                            << tr("': \n#\t\tindexFileInfo.absPath: ").toStdString()
                            << _indexFileInfo.absolutePath().toStdString()
                            << std::endl << tr("#\t\thref: ").toStdString()
                            << new_node->getAttributes()["href"].toStdString() << std::endl;
                }
                QString urlattribute = documentreference.getUrlContainingAttributeName();
                new_node->addAttribute(urlattribute, attributes.namedItem(urlattribute).nodeValue());
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
                if (_includeSubDocuments)
                    _documentStack.push(new DocumentData(myfileinfo, new_node, _fileType));
                if(Settings::DEBUG)
                {
                    std::cerr << tr("# CDocumentReader::readElement()").toStdString()
                           << std::endl << tr("#\tat \"if (element.childNodes()").toStdString()
                           << tr(".at(i).nodeName().toLower() == \"a\")\" returned true").toStdString()
                           << std::endl << tr("#\tfound subdocument href=").toStdString()
                           << new_node->getAttributes()["href"].toStdString() << std::endl;
                }
            }
            else
            {
                QDomNode attribute;
                for (int i = 0; i < attributes.count(); i++)
                {
                    attribute = attributes.item(i);
                    new_node->addAttribute(attribute.nodeName(), attribute.nodeValue());
                }
            }
            QDomElement new_element = element.childNodes().at(i).toElement();
            readElement(new_element, new_node);
        }
    }
};
