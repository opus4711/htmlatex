# -------------------------------------------------
# Project created by QtCreator 2010-09-12T12:17:04
# -------------------------------------------------
QT += network \
    webkit \
    xml \
    xmlpatterns
TARGET = htmlatex
TEMPLATE = app
CONFIG += console
SOURCES += main.cpp \
    cdocumentreader.cpp \
    cnode.cpp \
    convertdialog.cpp \
    mainwindow.cpp \
    cmodel.cpp \
    opendialog.cpp \
    cdocumentdata.cpp \
    citemdelegate.cpp \
    cconsole.cpp
HEADERS += cdocumentreader.h \
    cnode.h \
    convertdialog.h \
    mainwindow.h \
    ui_convertdialog.h \
    ui_mainwindow.h \
    cmodel.h \
    opendialog.h \
    cdocumentdata.h \
    citemdelegate.h \
    cconsole.h
FORMS += convertdialog.ui \
    mainwindow.ui \
    opendialog.ui
OTHER_FILES += README \
    html_examples/startseite.html \
    html_examples/kapitel_2.html \
    html_examples/kapitel_1.html \
    html_examples/html4.html \
    html_examples/kapitel/kapitel_3.html \
    html_examples/kapitel/kap01/kapitel_1.html \
    input_javadoc.xml \
    input_javadoc.xml
