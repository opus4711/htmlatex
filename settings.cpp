#include "settings.h"

Settings::Settings() : SETTINGSFILEPATH("htmlatex_settings.xml")
{
    if (!load())
        std::cerr << "Settings.load(): error loading settings file into domdocument" << std::endl;
};
bool Settings::load()
{
    // load settings from file
    QFile file(SETTINGSFILEPATH);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QString filecontent = QString(file.readAll()).toLatin1();
    file.close();
    QString errorStr = "";
    int errorLine = -1;
    int errorColumn = -1;
    return document.setContent(filecontent.toLatin1(),
                          false,
                          &errorStr,
                          &errorLine,
                          &errorColumn);
};
bool Settings::save()
{
    // save settings to file
    QFile file(SETTINGSFILEPATH);
    std::cerr << "Settings.save(): before file.open()" << std::endl;
    if (!file.open(QFile::WriteOnly | QFile::Text))
        return false;
    std::cerr << "Settings.save(): after file.open()" << std::endl;
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    document.save(stream, 0);
    file.close();
    std::cerr << "Settings.save(): after document.save()" << std::endl;
    return true;
};
QString Settings::latexpath() const
{
    QDomElement root = document.documentElement();
    return root.elementsByTagName("latexpath").at(0).firstChild().nodeValue();
};
QLocale::Country Settings::country() const
{
    QDomElement root = document.documentElement();
    // read language value
    int icountry = root.elementsByTagName("language").at(0).firstChild().nodeValue().toInt();
    // -1: retrieve system lanuage setting
    if (icountry == -1)
        return QLocale::system().country();
    else
        return (QLocale::Country)icountry;
};
void Settings::setLatexpath(QString path)
{
    QDomElement root = document.documentElement();
    root.elementsByTagName("latexpath").at(0).setNodeValue(path);
    std::cerr << "Settings.setLatexPath(): path: " << path.toStdString() << std::endl;
};
void Settings::setCountry(QLocale::Country country)
{
    QDomElement root = document.documentElement();
    root.elementsByTagName("language").at(0).setNodeValue(QString::number((int)country));
    std::cerr << "Settings.setCountry(): country: " << QString::number((int)country).toStdString() << std::endl;
};
