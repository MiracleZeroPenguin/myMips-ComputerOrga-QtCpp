#-------------------------------------------------
#
# Project created by QtCreator 2020-05-03T23:25:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = newMips
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        asmdemo.cpp \
        assembler.cpp \
        copyright.cpp \
        disassembler.cpp \
        machinedemo.cpp \
        main.cpp \
        mainwindow.cpp \
        window2.cpp

HEADERS += \
        asmdemo.h \
        assembler.h \
        copyright.h \
        disassembler.h \
        machinedemo.h \
        mainwindow.h \
        window2.h

FORMS += \
        asmdemo.ui \
        copyright.ui \
        machinedemo.ui \
        mainwindow.ui \
        window2.ui

RC_FILE += icoimg.rc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    icoimg.rc

