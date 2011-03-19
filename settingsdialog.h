#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "settings.h"
#include <QDialog>
#include <QDir>
#include <QProcess>
#include <QVariant>
#include <QMessageBox>
#include <QLocale>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::SettingsDialog *ui;
private slots:
    void apply();
signals:
    void languageChanged(QLocale::Country language);
public:
    void retranslateUi();
    // Constructor and Destructor
    SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
};

#endif // SETTINGSDIALOG_H
