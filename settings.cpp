#include "settings.h"

Settings::Settings() : _SETTINGSFILEPATH("htmlatex_settings.dat")
{
    if (!_load())
    {
        // an integer value taken from the enumerator QLocale::Country
        _settingsMap["language"] = "82";
        _settingsMap["latexpath"] = "";
        // boolean value
        _settingsMap["verbose"] = "0";
        // boolean value
        _settingsMap["includesubdocuments"] = "1";
        _save();
    }
};
bool Settings::DEBUG = false;
/** reads the settings from a binary data file
  */
bool Settings::_load()
{
    QFile file(_SETTINGSFILEPATH);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        std::cerr << tr("Settings.load() - file can't be opened for reading").toStdString() << std::endl;
        return false;
    }
    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_4_6);
    stream >> _settingsMap;
    file.close();
    return true;
};
/** writes the settings to a binary data file
  */
bool Settings::_save()
{
    QFile file(_SETTINGSFILEPATH);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        std::cerr << tr("Settings.save() - file can't be opened for writing").toStdString() << std::endl;
        return false;
    }
    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_4_6);
    stream << _settingsMap;
    file.close();
    return true;
};
QString Settings::getValue(QString key)
{
    if (!_load())
    {
        if (DEBUG)
        {
            std::cerr << tr("Settings.getValue() returned default value for key: ").toStdString() << key.toStdString()
            << tr(", value: ").toStdString() << _settingsMap[key].toStdString() << std::endl;
        }
    }
    return _settingsMap[key];
};
void Settings::setValue(QString key, QString value)
{
    _settingsMap[key] = value;
    if (key == "verbose")
        this->DEBUG = (bool)value.toInt();
    _save();
};
