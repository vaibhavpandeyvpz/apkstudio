@echo off
setlocal EnableExtensions

mkdir "%APPVEYOR_BUILD_FOLDER%-build"

qmake CONFIG+=release -o "%APPVEYOR_BUILD_FOLDER%-build" "%APPVEYOR_BUILD_FOLDER%"
cd /d "%APPVEYOR_BUILD_FOLDER%-build"
nmake
cd /d "%APPVEYOR_BUILD_FOLDER%"

set "DEPLOYMENT_DIR=%TEMP%\ApkStudio-%RANDOM%.tmp"
mkdir %DEPLOYMENT_DIR%
xcopy "%APPVEYOR_BUILD_FOLDER%-build\release\ApkStudio.exe" %DEPLOYMENT_DIR%\
windeployqt "%DEPLOYMENT_DIR%\ApkStudio.exe" --release
mkdir %APPVEYOR_BUILD_FOLDER%\deploy
iscc /O"%APPVEYOR_BUILD_FOLDER%\deploy" /F"ApkStudio-%VCARCH%" "%APPVEYOR_BUILD_FOLDER%\resources\apkstudio.iss"
