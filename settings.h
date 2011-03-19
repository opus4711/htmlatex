#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDataStream>
#include <QFile>
#include <QMap>
#include <iostream>

class Settings
{
public:
    Settings();
    static bool DEBUG;
private:
    const QString _SETTINGSFILEPATH;
    QMap<QString,QString> _settingsMap;
    bool _load();
public:
    bool save();
    void setValue(QString key, QString value);
    QString getValue(QString key) const;
};

#endif // SETTINGS_H
