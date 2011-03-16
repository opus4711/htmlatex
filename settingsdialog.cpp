#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->groupBox_language->setTitle(tr("Language"));
    ui->groupBox_latexpath->setTitle(tr("path to latex.exe"));
    ui->pushButton_apply->setText(tr("&Apply"));
    ui->pushButton_latexpath->setText(tr("&Browse"));
    ui->comboBox_language->addItem(tr("English"), QVariant(QLocale::C));
    ui->comboBox_language->addItem(tr("German"), QVariant(QLocale::Germany));
    connect(ui->pushButton_apply, SIGNAL(clicked()),
            this, SLOT(apply()));
};
SettingsDialog::~SettingsDialog()
{
    delete ui;
};
void SettingsDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
};
QString SettingsDialog::latexPath() const
{
    return ui->lineEdit_latexpath->text();
};
void SettingsDialog::apply()
{
    bool apply = true;
    QDir dir(ui->lineEdit_latexpath->text());
    if (!dir.exists())
    {
        QMessageBox msg(QMessageBox::Warning, tr("Error"),
                        tr("The path to the latex.exe doesn't exist.\n\nDo you still want to proceed?"),
                        QMessageBox::Yes|QMessageBox::No);
        if (msg.exec() == QMessageBox::No)
            apply = false;
    }
    if (apply)
    {
        Settings settings;
        int icountry = ui->comboBox_language->itemData(ui->comboBox_language->currentIndex()).toInt();
        settings.setCountry((QLocale::Country)icountry);
        settings.setLatexpath(ui->lineEdit_latexpath->text());
        accept();
    }
};
