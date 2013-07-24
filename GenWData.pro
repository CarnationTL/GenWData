#-------------------------------------------------
#
# Project created by QtCreator 2013-07-24T10:26:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GenWData
TEMPLATE = app


SOURCES += main.cpp\
        mwgenwdata.cpp

HEADERS  += mwgenwdata.h

FORMS    += mwgenwdata.ui


CONFIG += qwt


unix:!macx: LIBS += -L$$PWD/../../../../usr/local/qwt-6.1.0-rc3/lib/ -lqwt

INCLUDEPATH += $$PWD/../../../../usr/local/qwt-6.1.0-rc3/include
DEPENDPATH += $$PWD/../../../../usr/local/qwt-6.1.0-rc3/include
