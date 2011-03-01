/********************************************************************************
** Form generated from reading UI file 'opendialog.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENDIALOG_H
#define UI_OPENDIALOG_H

#include <QtCore/QLocale>
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

class Ui_OpenDialog
{
public:
    QPushButton *pushButton_open;
    QGroupBox *groupBox_sourcefile;
    QLineEdit *lineEdit_sourcefile;
    QPushButton *pushButton_sourcefile;

    void setupUi(QDialog *OpenDialog)
    {
        if (OpenDialog->objectName().isEmpty())
            OpenDialog->setObjectName(QString::fromUtf8("OpenDialog"));
        OpenDialog->resize(389, 106);
        OpenDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        pushButton_open = new QPushButton(OpenDialog);
        pushButton_open->setObjectName(QString::fromUtf8("pushButton_open"));
        pushButton_open->setGeometry(QRect(310, 80, 75, 23));
        groupBox_sourcefile = new QGroupBox(OpenDialog);
        groupBox_sourcefile->setObjectName(QString::fromUtf8("groupBox_sourcefile"));
        groupBox_sourcefile->setGeometry(QRect(10, 10, 371, 61));
        lineEdit_sourcefile = new QLineEdit(groupBox_sourcefile);
        lineEdit_sourcefile->setObjectName(QString::fromUtf8("lineEdit_sourcefile"));
        lineEdit_sourcefile->setEnabled(false);
        lineEdit_sourcefile->setGeometry(QRect(10, 20, 261, 20));
        pushButton_sourcefile = new QPushButton(groupBox_sourcefile);
        pushButton_sourcefile->setObjectName(QString::fromUtf8("pushButton_sourcefile"));
        pushButton_sourcefile->setGeometry(QRect(280, 20, 75, 23));

        retranslateUi(OpenDialog);

        QMetaObject::connectSlotsByName(OpenDialog);
    } // setupUi

    void retranslateUi(QDialog *OpenDialog)
    {
        OpenDialog->setWindowTitle(QApplication::translate("OpenDialog", "Open", 0, QApplication::UnicodeUTF8));
        pushButton_open->setText(QApplication::translate("OpenDialog", "&Open", 0, QApplication::UnicodeUTF8));
        groupBox_sourcefile->setTitle(QApplication::translate("OpenDialog", "source file", 0, QApplication::UnicodeUTF8));
        pushButton_sourcefile->setText(QApplication::translate("OpenDialog", "&Browse", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OpenDialog: public Ui_OpenDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENDIALOG_H
