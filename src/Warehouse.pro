#-------------------------------------------------
#
# Project created by QtCreator 2019-07-16T20:26:00
#
#-------------------------------------------------

QT       += core gui widgets sql

TARGET = Warehouse
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11
DESTDIR = bin
OBJECTS_DIR = tmp/obj
MOC_DIR = tmp/moc
RCC_DIR = tmp/rcc
UI_DIR = tmp/ui

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        database.hpp \
        mainwindow.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    resources.qrc
