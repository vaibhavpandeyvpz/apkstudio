#ifndef VPZ_APKSTUDIO_HELPERS_MACRO_HPP
#define VPZ_APKSTUDIO_HELPERS_MACRO_HPP

#define APKS_MENUITEM(toggles, toggle, parent, name, slot, shortcut) ({ \
    QAction *action = new QAction(translate("item_" #name), parent); \
    if (toggle) { \
        action->setCheckable(true); \
        action->setChecked(true); \
        toggles->addAction(action); \
    } else \
        connect(action, "2triggered()", parentWidget(), "1onAction" #slot "()"); \
    if (shortcut != 0) \
        action->setShortcut(shortcut); \
    parent->addAction(action); \
})

#define APKS_TOOLITEM(parent, name, png, slot) ({ \
    QAction *action = new QAction(translate("item_" #name), parent); \
    action->setIcon(VPZ::APKStudio::Resources::Embedded::icon("" #png)); \
    parent->addAction(action); \
    connect(action, "2triggered()", parentWidget(), "1onAction" #slot "()"); \
})

#endif // VPZ_APKSTUDIO_HELPERS_MACRO_HPP
