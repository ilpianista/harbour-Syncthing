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

    Q_INVOKABLE double getUptime() const;

private:
    QNetworkAccessManager *network;

};

#endif // SYNCLIENT_H
