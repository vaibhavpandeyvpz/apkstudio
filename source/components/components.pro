!include("../apkstudio.pri") {
    error("Unable to locate &/or include apkstudio.pri")
}

QT += core gui widgets

# Source files to be included/compiled within target
HEADERS += \
    vpz/apkstudio/components/coder.hpp

SOURCES += \
    vpz/apkstudio/components/coder.cpp

# Include referenced co-projects & libraries
win32 {
    CONFIG(release, debug|release): {
        LIBS += -L$$OUT_PWD/../resources/release/ -lresources
        LIBS += -L$$OUT_PWD/../helpers/release/ -lhelpers
    } else {
        LIBS += -L$$OUT_PWD/../resources/debug/ -lresources
        LIBS += -L$$OUT_PWD/../helpers/debug/ -lhelpers
    }
}

unix {
    LIBS += -L$$OUT_PWD/../resources/ -lresources
    LIBS += -L$$OUT_PWD/../helpers/ -lhelpers
}

DEPENDPATH += $$PWD/../helpers
DEPENDPATH += $$PWD/../resources

INCLUDEPATH += $$PWD/../helpers/vpz/apkstudio
INCLUDEPATH += $$PWD/../resources/vpz/apkstudio

