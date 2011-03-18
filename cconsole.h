#ifndef CCONSOLE_H
#define CCONSOLE_H

#include "ctranslationmapper.h"
#include "cdocumentreader.h"
#include "cconverter.h"
#include <QObject>
#include <QString>
#include <iostream>

/** This class provides the command line functionality of the application.
    @author Bjoern
  */
class CConsole : public QObject
{
    Q_OBJECT
private:
    void _performInitialOperations(QStringList arguments, QStringList options);
public:
    // Constructor
    CConsole(QStringList arguments, QStringList options);
    ~CConsole();
};

#endif // CCONSOLE_H
