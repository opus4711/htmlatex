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

/** This namespace is introduced to separate GUI related source code
    @author Bjoern
  */
namespace Ui
{
    class MainWindow;
};
/** This is the central class of the GUI application. The treeView on the left
    hand side displays the opened document as a tree structure and allows
    modification via context menu. The textEdit on the right hand side displays
    the conversion output and can be edited directly.
    @author Bjoern
  */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    // This is the only constructor.
    MainWindow(QStringList arguments, QStringList options, QWidget* parent);
    // This is the destructor.
    ~MainWindow();
private:
    // This declaration allows access to the separated GUI source code via the
    // short label ui.
    Ui::MainWindow* ui;
    // The model is the data source of the treeView.
    CModel* _model;
    // The _itemDelegate controls how the treeView displays data.
    CItemDelegate* _itemDelegate;
    // The _settingsDialog is a modal dialog whose settings are saved to binary file.
    SettingsDialog* _settingsDialog;
    // The _translator translates the application's texts.
    QTranslator _translator;
    // The _translationMapper provides key-value-pair structures which are used
    // reading the input data and creating the output data.
    CTranslationMapper* _translationMapper;
    // The _converter converts the internal tree structure.
    CConverter* _converter;
    // This method performs opening and converting operations depending on the
    // application's startup arguments.
    void _performInitialOperations(QStringList arguments, QStringList options);
private slots:
    // This slot is connected to _settingsDialog and is called when the user
    // applies settings.
    void languageChanged(QLocale::Country language);
    // This slot is called when the user clicks the menu item or tool bar button
    // for "open".
    void open();
    // This slot is called when the user clicks the menu item or tool bar button
    // for "convert".
    void convert();
    // This slot is called when the user clicks the menu item or tool bar button
    // for "set input definition".
    void setInputDefinition();
    // This slot is called when the user clicks the menu item or tool bar button
    // for "set output definition".
    void setOutputDefinition();
    // This slot is called when the user clicks the menu item or tool bar button
    // for "settings".
    void showSettings();
    // This slot is called when the user clicks the menu item or tool bar button
    // for "about".
    void about();
};

#endif // MAINWINDOW_H
