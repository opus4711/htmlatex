#include "opendialog.h"
#include "ui_opendialog.h"

OpenDialog::OpenDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::OpenDialog)
{
    ui->setupUi(this);
    ui->pushButton_open->setText(tr("&Open"));
    ui->pushButton_sourcefile->setText(tr("&Browse"));
    this->setWindowTitle(tr("Open"));
    connect(ui->pushButton_open, SIGNAL(clicked()),
            this, SLOT(open()));
    connect(ui->pushButton_sourcefile, SIGNAL(clicked()),
            this, SLOT(browse_sourcefile()));
    dialog = new QFileDialog(this, tr("Set Source File"), "", "JavaDoc (*.html *.htm);;any file (*.*)");
};
OpenDialog::~OpenDialog()
{
    delete ui;
};
void OpenDialog::changeEvent(QEvent* e)
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
void OpenDialog::browse_sourcefile()
{
    if (dialog->exec() == QFileDialog::Accepted)
    {
        QString suffix = dialog->selectedFilter().split(".", QString::SkipEmptyParts, Qt::CaseInsensitive)[dialog->selectedFilter().split(".", QString::SkipEmptyParts, Qt::CaseInsensitive).count() - 1];
        if (suffix.count() > 1)
            suffix.remove(suffix.count() - 1, 1);
        dialog->setDefaultSuffix(suffix);
        ui->lineEdit_sourcefile->setText(dialog->selectedFiles()[0]);
    }
};
QString OpenDialog::sourceFilePath()
{
    return ui->lineEdit_sourcefile->text();
};
CDocumentData::FileType OpenDialog::fileType()
{
    // determine file type
    CDocumentData::FileType filetype = CDocumentData::Unknown;
    if (dialog->selectedFilter() == "JavaDoc (*.html *.htm)")
        filetype = CDocumentData::JavaDocHTML;
    else if (dialog->selectedFilter() == "any file (*.*)")
        filetype = CDocumentData::Unknown;
    return filetype;
};
void OpenDialog::open()
{
    if (!ui->lineEdit_sourcefile->text().isEmpty())
        this->accept();
    else
    {
        QMessageBox msg(QMessageBox::Warning, tr("Error"), tr("You must select a source file."));
        msg.exec();
    }
};
