#include "ctranslationmapper.h"

CTranslationMapper::CTranslationMapper()
{
};
void CTranslationMapper::createInputElementMap(QString inputfilepath)
{
};
void CTranslationMapper::createOutputElementMap(QString outputfilepath)
{
    outputMap = QMap<QString,CTranslationData>();
    QFile file(outputfilepath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        std::cerr << "\nCTranslationMapper.createOutputElementMap(): file.open() returned false: path: " << outputfilepath.toStdString();
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
            CTranslationData translationdata;
            for (int j = 0; j < subnodes.count(); j++)
            {
                if (subnodes.at(j).nodeName().toLower() == "from")
                    translationdata.setFrom(subnodes.at(j).nodeValue());
                else if (subnodes.at(j).nodeName().toLower() == "to")
                    translationdata.setTo(subnodes.at(j).nodeValue());
                else if (subnodes.at(j).nodeName().toLower() == "requires")
                {
                    QDomNodeList requiresnodes = subnodes.at(j).childNodes();
                    for (int k = 0; k < requiresnodes.count(); k++)
                    {
                        CTranslationDataNode datanode;
                        datanode.setName(requiresnodes.at(k).nodeName());
                        datanode.setContent(requiresnodes.at(k).nodeValue());
                        QDomNamedNodeMap attributes = requiresnodes.at(k).attributes();
                        for (int l = 0; l < attributes.count(); l++)
                            datanode.addAttribute(attributes.item(l).nodeName(), attributes.item(l).nodeValue());
                        translationdata.addRequiresNode(datanode);
                    }
                }
            }
            outputMap[translationdata.from()] = translationdata;
        }
    }
    else
        std::cerr << "\nCTranslationMapper.createOutputElementMap(): doc.setContent returned false: filecontent: " << filecontent.toStdString();
};
