CONFIG += c++11

HEADERS += \
    include/adb.h \
    include/apktool.h \
    include/buildrunnable.h \
    include/coder.h \
    include/coderhighlighter.h \
    include/coderhighlighterdefinition.h \
    include/coderhighlightertheme.h \
    include/codersidebar.h \
    include/consoledock.h \
    include/constants.h \
    include/decoderunnable.h \
    include/dialog.h \
    include/editortabs.h \
    include/fileutils.h \
    include/findreplace.h \
    include/flickcharm.h \
    include/ide.h \
    include/installrunnable.h \
    include/jarsigner.h \
    include/java.h \
    include/macros.h \
    include/menubar.h \
    include/pathutils.h \
    include/pleasewait.h \
    include/preferences.h \
    include/preopenapk.h \
    include/process.h \
    include/projectdock.h \
    include/qrc.h \
    include/runnable.h \
    include/runner.h \
    include/settingseditor.h \
    include/signexportapk.h \
    include/signrunnable.h \
    include/statusbar.h \
    include/textutils.h \
    include/toolbar.h \
    include/updatedownloader.h \
    include/viewer.h \
    include/zipalign.h

OTHER_FILES += \
    .gitignore \
    .travis.yml \
    res/highlight/default.theme \
    res/highlight/java.def \
    res/highlight/numbers.def \
    res/highlight/smali.def \
    res/highlight/strings.def \
    res/highlight/xml.def \
    res/highlight/yml.def \
    res/html/about.html \ \
    res/lang/en.ts \
    res/styles/default.qss \
    res/win32.rc \
    README.md

QT += core gui network widgets

RESOURCES += \
    res/all.qrc

win32 {
    INCLUDEPATH += C:/OpenSSL-Win32/include

    LIBS += -LC:/OpenSSL-Win32/lib -lubsec

    RC_FILE = res/win32.rc
}

SOURCES += \
    src/adb.cpp \
    src/apktool.cpp \
    src/buildrunnable.cpp \
    src/coder.cpp \
    src/coderhighlighter.cpp \
    src/coderhighlighterdefinition.cpp \
    src/coderhighlightertheme.cpp \
    src/codersidebar.cpp \
    src/consoledock.cpp \
    src/decoderunnable.cpp \
    src/dialog.cpp \
    src/editortabs.cpp \
    src/fileutils.cpp \
    src/findreplace.cpp \
    src/flickcharm.cpp \
    src/ide.cpp \
    src/installrunnable.cpp \
    src/jarsigner.cpp \
    src/java.cpp \
    src/main.cpp \
    src/menubar.cpp \
    src/pathutils.cpp \
    src/pleasewait.cpp \
    src/preferences.cpp \
    src/preopenapk.cpp \
    src/process.cpp \
    src/projectdock.cpp \
    src/qrc.cpp \
    src/runnable.cpp \
    src/runner.cpp \
    src/settingseditor.cpp \
    src/signexportapk.cpp \
    src/signrunnable.cpp \
    src/statusbar.cpp \
    src/textutils.cpp \
    src/toolbar.cpp \
    src/updatedownloader.cpp \
    src/viewer.cpp \
    src/zipalign.cpp

TARGET = apkstudio

TEMPLATE = app

TRANSLATIONS += \
    res/lang/en.ts
