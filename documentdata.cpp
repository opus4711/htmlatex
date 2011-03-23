#include "documentdata.h"

DocumentData::DocumentData(QFileInfo fileinfo, Node* node, FileType filetype)
    : _text(""), _fileInfo(fileinfo), _preprocessed(false)
{
    this->_fileType = filetype;
    this->_node = node;
};
void DocumentData::_preprocessingHook()
{
    _preprocessHTML();
};
void DocumentData::_preprocessHTML()
{
    if (_fileType != DocumentData::JavaDocHTML)
        return;
    QString path = _fileInfo.filePath();
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        if (Settings::DEBUG)
        {
            std::cerr << tr("DocumentData._preprocessHTML() : can't preprocess file path: ").toStdString()
                    << path.toStdString() << std::endl;
        }
        return;
    }
    if (Settings::DEBUG)
    {
        std::cerr << tr("DocumentData._preprocessHTML() : preprocessing file path: ").toStdString()
                << path.toStdString() << std::endl;
    }
    _text = QString(file.readAll()).toLatin1();
    file.close();
    // processing document
    // add missing finalizing slashes to empty elements
    // the following two lines create an array of QString objects
    QStringList elements;
    elements << "br" << "img" << "hr" << "meta" << "link";
    QRegExp regex;
    foreach (QString element, elements)
    {
        regex = QRegExp("<" + element + // opening tag and tag name
                        "([^\\/>])*" // consume all characters except '/' and '>'
                        "(?!\\/)>"); // the character '/' is missing before '>'
        // the empty element stored in the iteration variable 'element' is found
        // without the character '/'
        while(regex.indexIn(_text, 0) >= 0)
        {
            // insert missing '/'
            // regex.indexIn() returns the found position and
            // regex.cap(0).count() is the number of characters of mathed string
            _text.insert(regex.indexIn(_text, 0) + regex.cap(0).count() - 1, "/");
        }
    }
    _preprocessed = true;
};
/**
  * @author Bjoern
  */
QString DocumentData::text()
{
    // the preprocessed document is stored in the attribute "_text"
    if (!_preprocessed)
        _preprocessingHook();
    return _text;
};
QFileInfo DocumentData::fileInfo() const
{
    return this->_fileInfo;
};
Node* DocumentData::node() const
{
    return this->_node;
};
