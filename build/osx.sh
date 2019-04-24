#!/usr/bin/env bash

DIR_BUILD=$TRAVIS_BUILD_DIR-build
mkdir $DIR_BUILD

cd $DIR_BUILD
qmake CONFIG+=release $TRAVIS_BUILD_DIR
make

openssl enc -d -aes-256-cbc -in $TRAVIS_BUILD_DIR/resources/macos.cer -out macos.plain.cer -k $SECRET_KEY
openssl enc -d -aes-256-cbc -in $TRAVIS_BUILD_DIR/resources/macos.p12 -out macos.plain.p12 -k $SECRET_KEY
security create-keychain -p travis apkstudio-osx.keychain
security default-keychain -s apkstudio-osx.keychain
security unlock-keychain -p travis apkstudio-osx.keychain
security import $TRAVIS_BUILD_DIR/resources/apple.cer -k ~/Library/Keychains/apkstudio-osx.keychain -T /usr/bin/codesign
security import macos.plain.cer -k ~/Library/Keychains/apkstudio-osx.keychain -T /usr/bin/codesign
security import macos.plain.p12 -k ~/Library/Keychains/apkstudio-osx.keychain -P $OSX_SIGNING_KEY -T /usr/bin/codesign
security set-key-partition-list -S apple-tool:,apple: -s -k travis apkstudio-osx.keychain

cd $TRAVIS_BUILD_DIR-build
macdeployqt ApkStudio.app -codesign="$OSX_SIGNING_IDENTITY"
spctl -a -vvvv ApkStudio.app

DMG_DIR_NAME=ApkStudio
if [ -d $DMG_DIR_NAME ]; then
  rm -rf $DMG_DIR_NAME
fi
mkdir $DMG_DIR_NAME
mv ApkStudio.app $DMG_DIR_NAME/
ln -s /Applications $DMG_DIR_NAME/Applications
hdiutil create -format UDZO -srcfolder $DMG_DIR_NAME ApkStudio-x86_64.dmg
codesign -s "$OSX_SIGNING_IDENTITY" ApkStudio.dmg
spctl -a --context context:primary-signature -t open -vvvv ApkStudio-x86_64.dmg
security delete-keychain apkstudio-osx.keychain

mkdir -p $TRAVIS_BUILD_DIR/deploy
mv ApkStudio-x86_64.dmg $TRAVIS_BUILD_DIR/deploy/
