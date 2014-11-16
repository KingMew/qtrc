#-------------------------------------------------
#
# Project created by QtCreator 2014-02-02T10:45:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtrc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    controller_window.cpp

HEADERS  += mainwindow.h \
    controller_window.h \
    global.h

FORMS    += mainwindow.ui \
    controller_window.ui

RESOURCES += \
    picz.qrc
