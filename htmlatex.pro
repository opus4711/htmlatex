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
    mainwindow.cpp \
    settingsdialog.cpp \
    settings.cpp \
    documentreaderdata.cpp \
    console.cpp \
    converter.cpp \
    documentreader.cpp \
    documentdata.cpp \
    model.cpp \
    itemdelegate.cpp \
    translationmapper.cpp \
    translationdatanode.cpp \
    translationdata.cpp \
    node.cpp
HEADERS += mainwindow.h \
    settingsdialog.h \
    settings.h \
    documentreaderdata.h \
    console.h \
    converter.h \
    documentreader.h \
    documentdata.h \
    model.h \
    itemdelegate.h \
    translationmapper.h \
    translationdatanode.h \
    translationdata.h \
    node.h
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
