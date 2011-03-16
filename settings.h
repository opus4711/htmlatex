#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDomDocument>
#include <QLocale>
#include <QFile>
#include <QTextStream>
#include <iostream>

class Settings
{
private:
    const QString SETTINGSFILEPATH;
    QDomDocument document;
    bool load();
public:
    bool save();
    void setLatexpath(QString path);
    void setCountry(QLocale::Country country);
    QString latexpath() const;
    QLocale::Country country() const;
    // Constructor
    Settings();
};

#endif // SETTINGS_H
