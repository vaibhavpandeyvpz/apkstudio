cmake_minimum_required(VERSION 3.16)

project(ApkStudio VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Gui Network Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Git version info
find_package(Git QUIET)
if(GIT_FOUND)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_FULL
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-list HEAD --count
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_NUMBER
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_SHORT
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
    execute_process(
        COMMAND ${GIT_EXECUTABLE} tag -l --points-at HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_TAG
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
else()
    set(GIT_BRANCH "unknown")
    set(GIT_COMMIT_FULL "unknown")
    set(GIT_COMMIT_NUMBER "0")
    set(GIT_COMMIT_SHORT "unknown")
    set(GIT_TAG "")
endif()

# Add QHexView subdirectory
add_subdirectory(QHexView)
set_target_properties(QHexView PROPERTIES
    QHEXVIEW_ENABLE_DIALOGS ON
)

# Application sources
set(SOURCES
    sources/main.cpp
    sources/adbinstallworker.cpp
    sources/apkdecompiledialog.cpp
    sources/apkdecompileworker.cpp
    sources/apkrecompileworker.cpp
    sources/apksignworker.cpp
    sources/appearancesettingswidget.cpp
    sources/binarysettingswidget.cpp
    sources/desktopdatabaseupdateworker.cpp
    sources/devicelistworker.cpp
    sources/deviceselectiondialog.cpp
    sources/findinfilesdialog.cpp
    sources/findreplacedialog.cpp
    sources/flickcharm.cpp
    sources/hexedit.cpp
    sources/imageviewerwidget.cpp
    sources/keystoregeneratedialog.cpp
    sources/keystoregenerateworker.cpp
    sources/mainwindow.cpp
    sources/processutils.cpp
    sources/settingsdialog.cpp
    sources/signingconfigdialog.cpp
    sources/signingconfigwidget.cpp
    sources/sourcecodeedit.cpp
    sources/splashwindow.cpp
    sources/themedsyntaxhighlighter.cpp
    sources/tooldownloaddialog.cpp
    sources/tooldownloadworker.cpp
    sources/versionresolveworker.cpp
)

set(HEADERS
    sources/adbinstallworker.h
    sources/apkdecompiledialog.h
    sources/apkdecompileworker.h
    sources/apkrecompileworker.h
    sources/apksignworker.h
    sources/appearancesettingswidget.h
    sources/binarysettingswidget.h
    sources/desktopdatabaseupdateworker.h
    sources/devicelistworker.h
    sources/deviceselectiondialog.h
    sources/findinfilesdialog.h
    sources/findreplacedialog.h
    sources/flickcharm.h
    sources/hexedit.h
    sources/imageviewerwidget.h
    sources/keystoregeneratedialog.h
    sources/keystoregenerateworker.h
    sources/mainwindow.h
    sources/processutils.h
    sources/settingsdialog.h
    sources/signingconfigdialog.h
    sources/signingconfigwidget.h
    sources/sourcecodeedit.h
    sources/splashwindow.h
    sources/themedsyntaxhighlighter.h
    sources/tooldownloaddialog.h
    sources/tooldownloadworker.h
    sources/versionresolveworker.h
)

set(RESOURCES
    resources/all.qrc
)

# Create executable
if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS} ${RESOURCES})
elseif(APPLE)
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES} ${HEADERS} ${RESOURCES})
else()
    add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})
endif()

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/sources
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Network
    Qt6::Widgets
    QHexView
)


# Compile definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE
    QT_VERSION_QT6
    GIT_BRANCH="${GIT_BRANCH}"
    GIT_COMMIT_FULL="${GIT_COMMIT_FULL}"
    GIT_COMMIT_NUMBER="${GIT_COMMIT_NUMBER}"
    GIT_COMMIT_SHORT="${GIT_COMMIT_SHORT}"
    GIT_TAG="${GIT_TAG}"
)

