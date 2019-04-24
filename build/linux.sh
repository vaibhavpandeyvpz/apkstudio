#!/usr/bin/env bash

mkdir $TRAVIS_BUILD_DIR-build

cd $TRAVIS_BUILD_DIR-build
qmake CONFIG+=release PREFIX=/usr $TRAVIS_BUILD_DIR
make
make install INSTALL_ROOT=AppDir

wget -c -nv https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage
chmod +x linuxdeployqt*.AppImage
unset QTDIR; unset QT_PLUGIN_PATH; unset LD_LIBRARY_PATH
mkdir -p AppDir/usr/lib/
cp -r /usr/lib/x86_64-linux-gnu/nss AppDir/usr/lib/
./linuxdeployqt*.AppImage AppDir/usr/share/applications/apkstudio.desktop -appimage -extra-plugins=iconengines,platformthemes/libqgtk3.so

if [ ! -z $TRAVIS_TAG ]; then
  mv ApkStudio-x86_64.AppImage ApkStudio-$TRAVIS_TAG-x86_64.AppImage
fi
mkdir -p $TRAVIS_BUILD_DIR/deploy
mv ApkStudio*AppImage $TRAVIS_BUILD_DIR/deploy/
