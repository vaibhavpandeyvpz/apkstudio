# APK Studio [![Codacy Badge](https://api.codacy.com/project/badge/Grade/9709de5012824c36b54fda9c2c6390bf)](https://app.codacy.com/app/Surendrajat/apkstudio?utm_source=github.com&utm_medium=referral&utm_content=Surendrajat/apkstudio&utm_campaign=badger) [![Build Status(Linux)](https://travis-ci.org/Surendrajat/ApkStudio.svg)](https://travis-ci.org/Surendrajat/ApkStudio) [![Build status(Windows)](https://ci.appveyor.com/api/projects/status/mnr254lm0mlshmfb?svg=true)](https://ci.appveyor.com/project/Surendrajat/apkstudio) [![Join the chat at https://gitter.im/apk-studio/ideas](https://badges.gitter.im/apk-studio/ideas.svg)](https://gitter.im/apk-studio/ideas?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
>**A Cross-Platform IDE for Reverse-Engineering (Decompiling, Hacking & Rebuilding)  Android applications  - featuring a friendly UI and Code editor which Syntax-highlighting for `smali` files**

### Features
- Decompile & Recompile APKs
- Code Editor with Syntax Highlighting (`smali` `xml` `yml` language)
- Flexible Keystore & Key-Alias Chooser
- Automatic *zipalign* & Apk *sign*ing
- Built-in Image viewer for Resources
- One-click App Install to device
- Frameworks Support

### Download
 >[![Download](https://img.shields.io/github/release/surendrajat/apkstudio/all.svg?longCache=true&style=for-the-badge)](https://github.com/Surendrajat/apkstudio/releases)

### Requirements
- **JDK >= 8**
- **Apktool**  
  [Download](https://bitbucket.org/iBotPeaches/apktool/downloads/) latest `apktool.jar` and put it in the following path:  
    - Linux: `/home/{your-user-name}/.apkstudio/vendor/apktool.jar`  
    - Windows: `C:\Users\{your-user-name}\.apkstudio\vendor\apktool.jar`

    If you've `apktool.jar` already installed in the specified path, replace it with the new one and execute the following command in same path:   `java -jar apktool.jar empty-framework-dir --force`
- **adb** driver and **zipalign** utility  
    - Ubuntu: `sudo apt-get install android-tools-adb zipalign`  
    - Windows: [adb driver](https://lifehacker.com/the-easiest-way-to-install-androids-adb-and-fastboot-to-1586992378) [zipalign](https://stackoverflow.com/questions/36916462/how-to-zipalign-the-apk-file-in-windows)

### Links
- [Building (Command line)](https://github.com/Surendrajat/ApkStudio/wiki/Building#building-linux)
- [Building (Qt Creator)](https://github.com/Surendrajat/ApkStudio/wiki/Building#building-with-qt-creator)
- [Bug Reporting](https://github.com/surendrajat/apkstudio/issues)
- [Contributors](https://github.com/Surendrajat/ApkStudio/graphs/contributors)
- [Special Thanks](https://github.com/Surendrajat/ApkStudio/wiki/SpecialThanks)

### TODO
- Replacing `jarsigner` with [`uber-apk-signer`](https://github.com/patrickfav/uber-apk-signer) ([#issue96](https://github.com/vaibhavpandeyvpz/apkstudio/issues/96))
- [Framework installation](https://ibotpeaches.github.io/Apktool/documentation/#frameworks) within IDE
- Code Completion

### Screenshots
>![Screenshot #1](https://raw.githubusercontent.com/surendrajat/apkstudio/master/external/screenshots/apkstudio000.png "Screenshot #1")

>![Screenshot #2](https://raw.githubusercontent.com/surendrajat/apkstudio/master/external/screenshots/apkstudio002.png "Screenshot #2")

### Disclaimer
>Same as [Apktool](http://ibotpeaches.github.io/Apktool/), **APK Studio** is neither intended for piracy nor other non-legal uses. It could be used for localizing, adding some features or support for custom platforms, analyzing applications &amp; much more.