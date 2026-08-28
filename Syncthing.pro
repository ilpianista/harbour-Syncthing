TARGET = harbour-syncthing

CONFIG += sailfishapp

SOURCES += \
    src/folder.cpp \
    src/foldermodel.cpp \
    src/folderstats.cpp \
    src/folderstatus.cpp \
    src/main.cpp \
    src/settings.cpp \
    src/synclient.cpp \
    src/synutils.cpp

OTHER_FILES += \
    qml/cover/CoverPage.qml \
    qml/cover/FolderCoverDelegate.qml \
    qml/pages/FolderDelegate.qml \
    qml/pages/MainPage.qml \
    qml/pages/SettingsPage.qml \
    qml/Syncthing.qml \
    harbour-syncthing.desktop \
    rpm/harbour-syncthing.changes \
    rpm/harbour-syncthing.spec \
    rpm/syncthing.service \
    translations/*.ts

CONFIG += sailfishapp_i18n
TRANSLATIONS += \
    translations/harbour-syncthing-et.ts \
    translations/harbour-syncthing-it.ts \
    translations/harbour-syncthing-nb_NO.ts \
    translations/harbour-syncthing-nl.ts \
    translations/harbour-syncthing-sv.ts

HEADERS += \
    src/folder.h \
    src/folder_p.h \
    src/foldermodel.h \
    src/folderstats.h \
    src/folderstats_p.h \
    src/folderstatus.h \
    src/folderstatus_p.h \
    src/settings.h \
    src/synclient.h \
    src/synutils.h

QT += xml
