#-------------------------------------------------
#
# Project created by QtCreator 2017-06-17T21:29:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ajedrez
TEMPLATE = app


SOURCES += main.cpp\
        principal.cpp \
    matriz.cpp \
    abb.cpp \
    reportes.cpp

HEADERS  += principal.h \
    matriz.h \
    abb.h \
    reportes.h

FORMS    += principal.ui \
    reportes.ui
