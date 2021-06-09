TARGET = harbour-syncthing

CONFIG += sailfishapp

SOURCES += \
    src/main.cpp \
    src/synclient.cpp \
    src/synutils.cpp

OTHER_FILES += \
    qml/cover/CoverPage.qml \
    qml/pages/MainPage.qml \
    qml/Syncthing.qml \
    harbour-syncthing.desktop \
    rpm/harbour-syncthing.changes \
    rpm/harbour-syncthing.spec \
    rpm/harbour-syncthing.yaml \
    rpm/syncthing.service \
    translations/*.ts

CONFIG += sailfishapp_i18n
TRANSLATIONS += \
    translations/harbour-syncthing-it.ts

HEADERS += \
    src/synclient.h \
    src/synutils.h

QT += xml
