QT += core
QT -= gui

CONFIG += c++11

TARGET = QtGB2ShapeCache
CONFIG += console
CONFIG -= app_bundle

include(Box2D/box2d.pri)

TEMPLATE = app

SOURCES += main.cpp \
    qtgb2helper.cpp \
    qtgb2shapecache.cpp

HEADERS += \
    qtgb2helper.h \
    qtgb2shapecache.h
