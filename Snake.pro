#-------------------------------------------------
#
# Project created by QtCreator 2013-08-18T18:17:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snake
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mygraphicview.cpp

HEADERS  += mainwindow.h \
    mygraphicview.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
