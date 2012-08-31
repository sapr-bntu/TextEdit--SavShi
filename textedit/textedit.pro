#-------------------------------------------------
#
# Project created by QtCreator 2011-12-05T23:41:19
#
#-------------------------------------------------
QT       += gui testlib


 TARGET          = textedit
CONFIG   += gui
CONFIG   -= app_bundle
 TEMPLATE        = app

 CONFIG          += qt warn_on

 HEADERS         = textedit.h
 SOURCES         = textedit.cpp \
                   main.cpp


 RESOURCES += textedit.qrc \
    textedit.qrc
 INCLUDEPATH += $(QTDIR)/src/gui/text
 QT           += xml
 LIBS += -lqaxcontainer
 build_all:!build_pass {
     CONFIG -= build_all
     CONFIG += release
 }

 # install
 target.path = $$[QT_INSTALL_DEMOS]/textedit
 sources.files = $$SOURCES $$HEADERS $$RESOURCES *.pro *.html *.doc images
 sources.path = $$[QT_INSTALL_DEMOS]/textedit
 INSTALLS += target sources

 symbian: include($$QT_SOURCE_TREE/demos/symbianpkgrules.pri)
