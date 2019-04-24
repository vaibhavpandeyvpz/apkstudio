#!/usr/bin/env bash

DIR_BUILD=$TRAVIS_BUILD_DIR-build
mkdir $DIR_BUILD

cd $DIR_BUILD
qmake CONFIG+=release $TRAVIS_BUILD_DIR
make

cd $TRAVIS_BUILD_DIR-build
macdeployqt ApkStudio.app

DMG_DIR_NAME=ApkStudio
if [ -d $DMG_DIR_NAME ]; then
  rm -rf $DMG_DIR_NAME
fi
mkdir $DMG_DIR_NAME
mv ApkStudio.app $DMG_DIR_NAME/
ln -s /Applications $DMG_DIR_NAME/Applications
hdiutil create -format UDZO -srcfolder $DMG_DIR_NAME ApkStudio-x86_64.dmg

mkdir -p $TRAVIS_BUILD_DIR/deploy
mv ApkStudio-x86_64.dmg $TRAVIS_BUILD_DIR/deploy/
