#include "settings.h"

#include <QCoreApplication>
#include <QDir>
#include <QSettings>
#include <QStandardPaths>

Settings::Settings(QObject *parent)
    : QObject(parent)
{
    const QString settingsPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)
                                 + QDir::separator() + QCoreApplication::applicationName()
                                 + ".conf";
    QSettings settings(settingsPath, QSettings::NativeFormat, this);
    m_keepRunning = settings.value(QStringLiteral("keepRunning"), false).toBool();
}

bool Settings::keepRunning() const
{
    return m_keepRunning;
}

void Settings::setKeepRunning(bool keepRunning)
{
    if (m_keepRunning == keepRunning) {
        return;
    }

    m_keepRunning = keepRunning;

    const QString settingsPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)
                                 + QDir::separator() + QCoreApplication::applicationName()
                                 + ".conf";
    QSettings settings(settingsPath, QSettings::NativeFormat, this);
    settings.setValue(QStringLiteral("keepRunning"), m_keepRunning);

    emit keepRunningChanged();
}
