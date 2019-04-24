@echo off
setlocal EnableExtensions

mkdir "%APPVEYOR_BUILD_FOLDER%-build"

qmake CONFIG+=release -o "%APPVEYOR_BUILD_FOLDER%-build" "%APPVEYOR_BUILD_FOLDER%"
cd /d "%APPVEYOR_BUILD_FOLDER%-build"
nmake

set "DEPLOYMENT_DIR=%TEMP%\ApkStudio-%RANDOM%.tmp"
mkdir %DEPLOYMENT_DIR%
xcopy "%APPVEYOR_BUILD_FOLDER%-build\release\ApkStudio.exe" %DEPLOYMENT_DIR%\
windeployqt "%DEPLOYMENT_DIR%\ApkStudio.exe" --release
mkdir %APPVEYOR_BUILD_FOLDER%\deploy

set SETUP_FILE_PREFIX=ApkStudio-
if not %APPVEYOR_REPO_TAG_NAME% == "" set SETUP_FILE_PREFIX=%SETUP_FILE_PREFIX%-%APPVEYOR_REPO_TAG_NAME%
iscc /O"%APPVEYOR_BUILD_FOLDER%\deploy" /F"%SETUP_FILE_PREFIX%-%VCARCH%" "%APPVEYOR_BUILD_FOLDER%\resources\apkstudio.iss"
