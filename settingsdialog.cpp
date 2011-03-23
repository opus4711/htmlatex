#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->comboBox_language->addItem(tr("English"), QVariant(QLocale::C));
    ui->comboBox_language->addItem(tr("German"), QVariant(QLocale::Germany));
    connect(ui->pushButton_apply, SIGNAL(clicked()),
            this, SLOT(_apply()));
    connect(ui->pushButton_latexpath, SIGNAL(clicked()),
            this, SLOT(_open()));
    Settings settings;
    ui->lineEdit_latexpath->setText(settings.getValue("latexpath"));
    // select language specified by settings file
    QLocale::Country initially_selected_language = (QLocale::Country)settings.getValue("language").toInt();
    // retrieve corresponding comboBox item index
    int itemindex = ui->comboBox_language->findData(initially_selected_language);
    ui->comboBox_language->setCurrentIndex(itemindex);
    ui->checkBox_verbose->setChecked((bool)settings.getValue("verbose").toInt());
    ui->checkBox_includesubdocuments->setChecked((bool)settings.getValue("includesubdocuments").toInt());
};
SettingsDialog::~SettingsDialog()
{
    delete ui;
};
void SettingsDialog::_apply()
{
    bool apply = true;
    QFileInfo fileinfo(ui->lineEdit_latexpath->text());
    if (!fileinfo.exists())
    {
        QMessageBox msg(QMessageBox::Warning, tr("Error"),
                        tr("The file path doesn't exist.\n\nDo you still want to proceed?"),
                        QMessageBox::Yes|QMessageBox::No);
        if (msg.exec() == QMessageBox::No)
            apply = false;
    }
    else if (!fileinfo.isFile())
    {
        QMessageBox msg(QMessageBox::Warning, tr("Error"),
                        tr("No file path specified.\n\nDo you still want to proceed?"),
                        QMessageBox::Yes|QMessageBox::No);
        if (msg.exec() == QMessageBox::No)
            apply = false;
    }
    if (apply)
    {
        Settings settings;
        settings.setValue("language", ui->comboBox_language->itemData(ui->comboBox_language->currentIndex()).toString());
        settings.setValue("latexpath", ui->lineEdit_latexpath->text());
        settings.setValue("includesubdocuments", QString::number((int)ui->checkBox_includesubdocuments->isChecked()));
        settings.setValue("verbose", QString::number((int)ui->checkBox_verbose->isChecked()));
        QLocale::Country language = (QLocale::Country)ui->comboBox_language->itemData(ui->comboBox_language->currentIndex()).toInt();
        emit languageChanged(language);
        ui->retranslateUi(this);
        accept();
    }
};
void SettingsDialog::_open()
{
    QFileDialog* dialog = new QFileDialog(this,
                                          tr("Set latex executable"),
                                          "",
                                          tr("executable (*.exe);;any file (*.*)"));
    // retrieve source file path and type
    if (dialog->exec() == QFileDialog::Accepted)
        ui->lineEdit_latexpath->setText(dialog->selectedFiles().at(0));
    delete dialog;
};
void SettingsDialog::retranslateUi()
{
    ui->retranslateUi(this);
};
