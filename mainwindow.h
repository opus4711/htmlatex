#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "opendialog.h"
#include "convertdialog.h"
#include "cdocumentreader.h"
#include "cmodel.h"
#include "citemdelegate.h"
#include <QMainWindow>
#include <QSplitter>
#include <QHBoxLayout>

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
    CModel* model;
    CItemDelegate* itemDelegate;
    void performInitialOperations(int argc, char* argv[]);
private slots:
    void showOpenDialog();
    void showConvertDialog();
protected:
    void changeEvent(QEvent* e);
public:
    // constructor and destructor
    MainWindow(int argc, char* argv[], QWidget* parent);
    ~MainWindow();
};

#endif // MAINWINDOW_H
