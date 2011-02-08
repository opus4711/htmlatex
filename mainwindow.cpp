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
    model = new CModel(this);
    ui->treeView->setModel(model);
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
    // retrieve source and target file path
    if (dialog.exec() == ConvertDialog::Accepted)
    {
        CDocumentReader* reader = new CDocumentReader(dialog.getSourceFilePath());
        CNode* root = reader->read();
        model->setRootNode(root);
        // now begin conversion...
    }
};
