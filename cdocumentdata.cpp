#include "cdocumentdata.h"

CDocumentData::CDocumentData(QUrl url, CNode* node, QFileInfo indexfileinfo, FileType filetype)
{
    this->_url = url;
    this->_node = node;
    this->_text = "";
    this->_indexFileInfo = indexfileinfo;
    this->_fileType = filetype;
    this->_preprocessed = false;
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
    if (!_preprocessed)
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
    QRegExp regex;
    foreach (QString element, elements)
    {
        regex = QRegExp("<" + element + // opening tag and tag name
                        "([^\\/>])*" // consume all characters except '/' and '>'
                        "(?!\/)>"); // the character '/' is missing before '>'
        if (_text.indexOf(regex, 0) >= 0)
        {
            for (int i = 0; i < regex.captureCount(); i++)
            {
                _text.insert(_text.indexOf(regex, 0) + regex.capturedTexts().at(i).count() - 1, "/");
            }
        }
    }

    msg.setText(_text);
    msg.exec();
    _preprocessed = true;
};
