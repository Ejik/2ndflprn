# -------------------------------------------------
# Project created by QtCreator 2009-12-14T09:08:22
# -------------------------------------------------
TARGET = 2ndflprn

# LIBS += -lqaxcontainer
# CONFIG += console
# CONFIG -= app_bundle
CONFIG += static
TEMPLATE = app
SOURCES += main.cpp \
    importer.cpp \
    exporter.cpp \
    processor.cpp \
    processorxml.cpp \
    processorlst.cpp \
    sprawmodel.cpp \
    tablemodel.cpp \

HEADERS += importer.h \
    exporter.h \
        app.rc \
    processor.h \
    processorxml.h \
    processorlst.h \
    sprawmodel.h \
    tablemodel.h \
    common.h

OTHER_FILES += README

RESOURCES += htmlres.qrc
RC_FILE = app.rc


