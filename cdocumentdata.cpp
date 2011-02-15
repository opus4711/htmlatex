#include "cdocumentdata.h"

CDocumentData::CDocumentData(QUrl url, CNode* node, QFileInfo indexfileinfo, FileType filetype)
{
    this->_url = url;
    this->_node = node;
    this->_text = "";
    this->_indexFileInfo = indexfileinfo;
    this->_fileType = filetype;
};
QUrl CDocumentData::url() const
{
    return this->_url;
};
CNode* CDocumentData::node() const
{
    return this->_node;
};
QString CDocumentData::text()
{
    // the preprocessed document is stored in the attribute "_text"
    preprocessingHook();
    return _text;
};
void CDocumentData::preprocessingHook()
{
    preprocessHTML();
};
/** This method changes the specified HTML-file in order to gain well-formed XML (XHTML).
  * @author Björn Kaiser
  */
void CDocumentData::preprocessHTML()
{
    if (_fileType != CDocumentData::JavaDocHTML)
        return;
    QString path = "";
    if (_url.isRelative())
        path = _indexFileInfo.absolutePath() + "/" + _url.path();
    else
        path = _url.path();
    QFile file(path);
    if (!file.open(QFile::ReadWrite | QFile::Text))
        return;
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    _text = stream.readAll();
    file.close();
    QMessageBox msg;
    msg.setTextFormat(Qt::PlainText);
    // processing document
    // add missing finalizing slashes to empty elements
    QStringList elements;
    elements << "br" << "img" << "hr";
    QRegExp rx;
    foreach (QString element, elements)
    {
        rx = QRegExp("<" + element + "(\\s*[a-zA-Z]+=.+)*\\s*(?<!\\/)>");
        if (_text.indexOf(rx, 0) >= 0)
        {
            //rx.indexIn(content, 0);
            msg.setText(element + ": " + rx.capturedTexts().at(0));
            msg.exec();
            //content.insert(content.indexOf(rx, 0) + rx.capturedTexts().at(0).count() - 1, "TEST");
        }
    }

    msg.setText(_text);
    msg.exec();
};
