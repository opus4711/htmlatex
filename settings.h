#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QDataStream>
#include <QFile>
#include <QMap>
#include <iostream>

class Settings : public QObject
{
    Q_OBJECT
public:
    Settings();
    static bool DEBUG;
private:
    const QString _SETTINGSFILEPATH;
    QMap<QString,QString> _settingsMap;
    bool _load();
    bool _save();
public:
    void setValue(QString key, QString value);
    QString getValue(QString key);
};

#endif // SETTINGS_H
