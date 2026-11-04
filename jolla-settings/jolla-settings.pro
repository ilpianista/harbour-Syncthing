TEMPLATE = aux

settings-entry.path = /usr/share/jolla-settings/entries
settings-entry.files = entries/syncthing.json

settings-ui.path = /usr/share/jolla-settings/pages/syncthing
settings-ui.files = pages/syncthing/mainpage.qml

INSTALLS += settings-entry settings-ui

lupdate_only {
    SOURCES += pages/*/*.qml
}

TRANSLATIONS += translations/settings-syncthing.ts

include(translations/translations.pri)
