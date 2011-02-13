#include "cdocumentreader.h"

CDocumentReader::CDocumentReader()
{
    fileType = CDocumentReader::Unknown;
};
QString CDocumentReader::toString(CNode* root)
{
    return nodeToString(root, 0);
};
/** Returns a string created from the specified node.
  * @author Björn Kaiser
  */
QString CDocumentReader::nodeToString(CNode* node, int ebene)
{
    int whitespaces = 5;
    QString result = "";
    if (node != 0)
    {
        // adds whitespaces to structurize string output
        for (int j = 0; j < ebene * whitespaces; j++)
            result += " ";
        result += "<" + node->name() + " id=\"" + QString::number(node->ID()) + "\"";
        QMapIterator<QString, QString> iterator(node->attributes());
        while (iterator.hasNext())
        {
            iterator.next();
            result += " " + iterator.key() + "=\"" + iterator.value() + "\"";
        }
        result += ">\n";
        if (node->name() == "#text")
        {
            // adds whitespaces to structurize string output
            for (int j = 0; j < (ebene + 1) * whitespaces; j++)
                result += " ";
            result += node->content() + "\n";
        }
        for (int i = 0; i < node->count(); i++)
            result += nodeToString(node->childAt(i), ebene + 1);
        // adds whitespaces to structurize string output
        for (int j = 0; j < ebene * whitespaces; j++)
            result += " ";
        result += "</" + node->name() + ">\n";
    }
    return result;
};
/** This method changes the specified HTML-file in order to gain well-formed XML.
  * @author Björn Kaiser
  */
void CDocumentReader::preprocessJavaDocHTML(QString path)
{
    QFile file(path);
    if (!file.open(QFile::ReadWrite | QFile::Text))
        return;
    QTextStream stream(&file);
    QString content = stream.readAll();
    stream.setCodec("UTF-8"); // use UTF-8
    // CParser parser;
    // QList<CNode*> nodes = parser.parseHTML(path);

    // resize(0) flushes / empties the file
    file.resize(0);
    stream << content; // .toUtf8(); <- DIDN'T WORK PROPERLY
    file.close();
};
/** This method determines if the source file is well-formed XML and initiates
  * a suitable prior treatment.
  * @author Björn Kaiser
  */
void CDocumentReader::preprocessingHook(QString path)
{
    switch (fileType)
    {
        case CDocumentReader::JavaDocHTML :
            preprocessJavaDocHTML(path); break;
        default : break;
    }
};
/** This method
  * @param filetype contains the file filter string selected previously.
  * @author Björn Kaiser
  */
CNode* CDocumentReader::read(QString sourcefilepath, QString filefilter)
{
    _sourceFileInfo = QFileInfo(sourcefilepath);
    if (filefilter == "JavaDoc (*.html *.htm)")
        fileType = CDocumentReader::JavaDocHTML;
    else if (filefilter == "any file (*.*)")
        fileType = CDocumentReader::Unknown;
    else
        fileType = CDocumentReader::Unknown;
    return read(_sourceFileInfo.filePath());
};
CNode* CDocumentReader::read(QString path)
{
    CNode* root = new CNode(0, "html");
    // add the index document to the stack of documents
    documentStack.push(DocumentData(path, root));
    // begin processing the documents stored on the document stack
    while(!documentStack.isEmpty())
    {
        DocumentData documentdata = documentStack.pop();
        QFile file(documentdata.path);
        if (file.open(QFile::ReadWrite | QFile::Text))
        {
            preprocessingHook(documentdata.path);
            QDomDocument doc;
            QString errorStr = "";
            int errorLine = -1;
            int errorColumn = -1;
            if (doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn))
            {
                if (doc.documentElement().tagName().toLower() == "html")
                    readElement(doc.documentElement(), documentdata.node);
            }
        }
        file.close();
    }
    return root;
};
void CDocumentReader::readElement(QDomElement element, CNode* node)
{
    for (int i = 0; i < element.childNodes().count(); i++)
    {
        CNode* new_node = new CNode(node, element.childNodes().at(i).nodeName().toLower());
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
            // HINWEIS: KEINE UNTERSCHEIDUNG ABSOLUTER UND RELATIVER PFADE!!!
            documentStack.push(DocumentData(QString(_sourceFileInfo.absolutePath() + "/" + new_node->attributes()["href"]), new_node));
        }
        else if (element.childNodes().at(i).nodeName().toLower() == "#text")
            new_node->setContent(element.childNodes().at(i).nodeValue());
        QDomElement new_element = element.childNodes().at(i).toElement();
        readElement(new_element, new_node);
    }
};
