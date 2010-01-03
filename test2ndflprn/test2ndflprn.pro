# -------------------------------------------------
# Project created by QtCreator 2009-12-14T09:37:39
# -------------------------------------------------
QT += testlib
QT += gui
TARGET = test2ndflprn
CONFIG += console
CONFIG -= app_bundle
CONFIG += static

LIBS += -lqaxcontainer
TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .
HEADERS += ../importer.h \
    ../exporter.h
SOURCES += main.cpp \
    ../importer.cpp \
    ../exporter.cpp
