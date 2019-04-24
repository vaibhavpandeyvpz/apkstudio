#!/usr/bin/env bash

mkdir $TRAVIS_BUILD_DIR-build

cd $TRAVIS_BUILD_DIR-build
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

if [ ! -z $TRAVIS_TAG ]; then
  mv ApkStudio-x86_64.dmg ApkStudio-$TRAVIS_TAG-x86_64.dmg
fi
mkdir -p $TRAVIS_BUILD_DIR/deploy
mv ApkStudio*dmg $TRAVIS_BUILD_DIR/deploy/
