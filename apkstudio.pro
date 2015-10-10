CONFIG += c++11

HEADERS += \
    include/adb.h \
    include/adbdock.h \
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
    include/dex2jar.h \
    include/dialog.h \
    include/editortabs.h \
    include/fileutils.h \
    include/findreplace.h \
    include/flickcharm.h \
    include/ide.h \
    include/installrunnable.h \
    include/jarsigner.h \
    include/jarsignerdock.h \
    include/java.h \
    include/javadock.h \
    include/macros.h \
    include/menubar.h \
    include/pathutils.h \
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
    include/viewer.h \
    include/zipalign.h \
    include/zipaligndock.h

INCLUDEPATH += include

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

QT += core gui widgets

RESOURCES += \
    res/all.qrc

SOURCES += \
    src/adb.cpp \
    src/adbdock.cpp \
    src/apktool.cpp \
    src/buildrunnable.cpp \
    src/coder.cpp \
    src/coderhighlighter.cpp \
    src/coderhighlighterdefinition.cpp \
    src/coderhighlightertheme.cpp \
    src/codersidebar.cpp \
    src/consoledock.cpp \
    src/decoderunnable.cpp \
    src/dex2jar.cpp \
    src/dialog.cpp \
    src/editortabs.cpp \
    src/fileutils.cpp \
    src/findreplace.cpp \
    src/flickcharm.cpp \
    src/ide.cpp \
    src/installrunnable.cpp \
    src/jarsigner.cpp \
    src/jarsignerdock.cpp \
    src/java.cpp \
    src/javadock.cpp \
    src/main.cpp \
    src/menubar.cpp \
    src/pathutils.cpp \
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
    src/viewer.cpp \
    src/zipalign.cpp \
    src/zipaligndock.cpp

TARGET = apkstudio

TEMPLATE = app

TRANSLATIONS += \
    res/lang/en.ts

win32:RC_FILE = res/win32.rc

DISTFILES += \
    external/updates.json
