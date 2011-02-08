#ifndef OPENDIALOG_H
#define OPENDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui
{
    class OpenDialog;
};
class OpenDialog : public QDialog {
    Q_OBJECT
private:
    Ui::OpenDialog* ui;
    QFileDialog* dialog;
protected:
    void changeEvent(QEvent* e);
private slots:
    void browse_sourcefile();
    void open();
public:
    QString sourceFilePath();
    QString fileFilter();
    // constructor and destructor
    OpenDialog(QWidget* parent = 0);
    ~OpenDialog();
};

#endif // OPENDIALOG_H
