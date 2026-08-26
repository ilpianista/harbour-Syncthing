#ifndef SYNCLIENT_H
#define SYNCLIENT_H

#include <QMap>
#include <QObject>

class QNetworkAccessManager;

class Folder;
class FolderStats;
class FolderStatus;

class SynClient : public QObject
{
    Q_OBJECT
public:
    explicit SynClient(QObject *parent = nullptr);
    virtual ~SynClient();

    Q_INVOKABLE bool getHealth();

    QList<Folder *> getFolders();

private:
    FolderStatus *getFolderStatus(const QString folderId);
    QMap<QString, FolderStats *> getFolderStats();

    QNetworkAccessManager *network;
};

#endif // SYNCLIENT_H
