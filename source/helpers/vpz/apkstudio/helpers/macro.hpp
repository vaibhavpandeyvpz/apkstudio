#ifndef VPZ_APKSTUDIO_HELPERS_MACRO_HPP
#define VPZ_APKSTUDIO_HELPERS_MACRO_HPP

#define APKS_MENUITEM(toggles, toggle, menu, name, slot, shortcut) ({ \
    QAction *name = new QAction(translate("item_" #name), menu); \
    if (toggle) { \
        name->setCheckable(true); \
        name->setChecked(true); \
        name->setObjectName(#name); \
        toggles->addAction(name); \
        connections.append(connect(this, &MenuBar::viewToggled, [ name ] (const char *id, bool visible) { \
            if (QString(#name) == QString(id)) \
                name->setChecked(visible); \
        })); \
    } else \
        connections.append(connect(name, "2triggered()", parent, "1onAction" #slot "()")); \
    if (shortcut != 0) \
        name->setShortcut(shortcut); \
    menu->addAction(name); \
})

#define APKS_TOOLITEM(toolbar, name, png, slot) ({ \
    QAction *action = new QAction(translate("item_" #name), toolbar); \
    action->setIcon(icon("" #png)); \
    toolbar->addAction(action); \
    connections.append(connect(action, "2triggered()", parent, "1onAction" #slot "()")); \
})

#endif // VPZ_APKSTUDIO_HELPERS_MACRO_HPP
