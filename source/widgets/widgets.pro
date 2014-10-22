!include("../apkstudio.pri") {
    error("Unable to locate &/or include apkstudio.pri")
}

# Refrence QT framework dependencies
QT += core gui widgets

# Source files to be included/compiled within target
HEADERS += \
    vpz/apkstudio/widgets/recents.hpp \
    vpz/apkstudio/widgets/scripts.hpp

SOURCES += \
    vpz/apkstudio/widgets/recents.cpp \
    vpz/apkstudio/widgets/scripts.cpp

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
