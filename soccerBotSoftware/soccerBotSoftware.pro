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
<<<<<<< Updated upstream \
    gamedata.cpp
    joystickhandler.cpp
=======
    gamesync.cpp
>>>>>>> Stashed changes

HEADERS  += mainwindow.h \
    client.h \
    host.h \
    udpsend.h \
<<<<<<< Updated upstream \
    gamedata.h
    joystickhandler.h
=======
    gamesync.h
>>>>>>> Stashed changes

FORMS    += mainwindow.ui

QT += network
win32: LIBS += -lXinput
