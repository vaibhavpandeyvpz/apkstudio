!include("../apkstudio.pri") {
    error("Unable to locate &/or include apkstudio.pri")
}

# Enable support for newer c++ expressions
CONFIG += c++11

# Include referenced co-projects & libraries
INCLUDEPATH += ../resources/vpz/apkstudio

# Refrence QT framework dependencies
QT += core gui widgets

# Source files to be included/compiled within target
HEADERS += \
    vpz/apkstudio/helpers/text.hpp \
    vpz/apkstudio/helpers/format.hpp \
    vpz/apkstudio/helpers/settings.hpp \
    vpz/apkstudio/helpers/macro.hpp \
    vpz/apkstudio/helpers/highlighter.hpp \
    vpz/apkstudio/helpers/completer.hpp \
    vpz/apkstudio/helpers/application.hpp \
    vpz/apkstudio/helpers/bracketmatcher.hpp \
    vpz/apkstudio/helpers/flickcharm.hpp \
    vpz/apkstudio/helpers/adb.hpp \
    vpz/apkstudio/helpers/cli.hpp \
    vpz/apkstudio/helpers/apktool.hpp \
    vpz/apkstudio/helpers/realtime.hpp \
    vpz/apkstudio/helpers/projects.hpp

SOURCES += \
    vpz/apkstudio/helpers/text.cpp \
    vpz/apkstudio/helpers/format.cpp \
    vpz/apkstudio/helpers/settings.cpp \
    vpz/apkstudio/helpers/highlighter.cpp \
    vpz/apkstudio/helpers/completer.cpp \
    vpz/apkstudio/helpers/application.cpp \
    vpz/apkstudio/helpers/bracketmatcher.cpp \
    vpz/apkstudio/helpers/flickcharm.cpp \
    vpz/apkstudio/helpers/adb.cpp \
    vpz/apkstudio/helpers/cli.cpp \
    vpz/apkstudio/helpers/apktool.cpp \
    vpz/apkstudio/helpers/realtime.cpp \
    vpz/apkstudio/helpers/projects.cpp
