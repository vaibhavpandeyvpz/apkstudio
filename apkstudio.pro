CONFIG += c++11

HEADERS += \
    sources/ide.h \
    sources/qrc.h \
    sources/apktool.h \
    sources/constants.h \
    sources/statusbar.h \
    sources/java.h \
    sources/javadock.h \
    sources/macros.h \
    sources/process.h \
    sources/pathutils.h \
    sources/textutils.h \
    sources/adb.h \
    sources/consoledock.h \
    sources/menubar.h \
    sources/adbdock.h \
    sources/projectdock.h \
    sources/preferences.h \
    sources/editortabs.h \
    sources/coder.h \
    sources/codersidebar.h \
    sources/toolbar.h \
    sources/fileutils.h \
    sources/zipaligndock.h \
    sources/zipalign.h \
    sources/jarsigner.h \
    sources/jarsignerdock.h \
    sources/dialog.h \
    sources/viewer.h \
    sources/flickcharm.h \
    sources/findreplace.h \
    sources/settingseditor.h \
    sources/signexportapk.h \
    sources/coderhighlighter.h \
    sources/coderhighlighterdefinition.h \
    sources/coderhighlightertheme.h \
    sources/runnable.h \
    sources/runner.h \
    sources/buildrunnable.h \
    sources/installrunnable.h \
    sources/decoderunnable.h \
    sources/signrunnable.h

OTHER_FILES += \
    .travis.yml \
    resources/highlight/default.theme \
    resources/highlight/java.def \
    resources/highlight/numbers.def \
    resources/highlight/smali.def \
    resources/highlight/strings.def \
    resources/highlight/xml.def \
    resources/highlight/yml.def \
    resources/html/about.html \
    resources/lang/en.ts \
    resources/styles/default.qss \
    resources/win32.rc \
    README.md

QMAKE_POST_LINK = $(QTDIR)/bin/lrelease $$_PRO_FILE_PWD_/resources/lang/en.ts

QT += core gui widgets

RESOURCES += \
    resources/all.qrc

SOURCES += \
    sources/ide.cpp \
    sources/apktool.cpp \
    sources/java.cpp \
    sources/javadock.cpp \
    sources/main.cpp \
    sources/qrc.cpp \
    sources/statusbar.cpp \
    sources/process.cpp \
    sources/pathutils.cpp \
    sources/menubar.cpp \
    sources/textutils.cpp \
    sources/adb.cpp \
    sources/consoledock.cpp \
    sources/adbdock.cpp \
    sources/projectdock.cpp \
    sources/preferences.cpp \
    sources/editortabs.cpp \
    sources/coder.cpp \
    sources/codersidebar.cpp \
    sources/toolbar.cpp \
    sources/fileutils.cpp \
    sources/zipaligndock.cpp \
    sources/zipalign.cpp \
    sources/jarsignerdock.cpp \
    sources/jarsigner.cpp \
    sources/dialog.cpp \
    sources/viewer.cpp \
    sources/flickcharm.cpp \
    sources/findreplace.cpp \
    sources/settingseditor.cpp \
    sources/signexportapk.cpp \
    sources/coderhighlighter.cpp \
    sources/coderhighlighterdefinition.cpp \
    sources/coderhighlightertheme.cpp \
    sources/buildrunnable.cpp \
    sources/decoderunnable.cpp \
    sources/signrunnable.cpp \
    sources/runnable.cpp \
    sources/installrunnable.cpp \
    sources/runner.cpp

TARGET = apkstudio

TEMPLATE = app

win32 {
    RC_FILE = resources/win32.rc
}
