#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"
#include "cconverter.h"

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
  @author Bjoern Kaiser
  */
void MainWindow::performInitialOperations(int argc, char* argv[])
{
    /* 0 = executable's name
       1 = source file path
       2 = source file type
       3 = input definition file path
       4 = target file path
       5 = target file type
       6 = output definition file path
       x = "-g" or "--gui"
    */
    if ((argc == 1) | (argc == 2))
        return;
    // one argument must be "-g" or "--gui"
    else if ((argc == 5)
        | (argc == 8))
    {
        // find and store the source file path, source file type, input difinition file,
        // target file path, target file type and output definition file in the
        // QStringList "arguments"
        QStringList arguments;
        for (int i = 1; i < argc; i++)
        {
            if (!QString(argv[i]).toLower().startsWith("-g")
                & !QString(argv[i]).toLower().startsWith("--gui"))
                arguments << QString(argv[i]);
        }
        QString sourcefilepath = arguments.at(0);
        QString filetypestring = arguments.at(1);
        // open source file
        QFile file(sourcefilepath);
        if (file.exists())
        {
            CDocumentData::FileType filetype = CDocumentData::Unknown;
            if (filetypestring.toLower() == "javadoc")
                filetype = CDocumentData::JavaDocHTML;
            QString inputdefinitionfilepath = arguments.at(2);
            translationMapper->createInputElementMap(inputdefinitionfilepath);
            CDocumentReader* reader = new CDocumentReader;
            reader->setTranslationMapper(translationMapper);
            CNode* root = reader->read(arguments.at(0), filetype);
            model->setRootNode(root);
            delete reader;
            if (root->count() == 0)
            {
                QMessageBox msg(QMessageBox::Warning,
                                tr("Error Reading Document"),
                                tr("The reading resulted in an empty document.\nMaybe an error occurred because of a wrong source file type:\n\n")
                                   + arguments.at(1),
                                QMessageBox::Ok,
                                this);
                msg.exec();
                if (DEBUG)
                {
                    std::cerr << "MainWindow::performInitialOperations: root.count() == 0: "
                            << "an empty document or an error occurred reading the document: file type: "
                            << arguments.at(1).toStdString() << std::endl;
                }
                return;
            }
        }
        else
        {
            QMessageBox msg(QMessageBox::Warning,
                            tr("I/O Error"),
                            tr("File doesn't exit:\n\n")
                            + arguments.at(0),
                            QMessageBox::Ok,
                            this);
            msg.exec();
            if (DEBUG)
            {
                std::cerr << "MainWindow::performInitialOperations: "
                        << "file.exits returned false: path: " << arguments.at(0).toStdString();
            }
            return;
        }
        if (argc == 8)
        {
            QString targetfilepath = arguments.at(3);
            filetypestring = arguments.at(4);
            QString outputdefinitionfilepath = arguments.at(5);
            translationMapper->createOutputElementMap(outputdefinitionfilepath);
            QFile file(targetfilepath);
            if (file.open(QFile::WriteOnly))
            {
                CDocumentData::FileType filetype = CDocumentData::Unknown;
                if (filetypestring.toLower() == "tex")
                    filetype = CDocumentData::Tex;
                // converting...
                CNode* root = model->root();
                CConverter* converter = new CConverter(targetfilepath,
                                                       root,
                                                       translationMapper);
                if (DEBUG)
                {
                    std::cerr << tr("conversion successfully performed").toStdString() << std::endl;
                }
                QMessageBox msg(QMessageBox::Information,
                                tr("Information"),
                                tr("Conversion successfully performed."),
                                QMessageBox::Ok,
                                this);
                msg.exec();
                delete converter;
            }
            else
            {
                QMessageBox msg(QMessageBox::Warning, tr("I/O Error"),
                                tr("can't write to file\n\n")
                                + arguments.at(2),
                                QMessageBox::Ok,
                                this);
                msg.exec();
                if(DEBUG)
                {
                    std::cerr << "MainWindow::performInitialOperations: "
                            << "file.open returned false\n\tPath: "
                            << arguments.at(2).toStdString() << std::endl;
                }
                return;
            }
        }
    }
    else
    {
        QMessageBox msg(QMessageBox::Warning,
                        tr("Error - argument list"),
                        tr("Unexpected number of arguments"),
                        QMessageBox::Ok,
                        this);
        msg.exec();
    }
};
void MainWindow::open()
{
    QFileDialog* dialog = new QFileDialog(this,
                                          tr("Set Source File"),
                                          "",
                                          "JavaDoc (*.html *.htm);;any file (*.*)");
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
        reader->setTranslationMapper(translationMapper);
        CNode* root = reader->read(dialog->selectedFiles().at(0), filetype);
        model->setRootNode(root);
        delete reader;
    }
    delete dialog;
};
void MainWindow::convert()
{
    QFileDialog* dialog = new QFileDialog(this,
                                          tr("Set Target File"),
                                          "",
                                          "Tex (*.tex);;JavaDoc (*.html *.htm);;any file (*.*)");
    dialog->setFileMode(QFileDialog::AnyFile);
    dialog->setAcceptMode(QFileDialog::AcceptSave);
    // retrieve target file path and type
    if (dialog->exec() == QFileDialog::Accepted)
    {
        // set suffix if no file suffix/extension is specified
        QString suffix = dialog->selectedFilter().split(".",
                                                        QString::SkipEmptyParts,
                                                        Qt::CaseInsensitive)[dialog->selectedFilter().split(".",
                                                                                                            QString::SkipEmptyParts,
                                                                                                            Qt::CaseInsensitive).count() - 1];
        if (suffix.count() > 1)
            suffix.remove(suffix.count() - 1, 1);
        dialog->setDefaultSuffix(suffix);
        if (DEBUG)
        {
            std::cerr << "MainWindow::convert()\n\tPath: "
                    << QString(dialog->selectedFiles().at(0)).toStdString() << std::endl;
        }
        // determine file type
        CDocumentData::FileType filetype = CDocumentData::Unknown;
        if (dialog->selectedFilter() == "JavaDoc (*.html *.htm)")
            filetype = CDocumentData::JavaDocHTML;
        if (dialog->selectedFilter() == "Tex (*.tex)")
            filetype = CDocumentData::Tex;
        else if (dialog->selectedFilter() == "any file (*.*)")
            filetype = CDocumentData::Unknown;
        CNode* root = model->root();
        // now begin conversion...
        CConverter* converter = new CConverter(dialog->selectedFiles().at(0),
                                               root, translationMapper);
        delete converter;
    }
};
void MainWindow::setInputDefinition()
{
    QString filepath = QFileDialog::getOpenFileName(0,
                                                    tr("Select Input Definition File"),
                                                    "",
                                                    tr("XML files (*.xml);;any file (*.*)"));
    translationMapper->createInputElementMap(filepath);
};
void MainWindow::setOutputDefinition()
{
    QString filepath = QFileDialog::getOpenFileName(0,
                                                    tr("Select Output Definition File"),
                                                    "",
                                                    tr("XML files (*.xml);;any file (*.*)"));
    translationMapper->createOutputElementMap(filepath);
};
