#-------------------------------------------------
#
# Project created by QtCreator 2018-05-11T12:51:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = my_wc100
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainbutton.cpp \
    testingdialog.cpp

HEADERS  += mainwindow.h \
    mainbutton.h \
    testingdialog.h

FORMS    += mainwindow.ui \
    mainbutton.ui \
    testingdialog.ui

RESOURCES += \
    rc.qrc
