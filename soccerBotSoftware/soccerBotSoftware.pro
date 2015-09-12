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
    client.cpp \
    host.cpp \
    udpsend.cpp \
    gamedata.cpp \
    joystickhandler.cpp

HEADERS  += mainwindow.h \
    client.h \
    host.h \
    udpsend.h \
    gamedata.h \
    joystickhandler.h

FORMS    += mainwindow.ui

QT += network
