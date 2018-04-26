
# APK Studio [![Codacy Badge](https://api.codacy.com/project/badge/Grade/a816c080acad4a1989219c0f55da34b3)](https://www.codacy.com/app/Surendrajat/apkstudio_2?utm_source=github.com&utm_medium=referral&utm_content=vaibhavpandeyvpz/apkstudio&utm_campaign=Badge_Grade) [![Build Status](https://travis-ci.org/vaibhavpandeyvpz/apkstudio.svg)](https://travis-ci.org/vaibhavpandeyvpz/apkstudio) [![Build status](https://ci.appveyor.com/api/projects/status/t437hn0osaik6vv5/branch/master?svg=true)](https://ci.appveyor.com/project/Surendrajat/apkstudio-1cupt/branch/master) [![Join the chat at https://gitter.im/apk-studio/ideas](https://badges.gitter.im/apk-studio/ideas.svg)](https://gitter.im/apk-studio/ideas?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
>**A Cross-Platform IDE for Reverse-Engineering (Disassembling, Hacking & Rebuilding)  Android applications  - featuring a friendly UI and Code editor with Syntax-highlighting support**

### Features
- Disassembling & Rebuilding APKs
- Code Editor with Syntax Highlighting (`java` `smali` `xml` `yml`)
-  Built-in Image viewer for Resources
- Single-click APK Signing with embedded key-store *(New)*
- Android Signing scheme v2 Support *(New)*
- Flexible Keystore & Key-Alias import
- Automatic Zip-Aligning with embedded `zipalign` *(New)*
- Single-click App Install to device
- Frameworks Support

### Download
 >[![Download](https://img.shields.io/github/release/vaibhavpandeyvpz/apkstudio/all.svg?longCache=true&style=for-the-badge)](https://github.com/vaibhavpandeyvpz/apkstudio/releases)

### Requirements
- **JDK >= 8**
- **Apktool**  
  >Download latest [`apktool`](https://bitbucket.org/iBotPeaches/apktool/downloads/), rename it to `apktool.jar` and put it in the following path:  
  >- Linux: `/home/{your-user-name}/.apkstudio/vendor/apktool.jar`  
  >- Windows: `C:\Users\{your-user-name}\.apkstudio\vendor\apktool.jar`
 
  >If you've `apktool.jar` already installed in the specified path, replace it with the new one and execute the following command in same path:   `java -jar apktool.jar empty-framework-dir --force`
- **uber-apk-signer**  
  >Download latest [`uber-apk-signer`](https://github.com/patrickfav/uber-apk-signer/releases), rename it to `uber-apk-signer.jar` and put it in the following path:  
    >- Linux: `/home/{your-user-name}/.apkstudio/vendor/uber-apk-signer.jar`  
    >- Windows: `C:\Users\{your-user-name}\.apkstudio\vendor\uber-apk-signer.jar`
- **adb** (optional) and **zipalign** (linux_x86 only) 
    >- Ubuntu: `sudo apt-get install android-tools-adb zipalign`  
    >- Windows: [adb driver](https://lifehacker.com/the-easiest-way-to-install-androids-adb-and-fastboot-to-1586992378)

### Links
- [Building (Command line)](https://github.com/vaibhavpandeyvpz/apkstudio/wiki/Building#building-linux)
- [Building (Qt Creator)](https://github.com/vaibhavpandeyvpz/apkstudio/wiki/Building#building-with-qt-creator)
- [Bug Reporting](https://github.com/vaibhavpandeyvpz/apkstudio/issues)
- [Contributors](https://github.com/vaibhavpandeyvpz/apkstudio/graphs/contributors)
- [Special Thanks](https://github.com/vaibhavpandeyvpz/apkstudio/wiki/SpecialThanks)
- [XDA Thread](https://forum.xda-developers.com/showthread.php?t=3761033)

### TODO
- [Framework management](https://ibotpeaches.github.io/Apktool/documentation/#frameworks) within IDE
- Opcode Hex Viewer

### Screenshots
>![Screenshot #1](https://raw.githubusercontent.com/vaibhavpandeyvpz/apkstudio/master/external/screenshots/apkstudio881.png "Screenshot #1")

>![Screenshot #2](https://raw.githubusercontent.com/vaibhavpandeyvpz/apkstudio/master/external/screenshots/apkstudio882.png "Screenshot #2")

### Disclaimer
>Same as [Apktool](http://ibotpeaches.github.io/Apktool/), **APK Studio** is neither intended for piracy nor other non-legal uses. It could be used for localizing, adding some features or support for custom platforms, analyzing applications & much more.
