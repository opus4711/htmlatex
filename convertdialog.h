#ifndef CONVERTDIALOG_H
#define CONVERTDIALOG_H

#include "cdocumentdata.h"
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui
{
    class ConvertDialog;
};
class ConvertDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::ConvertDialog* ui;
    QFileDialog* dialog;
protected:
    void changeEvent(QEvent* e);
private slots:
    void browse_targetfile();
    void convert();
public:
    QString targetFilePath();
    CDocumentData::FileType fileType();
    // constructor and destructor
    ConvertDialog(QWidget *parent = 0);
    ~ConvertDialog();
};

#endif // CONVERTDIALOG_H
