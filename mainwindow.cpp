#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(int argc, char* argv[], QWidget* parent) :
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
    performInitialOperations(argc, argv);
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
/** Performs opening and converting operations depending on application's startup
  * arguments.
  @author Björn Kaiser
  */
void MainWindow::performInitialOperations(int argc, char* argv[])
{
    /* 0 = executable's name
       1 = source file path
       2 = source file type
       3 = target file path
       4 = target file type
       5 = "-g" or "--gui"
    */
    if (argc == 1)
        return;
    // the last argument must be "-g" or "--gui" except there are no arguments given at all
    else if ((argc == 4)
        | (argc == 6))
    {
        QString sourcefilepath(argv[1]);
        QString filetypestring(argv[2]);
        QFile file(sourcefilepath);
        if (file.exists())
        {
            CDocumentData::FileType filetype = CDocumentData::Unknown;
            if (filetypestring.toLower() == "javadoc")
                filetype = CDocumentData::JavaDocHTML;
            CDocumentReader* reader = new CDocumentReader;
            CNode* root = reader->read(sourcefilepath, filetype);
            model->setRootNode(root);
            delete reader;
        }
        if (argc == 6)
        {
            QString targetfilepath(argv[3]);
            QString filetypestring(argv[4]);
            QFile file(targetfilepath);
            if (file.open(QFile::WriteOnly))
            {
                CDocumentData::FileType filetype = CDocumentData::Unknown;
                if (filetypestring.toLower() == "tex")
                    filetype = CDocumentData::Tex;
                // converting...
                QMessageBox msg(QMessageBox::Information, tr("Information"), tr("conversion successfully performed"), QMessageBox::Ok, this);
                msg.exec();
            }
            else
            {
                QMessageBox msg(QMessageBox::Warning, tr("I/O Error"), tr("can't write to file\n\n") + targetfilepath, QMessageBox::Ok, this);
                msg.exec();
            }
        }
    }
    else
    {
        QMessageBox msg(QMessageBox::Warning, tr("Error - argument list"), tr("unexpected number of arguments"), QMessageBox::Ok, this);
        msg.exec();
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
        delete reader;
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
