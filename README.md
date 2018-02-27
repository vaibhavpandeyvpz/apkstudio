[APK Studio](https://github.com/surendrajat/apkstudio) is a **cross-platform** IDE for reverse-engineering (decompiling/editing) & recompiling of android application binaries within a single user-interface. It features a friendly layout, with a code editor which support syntax highlighting for Android SMALI (*.smali) code files.

[![Build Status(Linux)](https://travis-ci.org/Surendrajat/apkstudio.svg)](https://travis-ci.org/Surendrajat/apkstudio) [![Build status(Windows)](https://ci.appveyor.com/api/projects/status/mnr254lm0mlshmfb?svg=true)](https://ci.appveyor.com/project/Surendrajat/apkstudio) [![Download](https://api.bintray.com/packages/vaibhavpandeyvpz/generic/apkstudio/images/download.svg) ](https://bintray.com/vaibhavpandeyvpz/generic/apkstudio/_latestVersion) [![issues](https://img.shields.io/github/issues/vaibhavpandeyvpz/apkstudio.svg?style=flat-square)](https://github.com/vaibhavpandeyvpz/apkstudio/issues) [![Code Health](https://landscape.io/github/Surendrajat/apkstudio/master/landscape.svg?style=flat)](https://landscape.io/github/Surendrajat/apkstudio/master) [![Join the chat at https://gitter.im/apk-studio/ideas](https://badges.gitter.im/apk-studio/ideas.svg)](https://gitter.im/apk-studio/ideas?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

Instructions:
--------
- Make sure **JAVA_HOME** point to a valid **JDK** (*JRE* may not work)
- You should also install or have **ADB** in *PATH*. This can be done on debian{-based} distros as follows:
```bash
sudo apt-get install android-tools-adb
```
- Also make sure you've **zipalign** installed. If it's not then issue the command:
```bash
sudo apt-get install zipalign
```
- You can then download, install & start de/re-compiling

**Note**: If you encounter any problems, make sure to check **Console Output** at bottom of IDE to get the output of command which was actually executed by program. Report any issues related to APK Studio [here](https://github.com/vaibhavpandeyvpz/apkstudio/issues) on Github. Please note, an issue with [apktool](http://ibotpeaches.github.io/Apktool/) is not an issue with **APK Studio**. Please verify the context of issue before opening a ticket.

Download:
--------
-   Native installers for supported platforms are [here](https://bintray.com/vaibhavpandeyvpz/generic/apkstudio/view).
    <br>
    [![Installers by BitRock](https://raw.githubusercontent.com/vaibhavpandeyvpz/apkstudio/master/external/bitrock.png "Many thanks to BitRock for donating license for InstallBuilder.")](http://installbuilder.bitrock.com/)


Building (Linux):
--------
- Make sure you have **GCC 4.6+**, **QT 5.2+**
- Run below commands in a writable directory
```bash
git clone https://github.com/surendrajat/apkstudio.git
cd apkstudio
lrelease res/lang/en.ts
qmake apkstudio.pro CONFIG+=release
# {IF} On KDE 5.x
export CXXFLAGS="$CXXFLAGS -DNO_NATIVE_DIALOG"
# {/IF}
make
```
- More information on building from source is provided in the [Wiki](https://github.com/surendrajat/apkstudio/wiki)

Features:
---------------------------------
- Decompile/Recompile APK
- Flexible Keystore & Key-Alias Chooser
- Automatic Zip-align
- Syntax Highlighting (*.java; *.smali; *.xml; *.yml)
- Image Viewer For Resources
- One-click **Install** To Device
- Frameworks Support

TODO:
-------------
- Code Completion

Screenshots:
-------------
![Windows Screenshot #1](https://raw.githubusercontent.com/surendrajat/apkstudio/master/external/screenshots/windows-1.png "Windows Screenshot #1")

![Linux Screenshot #1](https://raw.githubusercontent.com/surendrajat/apkstudio/master/external/screenshots/linux-1.png "Linux Screenshot #1")

![Linux Screenshot #2](https://raw.githubusercontent.com/surendrajat/apkstudio/master/external/screenshots/linux-2.png "Linux Screenshot #2")

Disclaimer:
-------------
Same as [apktool](http://ibotpeaches.github.io/Apktool/), **APK Studio** is neither intended for piracy nor other non-legal uses. It could be used for localizing, adding some features or support for custom platforms, analyzing applications &amp; much more.
