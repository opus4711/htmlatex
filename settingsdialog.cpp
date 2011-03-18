#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog), _restartRequired(false)
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
    Settings settings;
    ui->lineEdit_latexpath->setText(settings.getValue("latexpath"));
    // select language specified by settings file
    _initiallySelectedLanguage = QVariant((QLocale::Country)settings.getValue("language").toInt());
    // retrieve corresponding comboBox item index
    int itemindex = ui->comboBox_language->findData(_initiallySelectedLanguage);
    ui->comboBox_language->setCurrentIndex(itemindex);
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
bool SettingsDialog::restartRequired() const
{
    return this->_restartRequired;
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
        settings.setValue("language", ui->comboBox_language->itemData(ui->comboBox_language->currentIndex()).toString());
        settings.setValue("latexpath", ui->lineEdit_latexpath->text());
        settings.save();
        if (_initiallySelectedLanguage != ui->comboBox_language->itemData(ui->comboBox_language->currentIndex()))
        {
            QLocale::Country language = (QLocale::Country)ui->comboBox_language->itemData(ui->comboBox_language->currentIndex()).toInt();
            QTranslator translator;
            if (language == QLocale::Germany)
                translator.load(QString("htmlatex_de.qm"));
            else
                translator.load(QString("htmlatex_en.qm"));
            qApp->installTranslator(&translator);
        }
        accept();
    }
};
