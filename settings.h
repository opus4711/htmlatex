#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDataStream>
#include <QFile>
#include <QMap>
#include <iostream>

class Settings
{
private:
    const QString SETTINGSFILEPATH;
    QMap<QString,QString> settingsMap;
    bool load();
public:
    bool save();
    void setValue(QString key, QString value);
    QString getValue(QString key) const;
    // Constructor
    Settings();
};

#endif // SETTINGS_H
