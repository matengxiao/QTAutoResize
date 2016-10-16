#-------------------------------------------------
#
# Project created by QtCreator 2016-10-16T00:02:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AutoResizeDemo
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
        widget.cpp \
    AutoResize.cpp

HEADERS  += widget.h \
    AutoResize.h

FORMS    += widget.ui
