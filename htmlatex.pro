# -------------------------------------------------
# Project created by QtCreator 2010-09-12T12:17:04
# -------------------------------------------------
QT += network \
    webkit \
    xml \
    xmlpatterns
TARGET = htmlatex
TEMPLATE = app
TRANSLATIONS = htmlatex_en.ts \
    htmlatex_de.ts
CODECFORTR = UTF-8

# CODECFORTR = ISO-8859-1
CONFIG += console
SOURCES += main.cpp \
    cnode.cpp \
    mainwindow.cpp \
    cmodel.cpp \
    cdocumentdata.cpp \
    citemdelegate.cpp \
    cconsole.cpp \
    cdocumentreader.cpp \
    ctranslationmapper.cpp \
    ctranslationdata.cpp \
    ctranslationdatanode.cpp \
    cconverter.cpp
HEADERS += cdocumentreader.h \
    cnode.h \
    mainwindow.h \
    ui_mainwindow.h \
    cmodel.h \
    cdocumentdata.h \
    citemdelegate.h \
    cconsole.h \
    ctranslationmapper.h \
    ctranslationdata.h \
    ctranslationdatanode.h \
    constants.h \
    cconverter.h
FORMS += mainwindow.ui
OTHER_FILES += README \
    html_examples/startseite.html \
    html_examples/kapitel_2.html \
    html_examples/kapitel_1.html \
    html_examples/html4.html \
    html_examples/kapitel/kapitel_3.html \
    html_examples/kapitel/kap01/kapitel_1.html \
    input_javadoc.xml \
    input_javadoc.xml \
    output_tex.xml
RESOURCES += resource.qrc
