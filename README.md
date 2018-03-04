# APK Studio [![Codacy Badge](https://api.codacy.com/project/badge/Grade/9709de5012824c36b54fda9c2c6390bf)](https://app.codacy.com/app/Surendrajat/apkstudio?utm_source=github.com&utm_medium=referral&utm_content=Surendrajat/apkstudio&utm_campaign=badger) [![Build Status(Linux)](https://travis-ci.org/Surendrajat/apkstudio.svg)](https://travis-ci.org/Surendrajat/apkstudio) [![Build status(Windows)](https://ci.appveyor.com/api/projects/status/mnr254lm0mlshmfb?svg=true)](https://ci.appveyor.com/project/Surendrajat/apkstudio) [![Join the chat at https://gitter.im/apk-studio/ideas](https://badges.gitter.im/apk-studio/ideas.svg)](https://gitter.im/apk-studio/ideas?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
>**APK Studio is a cross-platform IDE for reverse-engineering (decompiling, hacking & rebuilding) of android applications (APKs) within a single user-interface. It features a friendly layout with a code editor which support syntax-highlighting for smali (dalvik-bytecode) code files.**

### Features
- **Decompile** & **Recompile** APKs (Using ***Apktool***)
- Flexible Keystore & Key-Alias Chooser
- Automatic **Zip-align**
- Syntax Highlighting (*.java, *.smali; *.xml; *.yml)
- **Image Viewer** For Resources
- **One-click Install** to Device
- **Framework**s Support

### Download
 >[![Download](https://img.shields.io/github/release/surendrajat/apkstudio/all.svg?longCache=true&style=for-the-badge)](https://github.com/Surendrajat/apkstudio/releases)

### Instructions
- Install **Java** & make sure ```$JAVA_HOME``` points to a valid **JDK** (**JRE** may not work)
- You should also install or have **ADB** in ```$PATH```. This can be done on debian{-based} distros as follows:
	```bash
	sudo apt-get install android-tools-adb
	```
- Download latest [Apktool](https://bitbucket.org/iBotPeaches/apktool/downloads/) and put it in the following path:
	>**linux:** ```/home/{your-user-name}/.apkstudio/vendor/apktool.jar```  
	>**Windows:** ```C:\Users\{your-user-name}\.apkstudio\vendor\apktool.jar```
- Also make sure you've **zipalign** installed. On Ubuntu issue the command:
	```bash
	sudo apt-get install zipalign
	```

	**Note**: If you encounter any problem, make sure to check **Console Output** at bottom of IDE to check what went wrong and report [here](https://github.com/vaibhavpandeyvpz/apkstudio/issues). Also note that an issue with [Apktool](http://ibotpeaches.github.io/Apktool/) is not an issue with **APK Studio**. Please verify the context of issue before opening a ticket.

### Building (Linux)
- Make sure you have **GCC 4.6+**, **QT 5.2+**
	```shell
	sudo apt-get install qt5-default qt4-linguist-tools qt5-qmake qttools5-dev build-essential
	```
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
	 More information on building from source using **Qt Creator** is provided in the [Wiki](https://github.com/surendrajat/apkstudio/wiki)

### TODO
- Replacing **jarsigner** with **apksigner**
- Code Completion

### Screenshots
>![Screenshot #1](https://raw.githubusercontent.com/surendrajat/apkstudio/master/external/screenshots/apkstudio000.png "Screenshot #1")

>![Screenshot #2](https://raw.githubusercontent.com/surendrajat/apkstudio/master/external/screenshots/apkstudio002.png "Screenshot #2")

### Disclaimer
>Same as [Apktool](http://ibotpeaches.github.io/Apktool/), **APK Studio** is neither intended for piracy nor other non-legal uses. It could be used for localizing, adding some features or support for custom platforms, analyzing applications &amp; much more.