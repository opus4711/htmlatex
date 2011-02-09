#include "cdocumentreader.h"

CDocumentReader::CDocumentReader()
{
    fileType = CDocumentReader::Unknown;
};
/** The hook method determines if the source file is well-formed XML and initiates
  * a suitable prior treatment.
  * @author Björn Kaiser
  */
void CDocumentReader::hook(QString path)
{
    QFile file(path);
    if (!file.open(QFile::ReadWrite | QFile::Text))
        return;
    QTextStream stream(&file);
    QString content = stream.readAll();
    content = content.replace("<br>", "<br/>", Qt::CaseInsensitive);
    content = content.replace("<hr>", "<hr/>", Qt::CaseInsensitive);
    //content = content.replace(QRegExp("", Qt::CaseInsensitive, QRegExp::RegExp));
    file.resize(0);
    stream << content.toUtf8();
    file.close();
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
    // Notiz: Wenn eine Datei fehlt, bricht der Einlesevorgang momentan ab.
    QDomDocument doc;
    QFile* file = new QFile(path);
    if (!file->open(QFile::ReadWrite | QFile::Text))
    {
        QMessageBox msg(QMessageBox::Warning, QObject::tr("Error"), QObject::tr("An error occurred accessing the file") + "\n\n" + path);
        msg.exec();
        file->close();
        return 0;
    }
    QString errorStr = "";
    int errorLine = -1;
    int errorColumn = -1;
    if (!doc.setContent(file, false, &errorStr, &errorLine, &errorColumn))
    {
        //QMessageBox msg(QMessageBox::Warning, QObject::tr("Error"), errorStr + ": line: " + QString::number(errorLine) + ", column: " + QString::number(errorColumn));
        //msg.exec();
        //file.close();
        //return 0;
        hook(path);
        file->close();
        delete file;
        file = new QFile(path);
        doc.setContent(file, false, &errorStr, &errorLine, &errorColumn);
    }
    file->close();
    QDomElement docroot = doc.documentElement();
    if (docroot.tagName().toLower() != QString("html"))
    {
        QMessageBox msg(QMessageBox::Warning, QObject::tr("Error - No valid HTML file."), QObject::tr("The root element <html> is missing."));
        msg.exec();
        return 0;
    }
    // begin processing the document
    CNode* root = new CNode(0, "html");
    readElement(docroot, root);
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
            new_node->addChild(read(_sourceFileInfo.absolutePath() + "/" + new_node->attributes()["href"]));
        }
        else if (element.childNodes().at(i).nodeName().toLower() == "#text")
            new_node->setContent(element.childNodes().at(i).nodeValue());
        QDomElement new_element = element.childNodes().at(i).toElement();
        readElement(new_element, new_node);
    }
};
