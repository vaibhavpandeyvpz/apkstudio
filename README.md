APK Studio is a **cross-platform** IDE for reverse-engineering (decompiling/editing) & recompiling of android application binaries within a single user-interface. It features a friendly IDE like layout, with a code editor which support syntax highlighting for Android SMALI (*.smali) code files.

[![Current Release](https://img.shields.io/github/release/vaibhavpandeyvpz/apkstudio.svg)](https://github.com/vaibhavpandeyvpz/apkstudio/releases) [![Build Status](https://img.shields.io/travis/vaibhavpandeyvpz/apkstudio.svg?style=flat-square)](https://travis-ci.org/vaibhavpandeyvpz/apkstudio) [![Downloads](https://img.shields.io/github/downloads/vaibhavpandeyvpz/apkstudio/latest/total.svg?style=flat-square)](https://github.com/vaibhavpandeyvpz/apkstudio/releases) [![GPL v3](https://img.shields.io/github/license/vaibhavpandeyvpz/apkstudio.svg?style=flat-square)](https://github.com/vaibhavpandeyvpz/apkstudio/blob/master/LICENSE.md)

Instructions
--------
- Make sure **JAVA_HOME** point to a valid **JDK** (*JRE* will not work)
- Point the **Binaries Path** in *Edit* > *Settings* to a valid folder having *ADB*, *Zipalign* & *apktool*
- Start re-building.

**Note**: If you encounter any problems, make sure to check **Console Output** at bottom of IDE to get the output of command which was actually executed by program. Report any issues related to APK Studio [here](https://github.com/vaibhavpandeyvpz/apkstudio/issues) on Github. Please note, an issue with [apktool](http://ibotpeaches.github.io/Apktool/) is not an issue with **APK Studio**. Please verify the context of issue before opening a ticket.

Download
--------
-   Please check **Releases** tab for Windows binaries
-   Linux users are required to build from source atm

Building (Linux)
--------
-   Make sure you have **GCC 4.8+**, **QT 5.4+**
-   Run below commands in a writable directory
```bash
# Run these commands in sequence
git clone https://github.com/vaibhavpandeyvpz/apkstudio.git
cd apkstudio
lrelease resources/lang/en.ts
qmake apkstudio.pro CONFIG+=release
make
```

Features:
---------------------------------
-   Decompile/Recompile APK
-   Flexible Keystore & Key-Alias Chooser
-   Automatic Zip-align
-   Image Viewer For Resources
-   One-click **Install** To Device
-   Syntax Highlighting (*java; *.smali; *.xml; *.yml)
-   Frameworks Support

TODO:
-------------
-   Code Completion

Screenshot:
-------------
![Windows Screenshot #1](https://raw.githubusercontent.com/vaibhavpandeyvpz/apkstudio/master/external/screenshots/windows-1.png "Windows Screenshot #1")
