#-------------------------------------------------
#
# Project created by QtCreator 2014-07-09T14:54:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DES
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    des_c_dll.cpp

HEADERS  += mainwindow.h \
    des_c_dll.h

FORMS    += mainwindow.ui
