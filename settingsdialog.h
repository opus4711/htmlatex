#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "settings.h"
#include <QDialog>
#include <QDir>
#include <QProcess>
#include <QVariant>
#include <QMessageBox>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::SettingsDialog *ui;
    QVariant _initiallySelectedLanguage;
    bool _restartRequired;
private slots:
    void apply();
protected:
    void changeEvent(QEvent *e);
public:
    bool restartRequired() const;
    // Constructor and Destructor
    SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
};

#endif // SETTINGSDIALOG_H
