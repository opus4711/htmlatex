#ifndef CONSOLE_H
#define CONSOLE_H

#include "translationmapper.h"
#include "documentreader.h"
#include "converter.h"
#include <QObject>
#include <QString>
#include <iostream>

/** This class provides the command line functionality of the application.
  * @author Bjoern
  */
class Console : public QObject
{
    Q_OBJECT
public:
    /** This is the only constructor.
        @param <arguments> is an array of strings which contains the startup arguments
        of the application except the executable file's name and optional paramters.
        @param <options> is an array of strings which contains just the optional
        startup arguments of the application.
        @author Bjoern
      */
    Console(QStringList arguments, QStringList options);
private:
    /** This method processes the application's startup arguments and performs the
        conversion by means of a DocumentReader and a Converter object.
        @param <arguments> is an array of strings which contains the startup arguments
        of the application except the executable file's name and optional paramters.
        @param <options> is an array of strings which contains just the optional
        startup arguments of the application.
        @author Bjoern
      */
    void _performInitialOperations(QStringList arguments, QStringList options);
};

#endif // CONSOLE_H
