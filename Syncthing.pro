TARGET = harbour-syncthing

CONFIG += sailfishapp

SOURCES += \
    src/folder.cpp \
    src/foldermodel.cpp \
    src/folderstats.cpp \
    src/main.cpp \
    src/synclient.cpp \
    src/synutils.cpp

OTHER_FILES += \
    qml/cover/CoverPage.qml \
    qml/pages/FolderDelegate.qml \
    qml/pages/MainPage.qml \
    qml/Syncthing.qml \
    harbour-syncthing.desktop \
    rpm/harbour-syncthing.changes \
    rpm/harbour-syncthing.spec \
    rpm/syncthing.service \
    translations/*.ts

CONFIG += sailfishapp_i18n
TRANSLATIONS += \
    translations/harbour-syncthing-it.ts

HEADERS += \
    src/folder.h \
    src/folder_p.h \
    src/foldermodel.h \
    src/folderstats.h \
    src/folderstats_p.h \
    src/synclient.h \
    src/synutils.h

QT += xml
