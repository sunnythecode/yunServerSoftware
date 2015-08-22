#-------------------------------------------------
#
# Project created by QtCreator 2015-08-21T09:43:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = soccerBotSoftware
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        broadcast.cpp \
    client.cpp

HEADERS  += mainwindow.h \
    broadcast.h \
    client.h

FORMS    += mainwindow.ui

QT += network
