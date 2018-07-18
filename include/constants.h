#ifndef CONSTANTS_H
#define CONSTANTS_H

#define APP_NAME "apkstudio/qt5"
#define APP_ORGANIZATION "vaibhavpandeyvpz"

#define CLI_TIMEOUT 5 * 60 * 1000

#define COLOR_CODE 0x2ad2c9
#define COLOR_COMMAND 0xd0d2d3
#define COLOR_OUTPUT 0xffffff
#define COLOR_ERROR 0xfb0a2a

#define EDITOR_EXT_CODER "java|smali|xml|yml|txt|md|SF|properties|clj|MF|crt|json"
#define EDITOR_EXT_VIEWER "gif|jpg|jpeg|png"

#define FILE_PREFERENCES "preferences.ini"

#define FOLDER_APP ".apkstudio"
#define FOLDER_VENDOR "vendor"

#define HIGHLIGHTER_THEME "default.theme"
#define HIGHLIGHTER_STYLE_WHITESPACES "whitespaces"

#define PREF_DEFAULT_JAVA_HEAP 256
#define PREF_DEFAULT_TAB_STOP_WIDTH 4
#define PREF_DEFAULT_TEXT_ENCODING "UTF-8"

#define PREF_DOCKS_STATE "DocksState"
#define PREF_JAVA_HEAP "JavaHeap"
#define PREF_PREVIOUS_DIR "PreviousDir"
#define PREF_SESSION_PROJECT "SessionProject"
#define PREF_SESSION_FILES "SessionFiles"
#define PREF_SHOW_WHITESPACES "ShowWhitespaces"
#define PREF_SIGN_KEY "SignKey"
#define PREF_SIGN_KEY_PASS "SignKeyPass"
#define PREF_SIGN_KEYSTORE "SignKeyStore"
#define PREF_SIGN_KEYSTORE_PASS "SignKeyStorePass"
#define PREF_SPACES_FOR_TABS "SpacesForTabs"
#define PREF_TAB_STOP_WIDTH "TabStopWidth"
#define PREF_TEXT_ENCODING "TextEncoding"
#define PREF_VENDOR_PATH "VendorPath"
#define PREF_WINDOW_MAXIMIZED "WindowMaximized"
#define PREF_WINDOW_SIZE "WindowSize"

#define QRC_FONTS ":/fonts/%1.ttf"
#define QRC_HIGHLIGHT ":/highlight/%1"
#define QRC_HTML ":/html/%1.html"
#define QRC_ICONS ":/icons/%1.png"
#define QRC_IMAGES ":/images/%1.%2"
#define QRC_LANG ":/lang/"
#define QRC_STYLES ":/styles/%1.qss"

#define REGEX_LF "[\\r\\n]"
#define REGEX_ADB_VERSION "^.*(\\d+)\\.(\\d+)\\.(\\d+)$"
#define REGEX_APKTOOL_VERSION "^(\\d+)\\.(\\d+)\\.(\\d+)$"
#define REGEX_UBERAPKTOOL_VERSION "^.*(\\d+)\\.(\\d+)\\.(\\d+)$"
#define REGEX_JAVA_VERSION "^.*\"(\\d+)\\.(\\d+)\\.(\\d+)_(\\d+)\"$"
#define REGEX_THEME_STYLE "\\b([a-z]+)\\:\\s*([0-9a-z#]+)\\b"
#define REGEX_WHITESPACE "\\s+"

#define TAB_PROPERTY_PATH "SrcPath"

#define TRANSLATION_CONTEXT "apkstudio"

#define THREADS_MAX 1

#define URL_CONTRIBUTE "https://github.com/vaibhavpandeyvpz/apkstudio"
#define URL_DOCUMENTATION "https://forum.xda-developers.com/showpost.php?p=75831837"
#define URL_ISSUES "https://github.com/vaibhavpandeyvpz/apkstudio/issues"
#define URL_THANKS "https://forum.xda-developers.com/showthread.php?t=3761033"

/**
  * @brief Build flags
  */
// #define NO_NATIVE_DIALOG

#ifndef LINUX_VENDOR_PATH
#define LINUX_VENDOR_PATH "/usr/share/apkstudio/vendor"
#endif

#endif // CONSTANTS_H
