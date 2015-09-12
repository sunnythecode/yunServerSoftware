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
<<<<<<< HEAD
    gamedata.cpp
=======
    gamedata.cpp \
    joystickhandler.cpp \
    gamesync.cpp
>>>>>>> master

HEADERS  += mainwindow.h \
    client.h \
    host.h \
    udpsend.h \
<<<<<<< HEAD
    gamedata.h
=======
    gamedata.h \
    joystickhandler.h \
    gamesync.h
>>>>>>> master

FORMS    += mainwindow.ui

QT += network
