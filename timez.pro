TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    timez.c

LIBS += -lrt

HEADERS += \
    timez.h
