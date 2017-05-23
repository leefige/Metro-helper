#-------------------------------------------------
#
# Project created by QtCreator 2017-03-29T00:13:14
#
#-------------------------------------------------


QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = metro
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    kernel.cpp \
    drawpad.cpp \
    NetworkFlow.cpp \
    Point.cpp \
    Line.cpp

HEADERS  += mainwindow.h \
    kernel.h \
    drawpad.h \
    NetworkFlow.h \
    Point.h \
    Line.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    rsc.qrc
