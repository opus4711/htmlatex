#include "settings.h"

Settings::Settings() : SETTINGSFILEPATH("htmlatex_settings.dat")
{
    if (!load())
    {
        settingsMap["language"] = "82";
        settingsMap["latexpath"] = "";
    }
};
/** reads the settings from a binary data file
  */
bool Settings::load()
{
    QFile file(SETTINGSFILEPATH);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        std::cerr << "Settings.save() - file can't be opened for reading" << std::endl;
        return false;
    }
    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_4_6);
    stream >> settingsMap;
    file.close();
    return true;
};
/** writes the settings to a binary data file
  */
bool Settings::save()
{
    QFile file(SETTINGSFILEPATH);
    std::cerr << "Settings.save(): before file.open()" << std::endl;
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        std::cerr << "Settings.save() - file can't be opened for writing" << std::endl;
        return false;
    }
    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_4_6);
    stream << settingsMap;
    file.close();
    return true;
};
QString Settings::getValue(QString key) const
{
    return settingsMap[key];
};
void Settings::setValue(QString key, QString value)
{
    settingsMap[key] = value;
};
