QT += core
QT -= gui

CONFIG += c++11

TARGET = apertus_challenge
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    lodepng.cpp \
    debayer.cpp

HEADERS += \
    lodepng.h \
    debayer.h

DISTFILES += \
    portrait-gainx2-offset2047-20ms-02.raw12

RESOURCES += \
    myres.qrc
