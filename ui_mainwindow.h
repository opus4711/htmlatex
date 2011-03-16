/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue 15. Mar 22:10:33 2011
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
#include <QtGui/QToolBar>
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
    QAction *action_Info;
    QAction *action_Settings;
    QWidget *centralwidget;
    QTreeView *treeView;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menu_Help;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        action_Quit = new QAction(MainWindow);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Images/icons/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Quit->setIcon(icon);
        action_Convert = new QAction(MainWindow);
        action_Convert->setObjectName(QString::fromUtf8("action_Convert"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Images/icons/button_ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Convert->setIcon(icon1);
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QString::fromUtf8("action_Open"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Images/icons/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Open->setIcon(icon2);
        actionSet_Replacement_Table = new QAction(MainWindow);
        actionSet_Replacement_Table->setObjectName(QString::fromUtf8("actionSet_Replacement_Table"));
        actionSet_Input_Definition = new QAction(MainWindow);
        actionSet_Input_Definition->setObjectName(QString::fromUtf8("actionSet_Input_Definition"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Images/icons/compfile.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSet_Input_Definition->setIcon(icon3);
        actionSet_O_utput_Definition = new QAction(MainWindow);
        actionSet_O_utput_Definition->setObjectName(QString::fromUtf8("actionSet_O_utput_Definition"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Images/icons/compfile_up_arrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSet_O_utput_Definition->setIcon(icon4);
        action_Info = new QAction(MainWindow);
        action_Info->setObjectName(QString::fromUtf8("action_Info"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Images/icons/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Info->setIcon(icon5);
        action_Settings = new QAction(MainWindow);
        action_Settings->setObjectName(QString::fromUtf8("action_Settings"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Images/icons/misc.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Settings->setIcon(icon6);
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
        menu_Help = new QMenu(menubar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu_File->menuAction());
        menubar->addAction(menu_Help->menuAction());
        menu_File->addAction(actionSet_Input_Definition);
        menu_File->addAction(actionSet_O_utput_Definition);
        menu_File->addSeparator();
        menu_File->addAction(action_Open);
        menu_File->addAction(action_Convert);
        menu_File->addSeparator();
        menu_File->addAction(action_Settings);
        menu_File->addSeparator();
        menu_File->addAction(action_Quit);
        menu_Help->addAction(action_Info);
        toolBar->addAction(actionSet_O_utput_Definition);
        toolBar->addAction(actionSet_Input_Definition);
        toolBar->addAction(action_Open);
        toolBar->addAction(action_Convert);

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
        action_Info->setText(QApplication::translate("MainWindow", "&Info", 0, QApplication::UnicodeUTF8));
        action_Settings->setText(QApplication::translate("MainWindow", "&Settings", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
