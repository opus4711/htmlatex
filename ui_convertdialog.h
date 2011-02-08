/********************************************************************************
** Form generated from reading UI file 'convertdialog.ui'
**
** Created: Tue 8. Feb 01:34:58 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONVERTDIALOG_H
#define UI_CONVERTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ConvertDialog
{
public:
    QGroupBox *groupBox_targetfile;
    QLineEdit *lineEdit_targetfile;
    QPushButton *pushButton_targetfile;
    QPushButton *pushButton_convert;
    QGroupBox *groupBox_sourcefile;
    QLineEdit *lineEdit_sourcefile;
    QPushButton *pushButton_sourcefile;

    void setupUi(QDialog *ConvertDialog)
    {
        if (ConvertDialog->objectName().isEmpty())
            ConvertDialog->setObjectName(QString::fromUtf8("ConvertDialog"));
        ConvertDialog->resize(389, 177);
        groupBox_targetfile = new QGroupBox(ConvertDialog);
        groupBox_targetfile->setObjectName(QString::fromUtf8("groupBox_targetfile"));
        groupBox_targetfile->setGeometry(QRect(10, 80, 371, 61));
        lineEdit_targetfile = new QLineEdit(groupBox_targetfile);
        lineEdit_targetfile->setObjectName(QString::fromUtf8("lineEdit_targetfile"));
        lineEdit_targetfile->setEnabled(false);
        lineEdit_targetfile->setGeometry(QRect(10, 20, 261, 20));
        pushButton_targetfile = new QPushButton(groupBox_targetfile);
        pushButton_targetfile->setObjectName(QString::fromUtf8("pushButton_targetfile"));
        pushButton_targetfile->setGeometry(QRect(280, 20, 75, 23));
        pushButton_convert = new QPushButton(ConvertDialog);
        pushButton_convert->setObjectName(QString::fromUtf8("pushButton_convert"));
        pushButton_convert->setGeometry(QRect(310, 150, 75, 23));
        groupBox_sourcefile = new QGroupBox(ConvertDialog);
        groupBox_sourcefile->setObjectName(QString::fromUtf8("groupBox_sourcefile"));
        groupBox_sourcefile->setGeometry(QRect(10, 10, 371, 61));
        lineEdit_sourcefile = new QLineEdit(groupBox_sourcefile);
        lineEdit_sourcefile->setObjectName(QString::fromUtf8("lineEdit_sourcefile"));
        lineEdit_sourcefile->setEnabled(false);
        lineEdit_sourcefile->setGeometry(QRect(10, 20, 261, 20));
        pushButton_sourcefile = new QPushButton(groupBox_sourcefile);
        pushButton_sourcefile->setObjectName(QString::fromUtf8("pushButton_sourcefile"));
        pushButton_sourcefile->setGeometry(QRect(280, 20, 75, 23));

        retranslateUi(ConvertDialog);

        QMetaObject::connectSlotsByName(ConvertDialog);
    } // setupUi

    void retranslateUi(QDialog *ConvertDialog)
    {
        ConvertDialog->setWindowTitle(QApplication::translate("ConvertDialog", "Convert", 0, QApplication::UnicodeUTF8));
        groupBox_targetfile->setTitle(QApplication::translate("ConvertDialog", "target file", 0, QApplication::UnicodeUTF8));
        pushButton_targetfile->setText(QApplication::translate("ConvertDialog", "Browse", 0, QApplication::UnicodeUTF8));
        pushButton_convert->setText(QApplication::translate("ConvertDialog", "Convert", 0, QApplication::UnicodeUTF8));
        groupBox_sourcefile->setTitle(QApplication::translate("ConvertDialog", "source file", 0, QApplication::UnicodeUTF8));
        pushButton_sourcefile->setText(QApplication::translate("ConvertDialog", "Browse", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConvertDialog: public Ui_ConvertDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONVERTDIALOG_H
