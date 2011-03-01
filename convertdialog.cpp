#include "convertdialog.h"
#include "ui_convertdialog.h"

ConvertDialog::ConvertDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConvertDialog)
{
    ui->setupUi(this);
    ui->pushButton_convert->setText(tr("&Convert"));
    ui->pushButton_targetfile->setText(tr("&Browse"));
    this->setWindowTitle(tr("Convert"));
    connect(ui->pushButton_convert, SIGNAL(clicked()),
            this, SLOT(convert()));
    connect(ui->pushButton_targetfile, SIGNAL(clicked()),
            this, SLOT(browse_targetfile()));
    dialog = new QFileDialog(this, tr("Set Target File"), "", "Tex (*.tex);;JavaDoc (*.html *.htm);;any file (*.*)");
    dialog->setFileMode(QFileDialog::AnyFile);
    dialog->setAcceptMode(QFileDialog::AcceptSave);
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
void ConvertDialog::browse_targetfile()
{
    if (dialog->exec() == QFileDialog::Accepted)
    {
        QString suffix = dialog->selectedFilter().split(".", QString::SkipEmptyParts, Qt::CaseInsensitive)[dialog->selectedFilter().split(".", QString::SkipEmptyParts, Qt::CaseInsensitive).count() - 1];
        if (suffix.count() > 1)
            suffix.remove(suffix.count() - 1, 1);
        dialog->setDefaultSuffix(suffix);
        ui->lineEdit_targetfile->setText(dialog->selectedFiles()[0]);
    }
};
QString ConvertDialog::targetFilePath()
{
    return ui->lineEdit_targetfile->text();
};
CDocumentData::FileType ConvertDialog::fileType()
{
    // determine file type
    CDocumentData::FileType filetype = CDocumentData::Unknown;
    if (dialog->selectedFilter() == "JavaDoc (*.html *.htm)")
        filetype = CDocumentData::JavaDocHTML;
    if (dialog->selectedFilter() == "Tex (*.tex)")
        filetype = CDocumentData::Tex;
    else if (dialog->selectedFilter() == "any file (*.*)")
        filetype = CDocumentData::Unknown;
    return filetype;
};
void ConvertDialog::convert()
{
    if (!ui->lineEdit_targetfile->text().isEmpty())
        this->accept();
    else
    {
        QMessageBox msg(QMessageBox::Warning, tr("Error"), tr("You must select a target file."));
        msg.exec();
    }
};
