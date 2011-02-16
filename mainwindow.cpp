#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->action_Open->setText(tr("&Open"));
    ui->action_Convert->setText(tr("&Convert"));
    ui->action_Quit->setText(tr("&Quit"));
    connect(ui->action_Quit, SIGNAL(triggered()),
            this, SLOT(close()));
    connect(ui->action_Convert, SIGNAL(triggered()),
            this, SLOT(showConvertDialog()));
    connect(ui->action_Open, SIGNAL(triggered()),
            this, SLOT(showOpenDialog()));
    model = new CModel(this);
    ui->treeView->setModel(model);
    itemDelegate = new CItemDelegate(model, this);
    ui->treeView->setItemDelegate(itemDelegate);
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
void MainWindow::showOpenDialog()
{
    OpenDialog dialog;
    // retrieve source file path and type
    if (dialog.exec() == OpenDialog::Accepted)
    {
        CDocumentReader* reader = new CDocumentReader;
        CNode* root = reader->read(dialog.sourceFilePath(), dialog.fileType());
        model->setRootNode(root);
    }
};
void MainWindow::showConvertDialog()
{
    ConvertDialog dialog;
    // retrieve target file path and type
    if (dialog.exec() == ConvertDialog::Accepted)
    {
        //CNode* root = model->root();
        // now begin conversion...
    }
};
