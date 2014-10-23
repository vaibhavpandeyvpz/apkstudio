# Include referenced co-projects & libraries
win32 {
    CONFIG(release, debug|release): {
        LIBS += -L$$OUT_PWD/../components/release/ -lcomponents
        LIBS += -L$$OUT_PWD/../helpers/release/ -lhelpers
        LIBS += -L$$OUT_PWD/../resources/release/ -lresources
        LIBS += -L$$OUT_PWD/../windows/release/ -lwindows
    } else {
        LIBS += -L$$OUT_PWD/../components/debug/ -lcomponents
        LIBS += -L$$OUT_PWD/../helpers/debug/ -lhelpers
        LIBS += -L$$OUT_PWD/../resources/debug/ -lresources
        LIBS += -L$$OUT_PWD/../windows/debug/ -lwindows
    }
}

unix {
    LIBS += -L$$OUT_PWD/../components/ -lcomponents
    LIBS += -L$$OUT_PWD/../helpers/ -lhelpers
    LIBS += -L$$OUT_PWD/../resources/ -lresources
    LIBS += -L$$OUT_PWD/../windows/ -lwindows
}

DEPENDPATH += $$PWD/../components
DEPENDPATH += $$PWD/../helpers
DEPENDPATH += $$PWD/../resources
DEPENDPATH += $$PWD/../windows

INCLUDEPATH += $$PWD/../components/vpz/apkstudio
INCLUDEPATH += $$PWD/../helpers/vpz/apkstudio
INCLUDEPATH += $$PWD/../resources/vpz/apkstudio
INCLUDEPATH += $$PWD/../windows/vpz/apkstudio

# Other misclleneous or platform specific files
OTHER_FILES += \
    ../../resource/language/en.ts \
    ../../resource/windows.rc \
    ../../resource/highlight/java.xml \
    ../../resource/highlight/number.xml \
    ../../resource/highlight/smali.xml \
    ../../resource/highlight/string.xml \
    ../../resource/highlight/xml.xml \
    ../../resource/theme/dark.xml \
    ../../resource/theme/light.xml

# Refrence QT framework dependencies
QT += core gui widgets

RESOURCES += \
    ../../resource/resources.qrc

# Source files to be included/compiled within target
SOURCES += main.cpp

# Other flags to direct qMake to build executable & where
TARGET = ../apkstudio
TEMPLATE = app

win32:RC_FILE = ../../resource/windows.rc

HEADERS +=
