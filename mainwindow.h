#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ctranslationmapper.h"
#include "cdocumentreader.h"
#include "cmodel.h"
#include "citemdelegate.h"
#include "constants.h"
#include "cconverter.h"
#include <QMainWindow>
#include <QSplitter>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QTextEdit>

namespace Ui
{
    class MainWindow;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow* ui;
    QSplitter* splitter;
    QHBoxLayout* hBoxLayout;
    QTextEdit* textEdit;
    CModel* model;
    CItemDelegate* itemDelegate;
    CTranslationMapper* translationMapper;
    void performInitialOperations(QStringList arguments, QStringList options);
private slots:
    void open();
    void convert();
    void setInputDefinition();
    void setOutputDefinition();
    void about();
protected:
    void changeEvent(QEvent* e);
public:
    // constructor and destructor
    MainWindow(QStringList arguments, QStringList options, QWidget* parent);
    ~MainWindow();
};

#endif // MAINWINDOW_H
