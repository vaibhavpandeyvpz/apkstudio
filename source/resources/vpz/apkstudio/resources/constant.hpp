#ifndef VPZ_APKSTUDIO_RESOURCES_CONSTANT_HPP
#define VPZ_APKSTUDIO_RESOURCES_CONSTANT_HPP

#define EXIT_CODE_RESTART 60600

#define APPLICATION_AUTHOR "Vaibhav Pandey"
#define APPLICATION_NAME "APK Studio"

#define ALLOWED_IMAGE_EXTENSIONS "png"
#define ALLOWED_TEXT_EXTENSIONS "java|smali|xml"

#define FORMAT_TIMESTAMP_FILE "dd-MM-yyyy_hh_mm_ss"
#define FORMAT_TIMESTAMP_GENERAL "dd/MM/yyyy hh:mm"

#define REGEX_APPLICATION "^package:(?<path>.+?)=(?<package>.+)$"
#define REGEX_EMULATOR "emulator-(?<port>\\d+)"
#define REGEX_GETPROP "^\\[(?<key>[^]]+)\\]\\:\\s*\\[(?<value>.*)\\]$"
#define REGEX_IMEI "\\s=\\s"
#define REGEX_LOGCAT "^(?<time>\\d\\d-\\d\\d\\s\\d\\d:\\d\\d:\\d\\d\\.\\d+)\\s*(?<pid>\\d+)\\s*(?<tid>\\d+)\\s(?<priority>[VDIWEAF])\\s(?<tag>.*?):\\s+(?<message>.*)$"
#define REGEX_LS "^(?<permission>[bcdlsp-][-r][-w][-xsS][-r][-w][-xsS][-r][-w][-xstST])\\s+(?<owner>\\S+)\\s+(?<group>\\S+)\\s+(?<size>[\\d\\s,]*)\\s+(?<date>\\d{4}-\\d\\d-\\d\\d)\\s+(?<time>\\d\\d:\\d\\d)\\s+(?<name>.*)$"
#define REGEX_PAIR "([0-9a-zA-Z_]+)=([0-9a-zA-Z\\-]+[^,\\s])"

#define RESOURCE_PATH_FONT ":/font/"
#define RESOURCE_PATH_HIGHLIGHT ":/highlight/"
#define RESOURCE_PATH_ICON ":/icon/"
#define RESOURCE_PATH_LANGUAGE ":/language/"
#define RESOURCE_PATH_THEME ":/theme/"

#define ROLE_PATH 70552
#define ROLE_STRUCT 43396
#define ROLE_TEXT 60600
#define ROLE_TYPE 25184

#define SETTING_BINARY_PATH "binary_path"
#define SETTING_CHARACTER_ENCODING "character_encoding"
#define SETTING_CURSOR_WIDTH "cursor_width"
#define SETTING_DOCK_STATE "dock_state"
#define SETTING_FONT_FAMILY "font_family"
#define SETTING_FONT_SIZE "font_size"
#define SETTING_FRAMEWORK_PATH "framework_path"
#define SETTING_HEAP_SIZE "heap_size"
#define SETTING_IMAGE_BACKGROUND "image_background"
#define SETTING_JAVA_HOME "java_home"
#define SETTING_LANGUAGE "language"
#define SETTING_MAXIMIZED "maximized"
#define SETTING_PREVIOUS_DIRECTORY "previous_directory"
#define SETTING_RECENT_FILES "recent_files"
#define SETTING_ROOT_SHELL "root_shell"
#define SETTING_SHOW_WHITESPACE "show_whitespace"
#define SETTING_SIGNING_CERTIFICATE "signing_certificate"
#define SETTING_SIGNING_KEY "signing_key"
#define SETTING_SPACES_FOR_TAB "spaces_for_tab"
#define SETTING_TAB_WIDTH "tab_width"
#define SETTING_THEME "theme"
#define SETTING_WORD_WRAP "word_wrap"
#define SETTING_WINDOW_SIZE "window_size"

#define STYLESHEET_COMBOBOXES "QComboBox { max-height: 22px; min-height: 22px; }"
#define STYLESHEET_PREFIXED "QLineEdit { font-size: 12px; height: 22px; padding-right: %1px; } "

#define TYPE_FILE 88004
#define TYPE_FOLDER 85273
#define TYPE_PROJECT 95999

#define URL_CONTRIBUTE "https://github.com/vaibhavpandeyvpz/apkstudio"
#define URL_DONATE "https://pledgie.com/campaigns/26789"
#define URL_ISSUES "https://github.com/vaibhavpandeyvpz/apkstudio/issues"
#define URL_THANKS "http://forum.xda-developers.com/showthread.php?t=2493107"

#endif // VPZ_APKSTUDIO_RESOURCES_CONSTANT_HPP
