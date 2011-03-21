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
    /** This is the only constructor.
        @param arguments is an array of strings which contains the startup argument
        of the application except the executable file's name and optional paramters.
        @param options is an array of strings which contains just the optional
        startup arguments of the application.
        @param parent is a pointer pointing to the parent widget (QDialog and
        QMainWindow are derived from QWidget).
        @author Bjoern
      */
    MainWindow(QStringList arguments, QStringList options, QWidget* parent);
    /** This is the destructor.
      */
    ~MainWindow();
private:
    /** This declaration allows access to the separated GUI source code via the
        short label ui.
        @author Bjoern
      */
    Ui::MainWindow* ui;
    /** The model is the data source of the treeView. The Model class is derived
        from the abstract class QAbstractItemModel and provides the functionality
        that a QTreeView object demands in order to display data.
        @author Bjoern
      */
    Model* _model;
    /** The _itemDelegate controls how the treeView displays data. The
        ItemDelegate class is derived from the QItemDelegate class. Its paint()
        method influences the drawing of the widget directly.
        @author Bjoern
      */
    ItemDelegate* _itemDelegate;
    /** The _settingsDialog is a modal dialog whose settings are saved to a
        binary file.
        @author Bjoern
      */
    SettingsDialog* _settingsDialog;
    /** The _translator translates the application's texts.
        @author Bjoern
      */
    QTranslator _translator;
    /** The _translationMapper provides two data objects: firstly a
        DocumentReaderData object which is used by the DocumentReader and
        secondly a key-value-pair structure which is used by the Converter.
        @author Bjoern
      */
    TranslationMapper* _translationMapper;
    /** The _converter converts the internal tree structure.
        @author Bjoern
      */
    Converter* _converter;
    /** This method performs opening and converting operations depending on the
        application's startup arguments.
        @param arguments is an array of strings which contains the startup argument
        of the application except the executable file's name and optional paramters.
        @param options is an array of strings which contains just the optional
        startup arguments of the application.
        @author Bjoern
      */
    void _performInitialOperations(QStringList arguments, QStringList options);
private slots:
    /** This slot is connected to _settingsDialog and is called when the user
        applies settings. It triggers the retranslation of the application's texts.
        @param language contains the information to which language the
        _translator is supposed to translate.
        @author Bjoern
      */
    void _languageChanged(QLocale::Country language);
    /** This slot is called when the user clicks the menu item or tool bar button
        for "open".
        @author Bjoern
      */
    void _open();
    /** This slot is called when the user clicks the menu item or tool bar button
        for "convert".
        @author Bjoern
      */
    void _convert();
    /** This slot is called when the user clicks the menu item or tool bar button
        for "set input definition".
        @author Bjoern
      */
    void _setInputDefinition();
    /** This slot is called when the user clicks the menu item or tool bar button
        for "set output definition".
        @author Bjoern
      */
    void _setOutputDefinition();
    /** This slot is called when the user clicks the menu item or tool bar button
        for "settings".
        @author Bjoern
      */
    void _showSettings();
    /** This slot is called when the user clicks the menu item or tool bar button
        for "about".
        @author Bjoern
      */
    void _about();
    /** This slot is called when the user clicks the right mouse button on the
        _treeView to show the context menu.
        @author Bjoern
      */
    void _showTreeViewContextMenu(QPoint point);
    /** This slot is called when the user chooses to remove a node from the treeView.
        @author Bjoern
      */
    void _treeViewRemoveNode();
    /** This slot is connected to the _converter.
        @author Bjoern
      */
    void _updateProgressBar(int percentage);
};

#endif // MAINWINDOW_H
