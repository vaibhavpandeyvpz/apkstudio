#!/usr/bin/env bash

DIR_BUILD=$TRAVIS_BUILD_DIR-build
mkdir $DIR_BUILD

cd $DIR_BUILD
qmake CONFIG+=release PREFIX=/usr $TRAVIS_BUILD_DIR
make
make install INSTALL_ROOT=AppDir

wget -c -nv https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage
chmod +x linuxdeployqt*.AppImage
unset QTDIR; unset QT_PLUGIN_PATH; unset LD_LIBRARY_PATH
mkdir -p AppDir/usr/lib/
cp -r /usr/lib/x86_64-linux-gnu/nss AppDir/usr/lib/
./linuxdeployqt*.AppImage AppDir/usr/share/applications/apkstudio.desktop -appimage -extra-plugins=iconengines,platformthemes/libqgtk3.so

mkdir -p $TRAVIS_BUILD_DIR/deploy
mv ApkStudio-x86_64.AppImage $TRAVIS_BUILD_DIR/deploy/
