#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QStringList arguments,
                       QStringList options,
                       QWidget* parent)
                           : QMainWindow(parent),
                           ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    connect(ui->action_Info, SIGNAL(triggered()),
            this, SLOT(about()));
    connect(ui->action_Settings, SIGNAL(triggered()),
            this, SLOT(showSettings()));
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
    textEdit = new QTextEdit;
    //QString str("quark mit soße und übermäßig reiz");
    //textEdit->setText(str);
    splitter->addWidget(textEdit);
    translationMapper = new CTranslationMapper;
    converter = new CConverter(this, translationMapper);
    connect(converter, SIGNAL(updateTextEdit(QString)),
            textEdit, SLOT(setPlainText(QString)));
    _settingsDialog = new SettingsDialog(this);
    connect(_settingsDialog, SIGNAL(languageChanged(QLocale::Country)),
            this, SLOT(languageChanged(QLocale::Country)));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    Settings settings;
    QLocale::Country language = (QLocale::Country)settings.getValue("language").toInt();
    this->languageChanged(language);
    performInitialOperations(arguments, options);
};
MainWindow::~MainWindow()
{
    delete ui;
    delete translationMapper;
    delete converter;
};
/** Performs opening and converting operations depending on application's startup
  * arguments.
  @author Bjoern Kaiser
  */
void MainWindow::performInitialOperations(QStringList arguments, QStringList options)
{
    /* arguments:
       0 = source file path
       1 = source file type
       2 = input definition file path
       3 = target file path
       4 = target file type
       5 = output definition file path
    */
    if ((arguments.count() == 0) | (arguments.count() == 1))
        return;
    // one argument must be "-g" or "--gui"
    else if ((arguments.count() == 4)
        | (arguments.count() == 6))
    {
        // find and store the source file path, source file type, input difinition file,
        // target file path, target file type and output definition file
        QString sourcefilepath(arguments.at(0));
        QString filetypestring(arguments.at(1));
        // open source file
        QFile file(sourcefilepath);
        if (file.exists())
        {
            CDocumentData::FileType filetype = CDocumentData::Unknown;
            if (filetypestring.toLower() == "javadoc")
                filetype = CDocumentData::JavaDocHTML;
            QString inputdefinitionfilepath(arguments.at(2));
            translationMapper->createInputElementMap(inputdefinitionfilepath);
            CDocumentReader* reader = new CDocumentReader;
            reader->setTranslationMapper(translationMapper);
            CNode* root = reader->read(arguments.at(0), filetype);
            model->setRootNode(root);
            delete reader;
            if (root->getCount() == 0)
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
        if (arguments.count() == 6)
        {
            QString targetfilepath(arguments.at(3));
            filetypestring = arguments.at(4);
            QString outputdefinitionfilepath(arguments.at(5));
            translationMapper->createOutputElementMap(outputdefinitionfilepath);
            QFile file(targetfilepath);
            if (file.open(QFile::WriteOnly))
            {
                CDocumentData::FileType filetype = CDocumentData::Unknown;
                if (filetypestring.toLower() == "tex")
                    filetype = CDocumentData::Tex;
                // converting...
                CNode* root = new CNode(*model->root());
                converter->convert(targetfilepath, root);
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
void MainWindow::languageChanged(QLocale::Country language)
{
    // Set translation environment for the application texts
    if (language == QLocale::Germany)
        _translator.load(QString("htmlatex_de.qm"));
    else
        _translator.load(QString("htmlatex_en.qm"));
    qApp->installTranslator(&_translator);
    ui->retranslateUi(this);
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
        CNode *root = reader->read(dialog->selectedFiles().at(0), filetype);
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
        if(DEBUG)
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
        // now begin conversion...
        CNode* root = new CNode(*model->root());
        converter->convert(dialog->selectedFiles().at(0), root);
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
void MainWindow::about()
{
    QMessageBox::about(this, tr("About htmLaTeX"),
                       tr("htmLaTeX 0.1\nA converter for JavaDoc-generated HTML to LaTeX"
                          "(c) 2011 Björn (Kaiser|Baß)"));
};
void MainWindow::showSettings()
{
    _settingsDialog->exec();
};
