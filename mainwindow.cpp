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
            this, SLOT(_setInputDefinition()));
    connect(ui->actionSet_O_utput_Definition, SIGNAL(triggered()),
            this, SLOT(_setOutputDefinition()));
    connect(ui->action_Quit, SIGNAL(triggered()),
            this, SLOT(close()));
    connect(ui->action_Convert, SIGNAL(triggered()),
            this, SLOT(_convert()));
    connect(ui->action_Open, SIGNAL(triggered()),
            this, SLOT(_open()));
    connect(ui->action_Save_As, SIGNAL(triggered()),
            this, SLOT(_saveAs()));
    connect(ui->action_Info, SIGNAL(triggered()),
            this, SLOT(_about()));
    connect(ui->action_Settings, SIGNAL(triggered()),
            this, SLOT(_showSettings()));
    _model = new Model(this);
    ui->treeView->setModel(_model);
    _itemDelegate = new ItemDelegate(_model, this);
    ui->treeView->setItemDelegate(_itemDelegate);
    _translationMapper = new TranslationMapper;
    _converter = new Converter(this, _translationMapper);
    connect(_converter, SIGNAL(updateTextEdit(QString)),
            ui->textEdit, SLOT(setPlainText(QString)));
    connect(_converter, SIGNAL(updateProgressBar(int)),
            this, SLOT(_updateProgressBar(int)));
    ui->statusbar->addPermanentWidget(ui->progressBar, 1);
    _settingsDialog = new SettingsDialog(this);
    connect(_settingsDialog, SIGNAL(languageChanged(QLocale::Country)),
            this, SLOT(_languageChanged(QLocale::Country)));
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(_showTreeViewContextMenu(QPoint)));
    // create menu items for the _treeView's context menu
    QAction *action_Remove_Node = new QAction("Remove", ui->treeView);
    action_Remove_Node->setShortcut(QKeySequence::Delete);
    connect(action_Remove_Node, SIGNAL(triggered()),
            this, SLOT(_treeViewRemoveNode()));
    ui->treeView->addAction(action_Remove_Node);
    // set translation for the application's text
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    Settings settings;
    QLocale::Country language = (QLocale::Country)settings.getValue("language").toInt();
    _languageChanged(language);
    _performInitialOperations(arguments, options);
};
MainWindow::~MainWindow()
{
    delete ui;
    delete _translationMapper;
    delete _converter;
};
void MainWindow::_performInitialOperations(QStringList arguments, QStringList options)
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
            DocumentData::FileType filetype = DocumentData::Unknown;
            if (filetypestring.toLower() == "javadoc")
                filetype = DocumentData::JavaDocHTML;
            QString inputdefinitionfilepath(arguments.at(2));
                _translationMapper->createDocumentReaderData(inputdefinitionfilepath);
            DocumentReader* reader = new DocumentReader(_translationMapper);
            Node* root = reader->read(arguments.at(0), filetype);
                _model->setRootNode(root);
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
                if (Settings::DEBUG)
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
            if (Settings::DEBUG)
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
            _translationMapper->createOutputElementMap(outputdefinitionfilepath);
            QFile file(targetfilepath);
            if (file.open(QFile::WriteOnly))
            {
                DocumentData::FileType filetype = DocumentData::Unknown;
                if (filetypestring.toLower() == "tex")
                    filetype = DocumentData::Tex;
                // converting...
                Node* root = new Node(*_model->root());
                _converter->convert(targetfilepath, root);
                if (Settings::DEBUG)
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
                if(Settings::DEBUG)
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
void MainWindow::_languageChanged(QLocale::Country language)
{
    // set translation environment for the application texts
    if (language == QLocale::Germany)
        _translator.load(QString("htmlatex_de.qm"));
    else
        _translator.load(QString("htmlatex_en.qm"));
    qApp->installTranslator(&_translator);
    ui->retranslateUi(this);
    _settingsDialog->retranslateUi();
};
void MainWindow::_open()
{
    QFileDialog* dialog = new QFileDialog(this,
                                          tr("Set Source File"),
                                          "",
                                          "JavaDoc (*.html *.htm);;any file (*.*)");
    // retrieve source file path and type
    if (dialog->exec() == QFileDialog::Accepted)
    {
        // determine file type
        DocumentData::FileType filetype = DocumentData::Unknown;
        if (dialog->selectedFilter() == "JavaDoc (*.html *.htm)")
            filetype = DocumentData::JavaDocHTML;
        else if (dialog->selectedFilter() == "any file (*.*)")
            filetype = DocumentData::Unknown;
        DocumentReader* reader = new DocumentReader(_translationMapper);
        Node *root = reader->read(dialog->selectedFiles().at(0), filetype);
        _model->setRootNode(root);
        delete reader;
    }
    delete dialog;
};
void MainWindow::_convert()
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
        if(Settings::DEBUG)
        {
            std::cerr << "MainWindow::convert()\n\tPath: "
                    << QString(dialog->selectedFiles().at(0)).toStdString() << std::endl;
        }
        // determine file type
        DocumentData::FileType filetype = DocumentData::Unknown;
        if (dialog->selectedFilter() == "JavaDoc (*.html *.htm)")
            filetype = DocumentData::JavaDocHTML;
        if (dialog->selectedFilter() == "Tex (*.tex)")
            filetype = DocumentData::Tex;
        else if (dialog->selectedFilter() == "any file (*.*)")
            filetype = DocumentData::Unknown;
        // now begin conversion...
        Node* root = new Node(*_model->root());
        _converter->convert(dialog->selectedFiles().at(0), root);
    }
};
void MainWindow::_saveAs()
{
};
void MainWindow::_setInputDefinition()
{
    QString filepath = QFileDialog::getOpenFileName(0,
                                                    tr("Select Input Definition File"),
                                                    "",
                                                    tr("XML files (*.xml);;any file (*.*)"));
    _translationMapper->createDocumentReaderData(filepath);
};
void MainWindow::_setOutputDefinition()
{
    QString filepath = QFileDialog::getOpenFileName(0,
                                                    tr("Select Output Definition File"),
                                                    "",
                                                    tr("XML files (*.xml);;any file (*.*)"));
    _translationMapper->createOutputElementMap(filepath);
};
void MainWindow::_showSettings()
{
    _settingsDialog->exec();
};
void MainWindow::_about()
{
    QMessageBox::about(this, tr("About htmLaTeX"),
                       tr("htmLaTeX 0.1\nA converter for JavaDoc-generated HTML to LaTeX"
                          "(c) 2011 Björn (Kaiser|Baß)"));
};
void MainWindow::_showTreeViewContextMenu(QPoint point)
{
    Node* node = _model->nodeFromIndex(ui->treeView->currentIndex());
    if (node != 0)
    {
        QMenu menu;
        menu.addActions(ui->treeView->actions());
        menu.exec(QCursor::pos());
    }
};
void MainWindow::_treeViewRemoveNode()
{
    Node* node = _model->nodeFromIndex(ui->treeView->currentIndex());
    if (node != 0)
    {
        int depth = node->getLayer();
        if (node->getParent() != 0)
            node->getParent()->removeChild(node);
        _model->refresh();
        ui->treeView->expandToDepth(depth);
    }
};
void MainWindow::_updateProgressBar(int percentage)
{
    ui->progressBar->setValue(percentage);
};
