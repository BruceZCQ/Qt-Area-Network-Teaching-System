#-------------------------------------------------
#
# Project created by QtCreator 2012-01-08T15:38:18
#
#-------------------------------------------------

QT       += core gui
QT += webkit network
QT += sql
QT += qt3support
TARGET = student
TEMPLATE = app


SOURCES += main.cpp\
    logindialog.cpp \
    settingserver.cpp \
    database.cpp \
    signupdialog.cpp \
    studentdashboard.cpp \
    style.cpp \
    pptwin.cpp \
    codingwindow.cpp \
    highlighter.cpp \
    questionwindow.cpp \
    receivequestion.cpp \
    questionset.cpp \
    answeredquestion.cpp \
    teachingroomstudents.cpp \
    customtextedit.cpp \
    questionwidget.cpp \
    videoview.cpp \
    showbroadcastcontent.cpp

HEADERS  += \
    logindialog.h \
    constvar.h \
    settingserver.h \
    database.h \
    signupdialog.h \
    studentdashboard.h \
    style.h \
    pptwin.h \
    codingwindow.h \
    highlighter.h \
    questionwindow.h \
    receivequestion.h \
    questionset.h \
    answeredquestion.h \
    teachingroomstudents.h \
    customtextedit.h \
    questionwidget.h \
    videoview.h \
    showbroadcastcontent.h

FORMS    += \
    logindialog.ui \
    settingserver.ui \
    signupdialog.ui \
    studentdashboard.ui \
    pptwin.ui \
    codingwindow.ui \
    questionwindow.ui \
    receivequestion.ui \
    questionwidget.ui \
    videoview.ui \
    showbroadcastcontent.ui

OTHER_FILES += \
    app.rc \
    style/style.qss

RESOURCES += \
    icons.qrc \
    icons.qrc
RC_FILE = app.rc
include(lib/lib.pri)
