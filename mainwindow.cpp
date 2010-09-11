#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->action_Convert->setText(tr("&Convert"));
    ui->action_Quit->setText(tr("&Quit"));
    connect(ui->action_Quit, SIGNAL(triggered()),
            this, SLOT(close()));
    connect(ui->action_Convert, SIGNAL(triggered()),
            this, SLOT(showConvertDialog()));
};
MainWindow::~MainWindow()
{
    delete ui;
};
void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
};
void MainWindow::showConvertDialog()
{
    ConvertDialog dialog;
    if (dialog.exec() == ConvertDialog::Accepted)
    {
        // dialog.exec() -> source file, target file and target definition file are set
        CDocumentReader* reader = new CDocumentReader;
        CNode* root = reader->read(dialog.getSourceFilePath());
        // now begin conversion...
    }
};
