#ifndef SYNCLIENT_H
#define SYNCLIENT_H

#include <QObject>

class QNetworkAccessManager;

class SynClient : public QObject
{
    Q_OBJECT
public:
    explicit SynClient(QObject *parent = nullptr);
    virtual ~SynClient();

    enum SynStatus {
        Running, Stopped
    };
    Q_ENUMS(SynStatus)

    Q_INVOKABLE SynStatus getStatus() const;

private:
    QNetworkAccessManager *network;

};

#endif // SYNCLIENT_H
