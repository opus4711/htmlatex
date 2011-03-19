#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ctranslationmapper.h"
#include "cdocumentreader.h"
#include "cmodel.h"
#include "citemdelegate.h"
#include "constants.h"
#include "cconverter.h"
#include "settingsdialog.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QTranslator>
#include <QTextCodec>

namespace Ui
{
    class MainWindow;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow* ui;
    CModel* model;
    CItemDelegate* itemDelegate;
    SettingsDialog* _settingsDialog;
    QTranslator _translator;
    CTranslationMapper* translationMapper;
    CConverter* converter;
    void performInitialOperations(QStringList arguments, QStringList options);
private slots:
    void open();
    void convert();
    void setInputDefinition();
    void setOutputDefinition();
    void about();
    void showSettings();
    void languageChanged(QLocale::Country language);
public:
    // constructor and destructor
    MainWindow(QStringList arguments, QStringList options, QWidget* parent);
    ~MainWindow();
};

#endif // MAINWINDOW_H
