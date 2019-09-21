<h1 align="center">
  <a href="http://www.vaibhavpandey.com/apkstudio/">
    <img src="https://raw.githubusercontent.com/vaibhavpandeyvpz/apkstudio/master/resources/icon.png" alt="APK Studio" height="192px">
  </a>
  <br>
  APK Studio
</h1>

Open-source, cross platform [Qt](https://www.qt.io/) based IDE for reverse-engineering [Android](https://android.com/) application packages. It features a friendly IDE-like layout including code editor with syntax highlighting support for \*.smali code files.

[![Screenshot](https://raw.githubusercontent.com/vaibhavpandeyvpz/apkstudio/master/resources/screenshot.png)](https://raw.githubusercontent.com/vaibhavpandeyvpz/apkstudio/master/resources/screenshot.png)

<p align="center">
  <a href="https://ci.appveyor.com/project/vaibhavpandeyvpz/apkstudio">
    <img src="https://img.shields.io/appveyor/ci/vaibhavpandeyvpz/apkstudio.svg" alt="AppVeyor">
  </a>
  <a href="https://travis-ci.org/vaibhavpandeyvpz/apkstudio">
    <img src="https://img.shields.io/travis/vaibhavpandeyvpz/apkstudio.svg" alt="Travis CI">
  </a>
  <a href="https://github.com/vaibhavpandeyvpz/apkstudio/releases/latest">
    <img src="https://img.shields.io/github/release/vaibhavpandeyvpz/apkstudio.svg" alt="Release">
  </a>
  <a href="https://github.com/vaibhavpandeyvpz/apkstudio/releases">
    <img src="https://img.shields.io/github/downloads/vaibhavpandeyvpz/apkstudio/total.svg" alt="Downloads">
  </a>
</p>

If you are just willing to quickly decompile an [Android](https://android.com/) app, you can make use of [DeAPK - Online APK Decompiler](https://deapk.vaibhavpandey.com/) which lets you decompile an Android app using [apktool](https://github.com/ibotpeaches/apktool) and [jadx](https://github.com/skylot/jadx).

### Features
- Cross platform, run on **Linux**, **Mac OS X** & **Windows**
- Decompile/recompile/sign & install APKs
- Built-in code editor (\*.java; \*.smali; \*.xml; \*.yml) w/ syntax highlighting
- Built-in viewer for image (\*.gif; \*.jpg; \*.jpeg; \*.png) files
- Built-in hex editor for binary files

### Downloads
Please head over to [Releases](https://github.com/vaibhavpandeyvpz/apkstudio/releases) page for downloading. **Important:** Make sure to have `JAVA_HOME` environment variable pointing to a valid java installation for *jadx* to be able to run.

### Building
Information on building from source is provided in the [Wiki](https://github.com/vaibhavpandeyvpz/apkstudio/wiki).

### Credits
- [iBotPeaches](https://github.com/iBotPeaches) for [apktool](https://ibotpeaches.github.io/Apktool)
- [patrickfav](https://github.com/patrickfav) for [uber-apk-signer](https://github.com/patrickfav/uber-apk-signer)
- [skylot](https://github.com/skylot) for [jadx](https://github.com/skylot/jadx)
- [probonopd](https://github.com/probonopd) for [linuxdeployqt](https://github.com/probonopd/linuxdeployqt)
- [Jürgen Skrotzky](https://github.com/Jorgen-VikingGod) for [Qt-Frameless-Window-DarkStyle](https://github.com/Jorgen-VikingGod/Qt-Frameless-Window-DarkStyle)
- [Antonio Davide](https://github.com/Dax89) for [QHexView](https://github.com/Dax89/QHexView)
- [p.yusukekamiyamane](https://p.yusukekamiyamane.com/) for [Fugue](https://p.yusukekamiyamane.com/) icons
- [Icons8](https://icons8.com/) for various icons
- [Surendrajat](https://github.com/Surendrajat) for maintaining project while I couldn't

**Note**: If you encounter any problems, make sure to check **Console** output at the bottom of the IDE to get the output of command which was actually executed by program. Report any issues related to APK Studio [here](https://github.com/vaibhavpandeyvpz/apkstudio/issues) on Github. Please note, an issue with [apktool](http://ibotpeaches.github.io/Apktool/) is not an issue with **APK Studio**. Please verify the context of issue before opening a ticket.

---

##### Disclaimer
Same as [apktool](http://ibotpeaches.github.io/Apktool/), **APK Studio** is neither intended for piracy nor other non-legal uses. It could be used for localizing, adding some features or support for custom platforms, analyzing applications &amp; much more.
