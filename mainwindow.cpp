#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(int argc, char* argv[], QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionSet_Input_Definition->setText(tr("Set &Input Definition"));
    ui->actionSet_O_utput_Definition->setText(tr("Set O&utput Definition"));
    ui->action_Open->setText(tr("&Open"));
    ui->action_Convert->setText(tr("&Convert"));
    ui->action_Quit->setText(tr("&Quit"));
    connect(ui->actionSet_Input_Definition, SIGNAL(triggered()),
            this, SLOT(setInputDefinition()));
    connect(ui->actionSet_O_utput_Definition, SIGNAL(triggered()),
            this, SLOT(setOutputDefinition()));
    connect(ui->action_Quit, SIGNAL(triggered()),
            this, SLOT(close()));
    connect(ui->action_Convert, SIGNAL(triggered()),
            this, SLOT(convert()));
    connect(ui->action_Open, SIGNAL(triggered()),
            this, SLOT(open()));
    model = new CModel(this);
    ui->treeView->setModel(model);
    itemDelegate = new CItemDelegate(model, this);
    ui->treeView->setItemDelegate(itemDelegate);
    splitter = new QSplitter;
    splitter->setOrientation(Qt::Horizontal);
    hBoxLayout = new QHBoxLayout;
    ui->centralwidget->setLayout(hBoxLayout);
    hBoxLayout->addWidget(splitter);
    splitter->addWidget(ui->treeView);
    //splitter->addWidget( zweiter rechter treeView );
    translationMapper = new CTranslationMapper;
    performInitialOperations(argc, argv);
};
MainWindow::~MainWindow()
{
    delete ui;
    delete translationMapper;
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
    if ((argc == 1) | (argc == 2))
        return;
    // the last argument must be "-g" or "--gui" except there are no arguments given at all
    else if ((argc == 4)
        | (argc == 6))
    {
        // find and store the source file path, source file type, target file
        // path and target file type in the QStringList "arguments"
        QStringList arguments;
        for (int i = 1; i < argc; i++)
        {
            if (!QString(argv[i]).toLower().startsWith("-g")
                & !QString(argv[i]).toLower().startsWith("--gui"))
                arguments << QString(argv[i]);
        }
        // open source file
        QFile file(arguments.at(0));
        if (file.exists())
        {
            CDocumentData::FileType filetype = CDocumentData::Unknown;
            if (arguments.at(1).toLower() == "javadoc")
                filetype = CDocumentData::JavaDocHTML;
            CDocumentReader* reader = new CDocumentReader;
            CNode* root = reader->read(arguments.at(0), filetype);
            model->setRootNode(root);
            delete reader;
            if (root->count() == 0)
            {
                QMessageBox msg(QMessageBox::Warning, tr("Error Reading Document"), tr("The reading resulted in an empty document.\nMaybe an error occurred because of a wrong source file type:\n\n") + arguments.at(1), QMessageBox::Ok, this);
                msg.exec();
                std::cerr << std::endl << "MainWindow::performInitialOperations: root.count() == 0: an empty document or an error occurred reading the document: file type: " << arguments.at(1).toStdString();
                return;
            }
        }
        else
        {
            QMessageBox msg(QMessageBox::Warning, tr("I/O Error"), tr("File doesn't exit:\n\n") + arguments.at(0), QMessageBox::Ok, this);
            msg.exec();
            std::cerr << std::endl << "MainWindow::performInitialOperations: file.exits returned false: path: " << arguments.at(0).toStdString();
            return;
        }
        if (argc == 6)
        {
            QFile file(arguments.at(2));
            if (file.open(QFile::WriteOnly))
            {
                CDocumentData::FileType filetype = CDocumentData::Unknown;
                if (arguments.at(3).toLower() == "tex")
                    filetype = CDocumentData::Tex;
                // converting...
                std::cerr << std::endl << tr("conversion successfully performed").toStdString() << std::endl;
                QMessageBox msg(QMessageBox::Information, tr("Information"), tr("Conversion successfully performed."), QMessageBox::Ok, this);
                msg.exec();
            }
            else
            {
                QMessageBox msg(QMessageBox::Warning, tr("I/O Error"), tr("can't write to file\n\n") + arguments.at(2), QMessageBox::Ok, this);
                msg.exec();
                std::cerr << std::endl << "MainWindow::performInitialOperations: file.open returned false: path: " << arguments.at(2).toStdString();
                return;
            }
        }
    }
    else
    {
        QMessageBox msg(QMessageBox::Warning, tr("Error - argument list"), tr("unexpected number of arguments"), QMessageBox::Ok, this);
        msg.exec();
    }
};
void MainWindow::open()
{
    QFileDialog* dialog = new QFileDialog(this, tr("Set Source File"), "", "JavaDoc (*.html *.htm);;any file (*.*)");
    // retrieve source file path and type
    if (dialog->exec() == QFileDialog::Accepted)
    {
        // determine file type
        CDocumentData::FileType filetype = CDocumentData::Unknown;
        if (dialog->selectedFilter() == "JavaDoc (*.html *.htm)")
            filetype = CDocumentData::JavaDocHTML;
        else if (dialog->selectedFilter() == "any file (*.*)")
            filetype = CDocumentData::Unknown;
        CDocumentReader* reader = new CDocumentReader;
        CNode* root = reader->read(dialog->selectedFiles().at(0), filetype);
        model->setRootNode(root);
        delete reader;
    }
    delete dialog;
};
void MainWindow::convert()
{
    QFileDialog* dialog = new QFileDialog(this, tr("Set Target File"), "", "Tex (*.tex);;JavaDoc (*.html *.htm);;any file (*.*)");
    dialog->setFileMode(QFileDialog::AnyFile);
    dialog->setAcceptMode(QFileDialog::AcceptSave);
    // retrieve target file path and type
    if (dialog->exec() == QFileDialog::Accepted)
    {
        // set suffix if no file suffix/extension is specified
        QString suffix = dialog->selectedFilter().split(".", QString::SkipEmptyParts, Qt::CaseInsensitive)[dialog->selectedFilter().split(".", QString::SkipEmptyParts, Qt::CaseInsensitive).count() - 1];
        if (suffix.count() > 1)
            suffix.remove(suffix.count() - 1, 1);
        dialog->setDefaultSuffix(suffix);
        std::cerr << std::endl << "MainWindow::convert(): path: " << QString(dialog->selectedFiles().at(0)).toStdString();
        // determine file type
        CDocumentData::FileType filetype = CDocumentData::Unknown;
        if (dialog->selectedFilter() == "JavaDoc (*.html *.htm)")
            filetype = CDocumentData::JavaDocHTML;
        if (dialog->selectedFilter() == "Tex (*.tex)")
            filetype = CDocumentData::Tex;
        else if (dialog->selectedFilter() == "any file (*.*)")
            filetype = CDocumentData::Unknown;
        //CNode* root = model->root();
        // now begin conversion...
    }
};
void MainWindow::setInputDefinition()
{
    QString filepath = QFileDialog::getOpenFileName(0, tr("Select Input Definition File"), "", tr("XML files (*.xml);;any file (*.*)"));
    translationMapper->createInputElementMap(filepath);
};
void MainWindow::setOutputDefinition()
{
    QString filepath = QFileDialog::getOpenFileName(0, tr("Select Output Definition File"), "", tr("XML files (*.xml);;any file (*.*)"));
    translationMapper->createOutputElementMap(filepath);
};
