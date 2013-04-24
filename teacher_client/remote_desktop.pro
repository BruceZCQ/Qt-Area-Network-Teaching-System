QT  += core gui
QT += sql
QT += webkit network
QT += qt3support
TARGET = remote_desktop
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    functionbox.cpp \
    teachingdb.cpp \
    sendquestiondialog.cpp \
    teachingroomstudents.cpp \
    teachingroomclass.cpp \
    settingdbserver.cpp \
    changepassworddialog.cpp \
    classmanagement.cpp \
    questionset.cpp \
    editquestion.cpp \
    createquestion.cpp \
    viewstudentinfo.cpp \
    viewquestioninfo.cpp \
    infotabwidget.cpp \
    serverstyle.cpp \
    answeredquestion.cpp \
    broadcast.cpp

HEADERS  += mainwindow.h \
    constvar.h \
    logindialog.h \
    functionbox.h \
    teachingdb.h \
    sendquestiondialog.h \
    teachingroomstudents.h \
    teachingroomclass.h \
    settingdbserver.h \
    changepassworddialog.h \
    classmanagement.h \
    questionset.h \
    editquestion.h \
    createquestion.h \
    viewstudentinfo.h \
    viewquestioninfo.h \
    infotabwidget.h \
    serverstyle.h \
    answeredquestion.h \
    broadcast.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    functionbox.ui \
    sendquestiondialog.ui \
    settingdbserver.ui \
    changepassworddialog.ui \
    classmanagement.ui \
    editquestion.ui \
    createquestion.ui \
    viewstudentinfo.ui \
    viewquestioninfo.ui \
    broadcast.ui

RESOURCES += \
    icons.qrc

OTHER_FILES += \
    app.rc \
    icons/style.qss
RC_FILE = app.rc
include(lib/lib.pri)
