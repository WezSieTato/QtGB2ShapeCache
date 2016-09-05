#-------------------------------------------------
#
# Project created by QtCreator 2016-09-05T17:59:55
#
#-------------------------------------------------

QT       += core testlib

QT       -= gui

TARGET = tst_qtgb2shelpertests
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app

include(../qtgb2shapecache.pri)
include(../Box2D/box2d.pri)
include(../qtplist/qtplist.pri)

SOURCES += \
    tst_gb2shelpertests.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

DISTFILES +=
