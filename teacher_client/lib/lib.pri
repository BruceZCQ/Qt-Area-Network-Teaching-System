INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/qxtglobal.h \
           $$PWD/qxtglobalshortcut.h \
           $$PWD/qxtglobalshortcut_p.h \
            $$PWD/datatransferserver.h

SOURCES += $$PWD/qxtglobalshortcut.cpp \
                      $$PWD/datatransferserver.cpp
win32{
    SOURCES += $$PWD/qxtglobalshortcut_win.cpp
    LIBS += -luser32
}
unix:SOURCES += $$PWD/qxtglobalshortcut_x11.cpp
mac:SOURCES += $$PWD/qxtglobalshortcut_mac.cpp
