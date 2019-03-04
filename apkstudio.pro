QT += core gui widgets

TARGET = ApkStudio
TEMPLATE = app

CONFIG += c++11

HEADERS += \
    sources/mainwindow.h \
    sources/splashwindow.h

SOURCES += \
    sources/main.cpp \
    sources/mainwindow.cpp \
    sources/splashwindow.cpp

RESOURCES += \
    resources/all.qrc

win32:RC_FILE = resources/windows.rc
