#-------------------------------------------------
#
# Project created by QtCreator 2012-05-18T08:46:59
#
#-------------------------------------------------

QT       += testlib

TARGET = tst_test2test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_test2test.cpp \
    ../textedit.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../textedit.h
