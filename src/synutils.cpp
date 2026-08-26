#include "synutils.h"

#include <QDebug>
#include <QDir>
#include <QDomDocument>
#include <QFile>
#include <QStandardPaths>

SynUtils::SynUtils() {}

QString SynUtils::getApiKey()
{
    QDomDocument xml;

    QFile configFile(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)
                     + QDir::separator() + "syncthing" + QDir::separator() + "config.xml");

    if (!configFile.open(QIODevice::ReadOnly)) {
        qCritical() << "Error while loading file";
    }

    xml.setContent(&configFile);
    configFile.close();

    return xml.namedItem("configuration").namedItem("gui").namedItem("apikey").toElement().text();
}
