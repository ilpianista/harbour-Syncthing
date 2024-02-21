#ifndef SYNCLIENT_H
#define SYNCLIENT_H

#include <QMap>
#include <QObject>

class QNetworkAccessManager;

class Folder;
class FolderStats;

class SynClient : public QObject
{
    Q_OBJECT
public:
    explicit SynClient(QObject *parent = nullptr);
    virtual ~SynClient();

    Q_INVOKABLE bool getHealth();

    QList<Folder *> getFolders();
    double getUptime();

private:
    void getFolderStats();

    QNetworkAccessManager *network;
    QList<Folder *> m_folders;
    QMap<QString, FolderStats*> m_folderstats;
};

#endif // SYNCLIENT_H
