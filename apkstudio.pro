QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS  += src/ide.h \
    src/ideui.h \
    src/menubarui.h \
    src/settingsabstract.h \
    src/settings.h \
    src/constant.h \
    src/utility.h \
    src/menubar.h \
    src/toolbarui.h \
    src/toolbar.h

OTHER_FILES += \
    res/windows.rc

RESOURCES += \
    res/resources.qrc

SOURCES += src/main.cpp\
    src/ide.cpp \
    src/ideui.cpp \
    src/menubarui.cpp \
    src/settingsabstract.cpp \
    src/settings.cpp \
    src/utility.cpp \
    src/menubar.cpp \
    src/toolbarui.cpp \
    src/toolbar.cpp

TARGET = apkstudio
TEMPLATE = app

TRANSLATIONS += \
    res/lang/en.ts

win32:RC_FILE = res/windows.rc
