#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool keepRunning READ keepRunning WRITE setKeepRunning NOTIFY keepRunningChanged)

public:
    explicit Settings(QObject *parent = nullptr);

    bool keepRunning() const;
    void setKeepRunning(bool keepRunning);

signals:
    void keepRunningChanged();

private:
    bool m_keepRunning;
};

#endif
