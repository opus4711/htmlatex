#include "cdocumentreader.h"

/** This class creates a tree representation of a given document.
  @author Björn Kaiser
  */
CDocumentReader::CDocumentReader()
{
    _fileType = CDocumentData::Unknown;
};
/** This method
  * @param filetype contains the file filter string selected previously.
  * @author Björn Kaiser
  */
CNode* CDocumentReader::read(QString indexfilepath, CDocumentData::FileType filetype)
{
    _fileType = filetype;
    // store information about the index document
    _indexFileInfo = QFileInfo(indexfilepath);
    // start reading the whole document tree
    CNode* root = new CNode(0, "html", 0);
    // add the index document to the stack of documents
    _documentStack.push(new CDocumentData(QUrl(_indexFileInfo.absoluteFilePath()), root, _indexFileInfo, _fileType));
    // begin processing the documents stored on the document stack
    int temp = 0;
    while(!_documentStack.isEmpty())
    {
        CDocumentData* documentdata = _documentStack.pop();
        QDomDocument doc;
        QString errorStr = "";
        int errorLine = -1;
        int errorColumn = -1;
        // ---Test-Ausgabe in eine UTF8-Datei
        // ---erzeugt durchnummerierte dateien im ausführungs-verzeichnis namens "0_testausgabe_utf8.txt"
        /*
        QFile testfile(QString::number(temp++) + "_testausgabe_utf8.txt");
        if (testfile.open(QFile::WriteOnly | QFile::Text))
            testfile.write(documentdata->text().toUtf8());
        testfile.close();
        */
        // ---Ende der Testausgabe
        if (doc.setContent(documentdata->text().toUtf8(), false, &errorStr, &errorLine, &errorColumn))
        {
            if (doc.documentElement().tagName().toLower() == "html")
                readElement(doc.documentElement(), documentdata->node());
            else
            {
                std::cerr << std::endl << std::endl
                        << std::endl << "error in CDocumentReader::read()"
                        << std::endl << " at \"if (doc.setContent())\" returned false;"
                        << std::endl << " file name: " << documentdata->url().toString().toStdString()
                        << std::endl << " error message: <html>-tag not found";
            }
        }
        else
        {
            std::cerr << std::endl << std::endl
                    << std::endl << "error in CDocumentReader::read()"
                    << std::endl << " at doc.setContent() returned false;"
                    << std::endl << " file name: " << documentdata->url().toString().toStdString()
                    << std::endl << " error message: "
                    << std::endl << errorStr.toStdString() << " line="
                    << std::endl << QString::number(errorLine).toStdString()
                    << std::endl << " column=" << QString::number(errorColumn).toStdString();
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
            CNode* new_node = new CNode(node, element.childNodes().at(i).nodeName().toLower(), node->layer() + 1);
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
                new_node->addAttribute("href", attributes.namedItem("href").nodeValue());
                _documentStack.push(new CDocumentData(QUrl(new_node->attributes()["href"]), new_node, _indexFileInfo, _fileType));
                std::cerr << std::endl << std::endl
                        << std::endl << "testing output: CDocumentReader::readElement()"
                        << std::endl << " at \"if (element.childNodes().at(i).nodeName().toLower() == \"a\")\" returned true"
                        << std::endl << " found subdocumunt href=" << new_node->attributes()["href"].toStdString();
            }
            QDomElement new_element = element.childNodes().at(i).toElement();
            readElement(new_element, new_node);
        }
    }
};
