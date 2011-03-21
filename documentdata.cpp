#include "documentdata.h"

/** This class holds information of one document (i.e. webpage). The information
  * consists of the file path (URL), a reference pointing to the corresponding node
  * in the document tree, which represents the whole document. This also stores a
  * QFileInfo-object for the whole documents' index document. The appropriate
  * document preprocessing is chosen by means of distinguished file types.
  * @author Bjoern Kaiser
  */
DocumentData::DocumentData(QFileInfo fileinfo, CNode* node, FileType filetype)
{
    this->_fileInfo = fileinfo;
    this->_node = node;
    this->_text = "";
    this->_fileType = filetype;
    this->_preprocessed = false;
};
/** Returns the URL to this document.
  * @author Bjoern Kaiser
  */
QFileInfo DocumentData::fileInfo() const
{
    return this->_fileInfo;
};
/** Returns the pointer to the corresponding tree node of the whole document.
  * @author Bjoern Kaiser
  */
CNode* DocumentData::node() const
{
    return this->_node;
};
/** Returns the document as a preprocessed QString.
  * @author Bjoern Kaiser
  */
QString DocumentData::text()
{
    // the preprocessed document is stored in the attribute "_text"
    if (!_preprocessed)
        preprocessingHook();
    return _text;
};
/** This hook-method calls all preprocessing methods.
  * @author Bjoern Kaiser
  */
void DocumentData::preprocessingHook()
{
    preprocessHTML();
};
/** This method changes the specified HTML-file in order to gain well-formed XML (XHTML).
  * @author Bjoern Kaiser
  */
void DocumentData::preprocessHTML()
{
    if (_fileType != DocumentData::JavaDocHTML)
        return;
    QString path = _fileInfo.filePath();
    if (Settings::DEBUG)
    {
        std::cerr << "Path: " << path.toStdString() << std::endl;
    }
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return;
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
        // the empty element stored in the iteration variable 'element' is found without a '/'
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
