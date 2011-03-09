#ifndef CCONSOLE_H
#define CCONSOLE_H

#include "cdocumentreader.h"
#include "ctranslationmapper.h"
#include <QObject>
#include <QString>

#include <iostream>

class CConsole : public QObject
{
    Q_OBJECT
private:
    void performInitialOperations(int argc, char* argv[]);
public:
    // Constructor
    CConsole(int argc, char* argv[]);
    ~CConsole();
};

#endif // CCONSOLE_H
