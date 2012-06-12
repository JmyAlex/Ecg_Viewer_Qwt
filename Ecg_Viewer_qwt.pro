#-------------------------------------------------
#
# Project created by QtCreator 2011-12-03T15:45:12
#
#-------------------------------------------------

QT       += core gui

TARGET = Ecg_Viewer_qwt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Plot/zoomer.cpp \
    Plot/panner.cpp \
    Plot/magnifier.cpp \
    Plot/grid.cpp \
    Plot/plot.cpp \
    Signal/signaldata.cpp \
    Signal/curvedata.cpp

HEADERS  += mainwindow.h \
    Plot/zoomer.h \
    Plot/panner.h \
    Plot/magnifier.h \
    Plot/grid.h \
    Plot/plot.h \
    Signal/signaldata.h \
    Signal/curvedata.h

INCLUDEPATH += E:/VirtualBox/SharingFolder/qwt-6.0/src

LIBS += E:/VirtualBox/SharingFolder/qwt-6.0/lib/libqwtd.a

RESOURCES += \
    application.qrc




















