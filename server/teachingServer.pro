#-------------------------------------------------
#
# Project created by QtCreator 2012-04-17T13:23:46
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += webkit network

TARGET = teachingServer
TEMPLATE = app


SOURCES += main.cpp\
        serverdashboard.cpp \
    customtabwidget.cpp \
    loginserverdialog.cpp \
    serversettingdialog.cpp \
    serverstyle.cpp \
    database.cpp \
    studentclassinfomaintain.cpp \
    teachingroomstudents.cpp \
    questionset.cpp \
    teachingroomclass.cpp \
    customstudenttablewidget.cpp

HEADERS  += serverdashboard.h \
    customtabwidget.h \
    loginserverdialog.h \
    serversettingdialog.h \
    serverstyle.h \
    database.h \
    serverconst.h \
    studentclassinfomaintain.h \
    teachingroomstudents.h \
    questionset.h \
    teachingroomclass.h \
    customstudenttablewidget.h

FORMS    += serverdashboard.ui \
    loginserverdialog.ui \
    serversettingdialog.ui \
    studentclassinfomaintain.ui

RESOURCES += \
    icons.qrc

OTHER_FILES += \
    app.rc \
    resource/style/style.qss
RC_FILE = app.rc
include(lib/lib.pri)
