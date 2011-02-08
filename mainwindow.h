#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "convertdialog.h"
#include "cdocumentreader.h"
#include "cmodel.h"
#include <QMainWindow>

namespace Ui
{
    class MainWindow;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow* ui;
    CModel* model;
private slots:
    void showConvertDialog();
protected:
    void changeEvent(QEvent *e);
public:
    // constructor and destructor
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
