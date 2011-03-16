#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "settings.h"
#include <QDialog>
#include <QDir>
#include <QMessageBox>

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
protected:
    void changeEvent(QEvent *e);
public:
    QString latexPath() const;
    // Constructor and Destructor
    SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
};

#endif // SETTINGSDIALOG_H