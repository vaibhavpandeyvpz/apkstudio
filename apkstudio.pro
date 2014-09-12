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
    src/toolbar.h \
    src/iaction.h \
    src/projectspanelui.h \
    src/projectspanel.h \
    src/filespanelui.h \
    src/filespanel.h \
    src/editorspanelui.h \
    src/editorspanel.h \
    src/outlinepanelui.h \
    src/outlinepanel.h \
    src/taskspanel.h \
    src/taskspanelui.h \
    src/logspanelui.h \
    src/logspanel.h \
    src/panelui.h \
    src/imageeditorui.h \
    src/imageeditor.h \
    src/flickcharm.h \
    src/editorwidgetui.h \
    src/editorwidget.h

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
    src/toolbar.cpp \
    src/projectspanelui.cpp \
    src/projectspanel.cpp \
    src/filespanelui.cpp \
    src/filespanel.cpp \
    src/editorspanelui.cpp \
    src/editorspanel.cpp \
    src/outlinepanelui.cpp \
    src/outlinepanel.cpp \
    src/taskspanel.cpp \
    src/taskspanelui.cpp \
    src/logspanelui.cpp \
    src/logspanel.cpp \
    src/panelui.cpp \
    src/imageeditorui.cpp \
    src/imageeditor.cpp \
    src/flickcharm.cpp \
    src/editorwidgetui.cpp \
    src/editorwidget.cpp

TARGET = apkstudio
TEMPLATE = app

TRANSLATIONS += \
    res/lang/en.ts

win32:RC_FILE = res/windows.rc
