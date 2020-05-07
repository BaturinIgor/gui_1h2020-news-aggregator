#-------------------------------------------------
#
# Project created by QtCreator 2020-04-17T12:27:51
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += xml

TARGET = GUI_Project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    information.cpp

HEADERS  += mainwindow.h \
    information.h

FORMS    += mainwindow.ui
