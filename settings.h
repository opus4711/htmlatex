#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QDataStream>
#include <QFile>
#include <QMap>
#include <iostream>

/** This class stores settings variables for the application in a binary file.
    The settings are stored in a key-value-pair data structure (an associative
    array). The class member DEBUG is used all over the application to provide
    additional information about the steps of the processings if desired (verbose).
    Saving to and loading from the binary file is performed "automatically". When
    a variable is requested or set the loading or saving is performed implicitly.
  */
class Settings : public QObject
{
    Q_OBJECT
public:
    /** This constructor tries to load the settings from the binary file. If it
        doesn't exist it is created with default settings.
        @author Bjoern
      */
    Settings();
    /** This class attribute is used to enable or disable "verbose-mode".
        @author Bjoern
      */
    static bool DEBUG;
private:
    /** This is the binary file's file path. This file contains the settings. If
        it doesn't exist it is created "automatically" with default settings.
        @author Bjoern
      */
    const QString _SETTINGSFILEPATH;
    /** This is the associative array which stores the settings as key-value-pairs.
        @author Bjoern
      */
    QMap<QString,QString> _settingsMap;
    /** This method tries to load the settings from the binary file.
        @author Bjoern
      */
    bool _load();
    /** This method tries to save the settings to the binary file.
        @author Bjoern
      */
    bool _save();
public:
    /** This method sets the specified variable to the given value.
        @param <key> is the variable's name.
        @param <value> is the new variable's value.
        @author Bjoern
      */
    void setValue(QString key, QString value);
    /** This method returns the value of the specified variable.
        @param <key> is the variable's name.
        @author Bjoern
      */
    QString getValue(QString key);
};

#endif // SETTINGS_H
