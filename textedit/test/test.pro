#-------------------------------------------------
#
# Project created by QtCreator 2012-03-11T00:02:39
#
#-------------------------------------------------


QT       += gui testlib

TARGET = testtextedit
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += testtextedit.cpp \
    ../textedit.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

CONFIG       += qtestlib
TARGET  = ../TestLib

HEADERS += \
    ../textedit.h

RESOURCES +=
