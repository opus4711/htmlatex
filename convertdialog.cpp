#include "convertdialog.h"
#include "ui_convertdialog.h"

ConvertDialog::ConvertDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConvertDialog)
{
    ui->setupUi(this);
    ui->pushButton_convert->setText(tr("Convert"));
    ui->pushButton_sourcefile->setText(tr("Browse"));
    ui->pushButton_targetfile->setText(tr("Browse"));
    this->setWindowTitle(tr("Convert"));
    connect(ui->pushButton_convert, SIGNAL(clicked()),
            this, SLOT(convert()));
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
void ConvertDialog::browse_sourcefile()
{
    //QFileDialog dialog(this, tr("Select Source File"), QDir::currentPath(), "JavaDoc (*.html *.htm);;any file (*.*)");
    QFileDialog dialog(this, tr("Set Target File"), "../html_examples", "JavaDoc (*.html *.htm);;any file (*.*)");
    if (dialog.exec() == QFileDialog::Accepted)
    {
        QString suffix = dialog.selectedFilter().split(".", QString::SkipEmptyParts, Qt::CaseInsensitive)[dialog.selectedFilter().split(".", QString::SkipEmptyParts, Qt::CaseInsensitive).count() - 1];
        if (suffix.count() > 1)
            suffix.remove(suffix.count() - 1, 1);
        dialog.setDefaultSuffix(suffix);
        ui->lineEdit_sourcefile->setText(dialog.selectedFiles()[0]);
    }
};
void ConvertDialog::browse_targetfile()
{
    //QFileDialog dialog(this, tr("Set Target File"), QDir::currentPath(), "Tex (*.tex);;JavaDoc (*.html *.htm);;any file (*.*)");
    QFileDialog dialog(this, tr("Set Target File"), "../html_examples", "Tex (*.tex);;JavaDoc (*.html *.htm);;any file (*.*)");
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() == QFileDialog::Accepted)
    {
        QString suffix = dialog.selectedFilter().split(".", QString::SkipEmptyParts, Qt::CaseInsensitive)[dialog.selectedFilter().split(".", QString::SkipEmptyParts, Qt::CaseInsensitive).count() - 1];
        if (suffix.count() > 1)
            suffix.remove(suffix.count() - 1, 1);
        dialog.setDefaultSuffix(suffix);
        ui->lineEdit_targetfile->setText(dialog.selectedFiles()[0]);
    }
};
QString ConvertDialog::getTargetFilePath()
{
    return ui->lineEdit_targetfile->text();
};
QString ConvertDialog::getSourceFilePath()
{
    return ui->lineEdit_sourcefile->text();
};
void ConvertDialog::convert()
{
    if (!ui->lineEdit_targetfile->text().isEmpty()
        & !ui->lineEdit_sourcefile->text().isEmpty())
        this->accept();
    else
    {
        QMessageBox msg(QMessageBox::Warning, tr("Error"), tr("You must select a source file and a target file."));
        msg.exec();
    }
};
