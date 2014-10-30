!include("../apkstudio.pri") {
    error("Unable to locate &/or include apkstudio.pri")
}

# Enable support for newer c++ expressions
CONFIG += c++11

QT += core gui widgets

# Source files to be included/compiled within target
HEADERS += \
    vpz/apkstudio/components/coder.hpp \
    vpz/apkstudio/components/linenumbers.hpp \
    vpz/apkstudio/components/recents.hpp \
    vpz/apkstudio/components/scripts.hpp \
    vpz/apkstudio/components/viewer.hpp \
    vpz/apkstudio/components/devices.hpp \
    vpz/apkstudio/components/editor.hpp \
    vpz/apkstudio/components/output.hpp \
    vpz/apkstudio/components/projects.hpp \
    vpz/apkstudio/components/files.hpp \
    vpz/apkstudio/components/outline.hpp \
    vpz/apkstudio/components/tasks.hpp \
    vpz/apkstudio/components/terminal.hpp \
    vpz/apkstudio/components/dockable.hpp

SOURCES += \
    vpz/apkstudio/components/coder.cpp \
    vpz/apkstudio/components/linenumbers.cpp \
    vpz/apkstudio/components/recents.cpp \
    vpz/apkstudio/components/scripts.cpp \
    vpz/apkstudio/components/viewer.cpp \
    vpz/apkstudio/components/devices.cpp \
    vpz/apkstudio/components/editor.cpp \
    vpz/apkstudio/components/output.cpp \
    vpz/apkstudio/components/projects.cpp \
    vpz/apkstudio/components/files.cpp \
    vpz/apkstudio/components/outline.cpp \
    vpz/apkstudio/components/tasks.cpp \
    vpz/apkstudio/components/terminal.cpp \
    vpz/apkstudio/components/dockable.cpp

# Include referenced co-projects & libraries
win32 {
    CONFIG(release, debug|release): {
        LIBS += -L$$OUT_PWD/../helpers/release/ -lhelpers
        LIBS += -L$$OUT_PWD/../resources/release/ -lresources
    } else {
        LIBS += -L$$OUT_PWD/../helpers/debug/ -lhelpers
        LIBS += -L$$OUT_PWD/../resources/debug/ -lresources
    }
}

unix {
    LIBS += -L$$OUT_PWD/../helpers/ -lhelpers
    LIBS += -L$$OUT_PWD/../resources/ -lresources
}

DEPENDPATH += $$PWD/../helpers
DEPENDPATH += $$PWD/../resources

INCLUDEPATH += $$PWD/../helpers/vpz/apkstudio
INCLUDEPATH += $$PWD/../resources/vpz/apkstudio
