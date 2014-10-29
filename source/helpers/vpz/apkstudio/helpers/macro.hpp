#ifndef VPZ_APKSTUDIO_HELPERS_MACRO_HPP
#define VPZ_APKSTUDIO_HELPERS_MACRO_HPP

#define APKS_MENUITEM(toggles, toggle, parent, name, slot, shortcut) ({ \
    QAction *name = new QAction(translate("item_" #name), parent); \
    if (toggle) { \
        name->setCheckable(true); \
        name->setChecked(true); \
        name->setObjectName(#name); \
        toggles->addAction(name); \
        connections.append(connect(dynamic_cast<IDE *>(parentWidget()), &IDE::viewToggled, [ name ] (const char *id, bool visible) { \
            if (QString(#name) == QString(id)) \
                name->setChecked(visible); \
        })); \
    } else \
        connect(name, "2triggered()", parentWidget(), "1onAction" #slot "()"); \
    if (shortcut != 0) \
        name->setShortcut(shortcut); \
    parent->addAction(name); \
})

#define APKS_TOOLITEM(parent, name, png, slot) ({ \
    QAction *action = new QAction(translate("item_" #name), parent); \
    action->setIcon(icon("" #png)); \
    parent->addAction(action); \
    connect(action, "2triggered()", parentWidget(), "1onAction" #slot "()"); \
})

#endif // VPZ_APKSTUDIO_HELPERS_MACRO_HPP
