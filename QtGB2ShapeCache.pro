QT += core
QT -= gui

CONFIG += c++11

TARGET = QtGB2ShapeCache
CONFIG += console
CONFIG -= app_bundle

include(Box2D/box2d.pri)
include(qtplist/qtplist.pri)

TEMPLATE = app

SOURCES += main.cpp \
    gb2helper.cpp \
    gb2shapecache.cpp

HEADERS += \
    gb2helper.h \
    gb2shapecache.h
