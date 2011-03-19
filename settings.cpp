#include "settings.h"

Settings::Settings() : _SETTINGSFILEPATH("htmlatex_settings.dat")
{
    if (!_load())
    {
        _settingsMap["language"] = "82";
        _settingsMap["latexpath"] = "";
    }
};
bool Settings::DEBUG = true;
/** reads the settings from a binary data file
  */
bool Settings::_load()
{
    QFile file(_SETTINGSFILEPATH);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        std::cerr << "Settings.load() - file can't be opened for reading" << std::endl;
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
bool Settings::save()
{
    QFile file(_SETTINGSFILEPATH);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        std::cerr << "Settings.save() - file can't be opened for writing" << std::endl;
        return false;
    }
    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_4_6);
    stream << _settingsMap;
    file.close();
    return true;
};
QString Settings::getValue(QString key) const
{
    return _settingsMap[key];
};
void Settings::setValue(QString key, QString value)
{
    _settingsMap[key] = value;
};
