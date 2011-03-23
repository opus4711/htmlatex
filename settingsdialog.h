#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "settings.h"
#include "constants.h"
#include <QDialog>
#include <QFileInfo>
#include <QProcess>
#include <QVariant>
#include <QMessageBox>
#include <QLocale>
#include <QFileDialog>

/** This namespace is introduced to separate GUI related source code
    @author Bjoern
  */
namespace Ui {
    class SettingsDialog;
}

/** The SettingsDialog provides a convenient way to change the application's
    settings such as the language or the inclusion of subdocuments. It makes use of
    the Settings class to laod the settings from and save them to a binary file.
    @author Bjoern
  */
class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    /** This is the only constructor which initializes the GUI.
        @author Bjoern
      */
    SettingsDialog(QWidget *parent = 0);
    /** This is the destructor.
        @author Bjoern
      */
    ~SettingsDialog();
private:
    /** This declaration allows access to the separated GUI source code via the
        short label ui.
        @author Bjoern
      */
    Ui::SettingsDialog *ui;
private slots:
    /** This slot is called when the user clicks the push button "apply".
        @author Bjoern
      */
    void _apply();
    /** This slot is called when the user clicks the push button "browse".
        @author Bjoern
      */
    void _open();
signals:
    /** This signal is connected to mainWindow and is raised when the user applies
        settings. It triggers the retranslation of the application's texts.
        @param <language> contains the information to which language mainWindow's
        _translator is supposed to translate.
        @author Bjoern
      */
    void languageChanged(QLocale::Country language);
public:
    /** This method is called by the mainWindow's _languageChanged slot after the
        mainWindow's _translator has been switched to another language. It triggers
        the retranslation of the SettingsDialog's texts.
        @author Bjoern
      */
    void retranslateUi();
};

#endif // SETTINGSDIALOG_H
