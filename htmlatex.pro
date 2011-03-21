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
unix { 
    UI_DIR = .ui
    MOC_DIR = .moc
    OBJECTS_DIR = .obj
}
SOURCES += main.cpp \
    cnode.cpp \
    mainwindow.cpp \
    cmodel.cpp \
    cdocumentdata.cpp \
    citemdelegate.cpp \
    cdocumentreader.cpp \
    ctranslationmapper.cpp \
    ctranslationdata.cpp \
    ctranslationdatanode.cpp \
    cconverter.cpp \
    settingsdialog.cpp \
    settings.cpp \
    documentreaderdata.cpp \
    console.cpp
HEADERS += mainwindow.h \
    cdocumentreader.h \
    cnode.h \
    cmodel.h \
    cdocumentdata.h \
    citemdelegate.h \
    ctranslationmapper.h \
    ctranslationdata.h \
    ctranslationdatanode.h \
    cconverter.h \
    settingsdialog.h \
    settings.h \
    documentreaderdata.h \
    console.h
FORMS += mainwindow.ui \
    settingsdialog.ui
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
