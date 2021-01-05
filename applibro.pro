#-------------------------------------------------
#
# Project created by QtCreator 2018-02-08T20:06:16
#
#-------------------------------------------------

QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = applibro
TEMPLATE = app


SOURCES += main.cpp\
        iniciodialog.cpp \
    registrodialog.cpp \
    menuprincipal.cpp \
    usuario.cpp \
    libro.cpp \
    editar.cpp


HEADERS  += iniciodialog.h \
    registrodialog.h \
    menuprincipal.h \
    usuario.h \
    libro.h \
    editar.h


FORMS    += iniciodialog.ui \
    registrodialog.ui \
    menuprincipal.ui \
    editar.ui

RESOURCES += \
    res.qrc
