#include "translationmapper.h"

TranslationMapper::TranslationMapper()
{
};
void TranslationMapper::createDocumentReaderData(QString inputfilepath)
{
    QFile file(inputfilepath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        if(Settings::DEBUG)
        {
            std::cerr << "CTranslationMapper.createDocumentReaderData(): "
                    << "file.open() returned false\n\tPath: "
                    << inputfilepath.toStdString() << std::endl;
        }
        return;
    }
    // load content of the XML file into "filecontent"
    QString filecontent = QString(file.readAll()).toLatin1();
    file.close();
    QDomDocument doc;
    QString errorMsg = "";
    int errorLine = -1;
    int errorColumn = -1;
    if (doc.setContent(filecontent, &errorMsg, &errorLine, &errorColumn))
    {
        QDomElement root = doc.documentElement();
        QDomNode node = root.elementsByTagName("documentreference").at(0);
        if (!node.isNull())
        {
            QDomNamedNodeMap attributes = node.attributes();
            QString tagname = attributes.namedItem("tagname").nodeValue();
            QString urlcontainingattributename = attributes.namedItem("urlcontainingattributename").nodeValue();
            _documentReference = DocumentReaderData(tagname, urlcontainingattributename);
        }
    }
    else if (Settings::DEBUG)
    {
        std::cerr << "CTranslationMapper.createDocumentReaderData(): doc.setContent returned false"
                << "\n\tFilecontent: " << filecontent.toStdString() << std::endl;
    }
};
void TranslationMapper::createOutputElementMap(QString outputfilepath)
{
    _outputMap = QMap<QString,TranslationData>();
    QFile file(outputfilepath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        if(Settings::DEBUG)
        {
            std::cerr << "CTranslationMapper.createOutputElementMap(): "
                    << "file.open() returned false\n\tPath: "
                    << outputfilepath.toStdString() << std::endl;
        }
        return;
    }
    // load content of the XML file into "filecontent"
    QString filecontent = QString(file.readAll()).toLatin1();
    file.close();
    QDomDocument doc;
    QString errorMsg = "";
    int errorLine = -1;
    int errorColumn = -1;
    if (doc.setContent(filecontent, &errorMsg, &errorLine, &errorColumn))
    {
        QDomElement root = doc.documentElement();
        // create a node list of "node"-elements
        QDomNodeList nodes = root.elementsByTagName("node");
        for (int i = 0; i < nodes.count(); i++)
        {
            // create a node list from "node"-element's child nodes
            QDomNodeList subnodes = nodes.at(i).childNodes();
            TranslationData translationdata;
            for (int j = 0; j < subnodes.count(); j++)
            {
                if (subnodes.at(j).nodeName().toLower() == "from")
                    translationdata.setFrom(subnodes.at(j).firstChild().nodeValue());
                else if (subnodes.at(j).nodeName().toLower() == "key")
                    translationdata.setKey(subnodes.at(j).firstChild().nodeValue());
                else if (subnodes.at(j).nodeName().toLower() == "to")
                    translationdata.setTo(subnodes.at(j).firstChild().nodeValue());
                else if (subnodes.at(j).nodeName().toLower() == "requires")
                {
                    QDomNodeList requiresnodes = subnodes.at(j).childNodes();
                    for (int k = 0; k < requiresnodes.count(); k++)
                    {
                        TranslationDataNode datanode;
                        datanode.setName(requiresnodes.at(k).nodeName());
                        datanode.setContent(requiresnodes.at(k).firstChild().nodeValue());
                        QDomNamedNodeMap attributes = requiresnodes.at(k).attributes();
                        for (int l = 0; l < attributes.count(); l++)
                        {
                            datanode.addAttribute(attributes.item(l).nodeName(),
                                                  attributes.item(l).nodeValue());
                        }
                        translationdata.addRequiresNode(datanode);
                    }
                }
            }
            _outputMap[translationdata.key()] = translationdata;
        }
    }
    else if (Settings::DEBUG)
    {
        std::cerr << "CTranslationMapper.createOutputElementMap(): doc.setContent returned false"
                << "\n\tFilecontent: " << filecontent.toStdString() << std::endl;
    }
};
DocumentReaderData TranslationMapper::getDocumentReference() const
{
    return this->_documentReference;
};
QMap<QString,TranslationData> TranslationMapper::outputMap() const
{
    return this->_outputMap;
};
