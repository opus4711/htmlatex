#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDomDocument>
#include <QLocale>
#include <QFile>

class Settings
{
private:
    const QString SETTINGSFILEPATH;
    QString _latexpath;
    QLocale::Country _country;
public:
    bool load();
    bool save();
    QString latexpath() const;
    QLocale::Country country() const;
    void setLatexpath(QString path);
    void setCountry(QLocale::Country country);
    // Constructor
    Settings();
};

#endif // SETTINGS_H
