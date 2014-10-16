!include("../apkstudio.pri") {
    error("Unable to locate &/or include apkstudio.pri")
}

# Include referenced co-projects & libraries
INCLUDEPATH += ../resources/vpz/apkstudio

# Refrence QT framework dependencies
QT += core gui widgets

# Source files to be included/compiled within target
HEADERS += \
    vpz/apkstudio/helpers/text.hpp \
    vpz/apkstudio/helpers/format.hpp \
    vpz/apkstudio/helpers/settings.hpp \
    vpz/apkstudio/helpers/macro.hpp

SOURCES += \
    vpz/apkstudio/helpers/text.cpp \
    vpz/apkstudio/helpers/format.cpp \
    vpz/apkstudio/helpers/settings.cpp
