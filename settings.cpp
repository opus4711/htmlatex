#include "settings.h"

Settings::Settings() : SETTINGSFILEPATH("htmlatex_settings.xml")
{
    _country = QLocale::system().country();
    _latexpath = "";
    load();
};
bool Settings::load()
{
    // load settings from file
    QFile file(SETTINGSFILEPATH);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QString filecontent = QString(file.readAll()).toLatin1();
    file.close();
    QDomDocument doc;
    QString errorStr = "";
    int errorLine = -1;
    int errorColumn = -1;
    if (doc.setContent(filecontent.toLatin1(),
                       false,
                       &errorStr,
                       &errorLine,
                       &errorColumn))
    {
        QDomElement root = doc.documentElement();
        // read language value
        int icountry = root.elementsByTagName("language").at(0).firstChild().nodeValue().toInt();
        // -1: retrieve system lanuage setting
        if (icountry == -1)
            _country = QLocale::system().country();
        else
            _country = (QLocale::Country)icountry;
        // read latexpath
        _latexpath = root.elementsByTagName("latexpath").at(0).firstChild().nodeValue();
    }
    return true;
};
bool Settings::save()
{
    // save settings to file
    QFile file(SETTINGSFILEPATH);
    if (!file.open(QFile::ReadWrite | QFile::Text))
        return false;
    //QString filecontent = QString(file.readAll()).toLatin1();
    QDomDocument doc;
    QString errorStr = "";
    int errorLine = -1;
    int errorColumn = -1;
    if (doc.setContent(&file,
                       false,
                       &errorStr,
                       &errorLine,
                       &errorColumn))
    {
        QDomElement root = doc.documentElement();
        // write language value
        root.elementsByTagName("language").at(0).firstChild().setNodeValue(QString::number((int)_country));
        // write latexpath
        root.elementsByTagName("latexpath").at(0).firstChild().setNodeValue(_latexpath);
    }
    file.close();
    return true;
};
QString Settings::latexpath() const
{
    return this->_latexpath;
};
QLocale::Country Settings::country() const
{
    return (QLocale::Country)this->_country;
};
void Settings::setLatexpath(QString path)
{
    this->_latexpath = path;
};
void Settings::setCountry(QLocale::Country country)
{
    this->_country = country;
};
