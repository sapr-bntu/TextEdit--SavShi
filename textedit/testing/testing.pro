#-------------------------------------------------
#
# Project created by QtCreator 2012-05-18T08:14:52
#
#-------------------------------------------------

QT       +=gui testlib

TARGET  = ../TestLib

CONFIG   += console
CONFIG   -= app_bundle

CONFIG += QwtDll


TEMPLATE = app


SOURCES += tst_testingtest.cpp\
    ../textedit.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
HEADERS += \
    ../textedit.h

RESOURCES +=


