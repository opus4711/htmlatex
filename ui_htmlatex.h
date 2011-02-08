/********************************************************************************
** Form generated from reading UI file 'htmlatex.ui'
**
** Created: Tue 8. Feb 01:34:58 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HTMLATEX_H
#define UI_HTMLATEX_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_htmlatex
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *htmlatex)
    {
        if (htmlatex->objectName().isEmpty())
            htmlatex->setObjectName(QString::fromUtf8("htmlatex"));
        htmlatex->resize(600, 400);
        menuBar = new QMenuBar(htmlatex);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        htmlatex->setMenuBar(menuBar);
        mainToolBar = new QToolBar(htmlatex);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        htmlatex->addToolBar(mainToolBar);
        centralWidget = new QWidget(htmlatex);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        htmlatex->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(htmlatex);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        htmlatex->setStatusBar(statusBar);

        retranslateUi(htmlatex);

        QMetaObject::connectSlotsByName(htmlatex);
    } // setupUi

    void retranslateUi(QMainWindow *htmlatex)
    {
        htmlatex->setWindowTitle(QApplication::translate("htmlatex", "htmlatex", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class htmlatex: public Ui_htmlatex {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HTMLATEX_H
