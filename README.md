APK Studio is a **cross-platform** IDE for reverse-engineering (decompiling/editing) & recompiling of android application binaries within a single user-interface. It features a friendly IDE like layout, with a code editor which support syntax highlighting for Android SMALI (*.smali) code files.

[![Build Status](https://travis-ci.org/vaibhavpandeyvpz/apkstudio.svg?branch=master)](https://travis-ci.org/vaibhavpandeyvpz/apkstudio)

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

TODO:
-------------
-   Code Completion
-   Frameworks Support

Screenshot:
-------------
![Windows Screenshot](https://raw.githubusercontent.com/vaibhavpandeyvpz/apkstudio/master/screenshots/1.png "Windows Screenshot")
