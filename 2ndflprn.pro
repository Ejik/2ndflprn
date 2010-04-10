# -------------------------------------------------
# Project created by QtCreator 2009-12-14T09:08:22
# -------------------------------------------------
TARGET = 2ndflprn
#LIBS += -lqaxcontainer

# CONFIG += console
# CONFIG -= app_bundle
CONFIG += static
TEMPLATE = app
SOURCES += main.cpp \
    importer.cpp \
    exporter.cpp
HEADERS += importer.h \
    exporter.h
OTHER_FILES += README.txt \
    res/sec1.txt
RESOURCES += htmlres.qrc
