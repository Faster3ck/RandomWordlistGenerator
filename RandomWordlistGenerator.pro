#-------------------------------------------------
#
# Project created by QtCreator 2013 - 2014-10-22T18:25:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = randomwordlistgenerator
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/wordgenerator.cpp \
    src/randomize.cpp \
    src/dialoginfo.cpp

HEADERS  += src/mainwindow.h \
    src/wordgenerator.h \
    src/randomize.h \
    src/dialoginfo.h

FORMS    += ui/mainwindow.ui \
    ui/dialoginfo.ui

RESOURCES += \
    res.qrc
