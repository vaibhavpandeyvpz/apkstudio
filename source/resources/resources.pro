!include("../apkstudio.pri") {
    error("Unable to locate &/or include apkstudio.pri")
}

# Source files to be included/compiled within target
HEADERS += \
    vpz/apkstudio/resources/constant.hpp \
    vpz/apkstudio/resources/embedded.hpp \
    vpz/apkstudio/resources/variant.hpp

SOURCES += \
    vpz/apkstudio/resources/embedded.cpp \
    vpz/apkstudio/resources/constant.cpp \
    vpz/apkstudio/resources/variant.cpp
