#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "translationmapper.h"
#include "documentreader.h"
#include "model.h"
#include "itemdelegate.h"
#include "converter.h"
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
    Model* _model;
    // The _itemDelegate controls how the treeView displays data.
    ItemDelegate* _itemDelegate;
    // The _settingsDialog is a modal dialog whose settings are saved to binary file.
    SettingsDialog* _settingsDialog;
    // The _translator translates the application's texts.
    QTranslator _translator;
    // The _translationMapper provides key-value-pair structures which are used
    // reading the input data and creating the output data.
    TranslationMapper* _translationMapper;
    // The _converter converts the internal tree structure.
    Converter* _converter;
    // This method performs opening and converting operations depending on the
    // application's startup arguments.
    void _performInitialOperations(QStringList arguments, QStringList options);
private slots:
    // This slot is connected to _settingsDialog and is called when the user
    // applies settings.
    void _languageChanged(QLocale::Country language);
    // This slot is called when the user clicks the menu item or tool bar button
    // for "open".
    void _open();
    // This slot is called when the user clicks the menu item or tool bar button
    // for "convert".
    void _convert();
    // This slot is called when the user clicks the menu item or tool bar button
    // for "set input definition".
    void _setInputDefinition();
    // This slot is called when the user clicks the menu item or tool bar button
    // for "set output definition".
    void _setOutputDefinition();
    // This slot is called when the user clicks the menu item or tool bar button
    // for "settings".
    void _showSettings();
    // This slot is called when the user clicks the menu item or tool bar button
    // for "about".
    void _about();
    // This slot is called when the user clicks the right mouse button on the
    // _treeView to show the context menu.
    void _showTreeViewContextMenu(QPoint point);
    // This slot is called when the user chooses to remove a node from the treeView.
    void _treeViewRemoveNode();
    // This slot is connected to the _converter.
    void _updateProgressBar(int percentage);
};

#endif // MAINWINDOW_H
