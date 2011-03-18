/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created: Fri 18. Mar 13:31:30 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QGroupBox *groupBox_latexpath;
    QLineEdit *lineEdit_latexpath;
    QPushButton *pushButton_latexpath;
    QGroupBox *groupBox_language;
    QComboBox *comboBox_language;
    QPushButton *pushButton_apply;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QString::fromUtf8("SettingsDialog"));
        SettingsDialog->resize(400, 188);
        SettingsDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        groupBox_latexpath = new QGroupBox(SettingsDialog);
        groupBox_latexpath->setObjectName(QString::fromUtf8("groupBox_latexpath"));
        groupBox_latexpath->setGeometry(QRect(10, 10, 381, 81));
        lineEdit_latexpath = new QLineEdit(groupBox_latexpath);
        lineEdit_latexpath->setObjectName(QString::fromUtf8("lineEdit_latexpath"));
        lineEdit_latexpath->setGeometry(QRect(20, 20, 341, 20));
        pushButton_latexpath = new QPushButton(groupBox_latexpath);
        pushButton_latexpath->setObjectName(QString::fromUtf8("pushButton_latexpath"));
        pushButton_latexpath->setGeometry(QRect(20, 50, 75, 23));
        groupBox_language = new QGroupBox(SettingsDialog);
        groupBox_language->setObjectName(QString::fromUtf8("groupBox_language"));
        groupBox_language->setGeometry(QRect(10, 110, 161, 71));
        groupBox_language->setCheckable(false);
        comboBox_language = new QComboBox(groupBox_language);
        comboBox_language->setObjectName(QString::fromUtf8("comboBox_language"));
        comboBox_language->setGeometry(QRect(20, 30, 121, 22));
        pushButton_apply = new QPushButton(SettingsDialog);
        pushButton_apply->setObjectName(QString::fromUtf8("pushButton_apply"));
        pushButton_apply->setGeometry(QRect(320, 160, 75, 23));

        retranslateUi(SettingsDialog);

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "Settings", 0, QApplication::UnicodeUTF8));
        groupBox_latexpath->setTitle(QApplication::translate("SettingsDialog", "path to latex.exe", 0, QApplication::UnicodeUTF8));
        pushButton_latexpath->setText(QApplication::translate("SettingsDialog", "&Browse", 0, QApplication::UnicodeUTF8));
        groupBox_language->setTitle(QApplication::translate("SettingsDialog", "Language", 0, QApplication::UnicodeUTF8));
        pushButton_apply->setText(QApplication::translate("SettingsDialog", "&Apply", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
