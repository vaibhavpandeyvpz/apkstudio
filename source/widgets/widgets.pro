!include("../apkstudio.pri") {
    error("Unable to locate &/or include apkstudio.pri")
}

# Source files to be included/compiled within target
HEADERS += \
    vpz/apkstudio/widgets/editor.hpp

SOURCES += \
    vpz/apkstudio/widgets/editor.cpp
