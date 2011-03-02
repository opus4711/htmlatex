/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed 2. Mar 15:44:59 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTreeView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Quit;
    QAction *action_Convert;
    QAction *action_Open;
    QAction *actionSet_Replacement_Table;
    QAction *actionSet_Input_Definition;
    QAction *actionSet_O_utput_Definition;
    QWidget *centralwidget;
    QTreeView *treeView;
    QMenuBar *menubar;
    QMenu *menu_File;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        action_Quit = new QAction(MainWindow);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        action_Convert = new QAction(MainWindow);
        action_Convert->setObjectName(QString::fromUtf8("action_Convert"));
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QString::fromUtf8("action_Open"));
        actionSet_Replacement_Table = new QAction(MainWindow);
        actionSet_Replacement_Table->setObjectName(QString::fromUtf8("actionSet_Replacement_Table"));
        actionSet_Input_Definition = new QAction(MainWindow);
        actionSet_Input_Definition->setObjectName(QString::fromUtf8("actionSet_Input_Definition"));
        actionSet_O_utput_Definition = new QAction(MainWindow);
        actionSet_O_utput_Definition->setObjectName(QString::fromUtf8("actionSet_O_utput_Definition"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setGeometry(QRect(10, 10, 511, 531));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu_File->menuAction());
        menu_File->addAction(actionSet_Input_Definition);
        menu_File->addAction(actionSet_O_utput_Definition);
        menu_File->addSeparator();
        menu_File->addAction(action_Open);
        menu_File->addAction(action_Convert);
        menu_File->addSeparator();
        menu_File->addAction(action_Quit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "HTMLatex", 0, QApplication::UnicodeUTF8));
        action_Quit->setText(QApplication::translate("MainWindow", "&Quit", 0, QApplication::UnicodeUTF8));
        action_Convert->setText(QApplication::translate("MainWindow", "&Convert", 0, QApplication::UnicodeUTF8));
        action_Open->setText(QApplication::translate("MainWindow", "&Open", 0, QApplication::UnicodeUTF8));
        actionSet_Replacement_Table->setText(QApplication::translate("MainWindow", "Set &Replacement Table", 0, QApplication::UnicodeUTF8));
        actionSet_Input_Definition->setText(QApplication::translate("MainWindow", "Set &Input Definition", 0, QApplication::UnicodeUTF8));
        actionSet_O_utput_Definition->setText(QApplication::translate("MainWindow", "Set O&utput Definition", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
