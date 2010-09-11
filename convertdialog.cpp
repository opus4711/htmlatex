#include "convertdialog.h"
#include "ui_convertdialog.h"

ConvertDialog::ConvertDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConvertDialog)
{
    ui->setupUi(this);
    ui->pushButton_convert->setText(tr("Convert"));
    ui->pushButton_sourcefile->setText(tr("Browse"));
    ui->pushButton_targetdefinition->setText(tr("Browse"));
    ui->pushButton_targetfile->setText(tr("Browse"));
    this->setWindowTitle(tr("Convert"));
    connect(ui->pushButton_convert, SIGNAL(clicked()),
            this, SLOT(convert()));
    connect(ui->pushButton_targetdefinition, SIGNAL(clicked()),
            this, SLOT(browse_targetdefinition()));
    connect(ui->pushButton_targetfile, SIGNAL(clicked()),
            this, SLOT(browse_targetfile()));
    connect(ui->pushButton_sourcefile, SIGNAL(clicked()),
            this, SLOT(browse_sourcefile()));
};
ConvertDialog::~ConvertDialog()
{
    delete ui;
};
void ConvertDialog::changeEvent(QEvent *e)
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
void ConvertDialog::browse_targetdefinition()
{
    QFileDialog dialog(this, tr("Select Target Definition File"), QDir::currentPath(), "JavaDoc (*.html *.htm)");
    if (dialog.exec() == QFileDialog::Accepted)
    {
        ui->lineEdit_targetdefinition->setText(dialog.selectedFiles()[0]);
    }
};
void ConvertDialog::browse_sourcefile()
{
    QFileDialog dialog(this, tr("Select Source File"), QDir::currentPath(), "JavaDoc (*.html *.htm)");
    if (dialog.exec() == QFileDialog::Accepted)
    {
        ui->lineEdit_sourcefile->setText(dialog.selectedFiles()[0]);
    }
};
void ConvertDialog::browse_targetfile()
{
    QFileDialog dialog(this, tr("Set Target File"), QDir::currentPath(), "Tex (*.tex);;JavaDoc (*.html *.htm);;any file (*.*)");
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() == QFileDialog::Accepted)
    {
        ui->lineEdit_targetfile->setText(dialog.selectedFiles()[0]);
    }
};
QString ConvertDialog::getTargetFilePath()
{
    return ui->lineEdit_targetfile->text();
};
QString ConvertDialog::getTargetDefinitionFilePath()
{
    return ui->lineEdit_targetdefinition->text();
};
QString ConvertDialog::getSourceFilePath()
{
    return ui->lineEdit_sourcefile->text();
};
void ConvertDialog::convert()
{
    if (!ui->lineEdit_targetdefinition->text().isEmpty()
        & !ui->lineEdit_targetfile->text().isEmpty()
        & !ui->lineEdit_sourcefile->text().isEmpty())
        this->accept();
    else
    {
        QMessageBox msg(QMessageBox::Warning, tr("Error"), tr("You must select a source file, a target file and a target definition file."));
        msg.exec();
    }
};
