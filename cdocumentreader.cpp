#include "cdocumentreader.h"

CDocumentReader::CDocumentReader()
{
};
CNode* CDocumentReader::read(QString path)
{
    QDomDocument doc;
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox msg(QMessageBox::Warning, QObject::tr("Error"), QObject::tr("An error occurred accessing the file") + "\n\n" + path);
        msg.exec();
        return 0;
    }
    QString errorStr = "";
    int errorLine = -1;
    int errorColumn = -1;
    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn))
    {
        QMessageBox msg(QMessageBox::Warning, QObject::tr("Error"), errorStr);
        msg.exec();
        return 0;
    }
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
        if (element.childNodes().at(i).nodeName().toLower() == "font")
        {
            QString additionaldata = "";
            QDomNamedNodeMap attributes = element.childNodes().at(i).attributes();
            additionaldata += "size:" + attributes.namedItem("size").nodeValue();
            new_node->setAdditionalData(additionaldata);
        }
        else if (element.childNodes().at(i).nodeName().toLower() == "td")
        {
            QString additionaldata = "";
            QDomNamedNodeMap attributes = element.childNodes().at(i).attributes();
            additionaldata += "align:" + attributes.namedItem("align").nodeValue() + ";";
            additionaldata += "valign:" + attributes.namedItem("valign").nodeValue() + ";";
            additionaldata += "width:" + attributes.namedItem("width").nodeValue();
            new_node->setAdditionalData(additionaldata);
        }
        else if (element.childNodes().at(i).nodeName().toLower() == "tr")
        {
            QString additionaldata = "";
            QDomNamedNodeMap attributes = element.childNodes().at(i).attributes();
            additionaldata += "bgcolor:" + attributes.namedItem("bgcolor").nodeValue();
            new_node->setAdditionalData(additionaldata);
        }
        else if (element.childNodes().at(i).nodeName().toLower() == "th")
        {
            QString additionaldata = "";
            QDomNamedNodeMap attributes = element.childNodes().at(i).attributes();
            additionaldata += "align:" + attributes.namedItem("align").nodeValue() + ";";
            additionaldata += "colspan:" + attributes.namedItem("colspan").nodeValue();
            new_node->setAdditionalData(additionaldata);
        }
        else if (element.childNodes().at(i).nodeName().toLower() == "a")
        {
            QDomNamedNodeMap attributes = element.childNodes().at(i).attributes();
            new_node->setReference(attributes.namedItem("href").nodeValue());
        }
        QDomElement new_element = element.childNodes().at(i).toElement();
        readElement(new_element, new_node);
    }
};