# Windows specific
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
    if(EXISTS ${CMAKE_SOURCE_DIR}/resources/icon.ico)
        # Create resource file for icon
        file(WRITE ${CMAKE_BINARY_DIR}/app.rc
            "IDI_ICON1 ICON DISCARDABLE \"${CMAKE_SOURCE_DIR}/resources/icon.ico\"\n"
        )
        target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/app.rc)
    endif()
endif()

# macOS specific
if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
    )
    # Create Info.plist if it doesn't exist
    if(NOT EXISTS ${CMAKE_SOURCE_DIR}/resources/Info.plist)
        file(WRITE ${CMAKE_BINARY_DIR}/Info.plist
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n"
            "<plist version=\"1.0\">\n"
            "<dict>\n"
            "    <key>CFBundleDevelopmentRegion</key>\n"
            "    <string>en</string>\n"
            "    <key>CFBundleExecutable</key>\n"
            "    <string>${PROJECT_NAME}</string>\n"
            "    <key>CFBundleIdentifier</key>\n"
            "    <string>com.vaibhavpandey.apkstudio</string>\n"
            "    <key>CFBundleInfoDictionaryVersion</key>\n"
            "    <string>6.0</string>\n"
            "    <key>CFBundleName</key>\n"
            "    <string>${PROJECT_NAME}</string>\n"
            "    <key>CFBundleDisplayName</key>\n"
            "    <string>APK Studio</string>\n"
            "    <key>CFBundlePackageType</key>\n"
            "    <string>APPL</string>\n"
            "    <key>CFBundleShortVersionString</key>\n"
            "    <string>${PROJECT_VERSION}</string>\n"
            "    <key>CFBundleVersion</key>\n"
            "    <string>${PROJECT_VERSION}</string>\n"
            "    <key>LSMinimumSystemVersion</key>\n"
            "    <string>10.13</string>\n"
            "    <key>NSHighResolutionCapable</key>\n"
            "    <true/>\n"
            "    <key>NSPrincipalClass</key>\n"
            "    <string>NSApplication</string>\n"
            "    <key>LSApplicationCategoryType</key>\n"
            "    <string>public.app-category.developer-tools</string>\n"
            "    <key>NSRequiresAquaSystemAppearance</key>\n"
            "    <false/>\n"
            "    <key>CFBundleIconFile</key>\n"
            "    <string>icon.icns</string>\n"
            "    <key>CFBundleIconName</key>\n"
            "    <string>icon.icns</string>\n"
            "</dict>\n"
            "</plist>\n"
        )
        set_target_properties(${PROJECT_NAME} PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_BINARY_DIR}/Info.plist
        )
    else()
        set_target_properties(${PROJECT_NAME} PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/resources/Info.plist
        )
    endif()
    if(EXISTS ${CMAKE_SOURCE_DIR}/resources/icon.icns)
        set(MACOSX_BUNDLE_ICON_FILE "icon.icns")
        set_target_properties(${PROJECT_NAME} PROPERTIES
            MACOSX_BUNDLE_ICON_FILE ${MACOSX_BUNDLE_ICON_FILE}
        )
        # Copy icon to bundle Resources
        set(APP_ICON_RESOURCE_MACOSX "${CMAKE_SOURCE_DIR}/resources/icon.icns")
        set_source_files_properties(${APP_ICON_RESOURCE_MACOSX} PROPERTIES
            MACOSX_PACKAGE_LOCATION "Resources"
        )
        # Add icon to target so it's included in the bundle
        target_sources(${PROJECT_NAME} PRIVATE ${APP_ICON_RESOURCE_MACOSX})
    endif()
endif()

# Install rules (Unix)
if(UNIX AND NOT APPLE)
    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
    )
    install(FILES resources/icon.png
        DESTINATION share/pixmaps
    )
    install(FILES resources/apkstudio.desktop
        DESTINATION share/applications
    )
endif()

# Install rules (macOS)
if(APPLE)
    install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION .
        RUNTIME DESTINATION bin
    )
endif()

# Set output directories
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
    )
else()
    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
endif()

