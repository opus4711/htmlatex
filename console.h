#ifndef CONSOLE_H
#define CONSOLE_H

#include "ctranslationmapper.h"
#include "cdocumentreader.h"
#include "cconverter.h"
#include <QObject>
#include <QString>
#include <iostream>

/** This class provides the command line functionality of the application.
    @author Bjoern
  */
class Console : public QObject
{
    Q_OBJECT
private:
    void _performInitialOperations(QStringList arguments, QStringList options);
public:
    // Constructor
    Console(QStringList arguments, QStringList options);
    ~Console();
};

#endif // CONSOLE_H
