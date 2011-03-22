#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "settings.h"
#include <QDialog>
#include <QFileInfo>
#include <QProcess>
#include <QVariant>
#include <QMessageBox>
#include <QLocale>
#include <QFileDialog>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::SettingsDialog *ui;
private slots:
    void _apply();
    void _open();
signals:
    void languageChanged(QLocale::Country language);
public:
    void retranslateUi();
    /** Constructor */
    SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
};

#endif // SETTINGSDIALOG_H
