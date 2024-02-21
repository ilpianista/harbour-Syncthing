/*
  The MIT License (MIT)

  Copyright (c) 2021 Andrea Scarpino <andrea@scarpino.dev>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "synclient.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "folder.h"
#include "folderstats.h"
#include "synutils.h"

const static QString BASE_URL = QStringLiteral("http://localhost:8384");

SynClient::SynClient(QObject *parent) :
    QObject(parent)
  , network(new QNetworkAccessManager(this))
  , m_folders()
  , m_folderstats()
{
}

SynClient::~SynClient()
{
    delete network;
    qDeleteAll(m_folders);
    qDeleteAll(m_folderstats);
}

bool SynClient::getHealth()
{
    QNetworkRequest req(QUrl(BASE_URL + QLatin1String("/rest/noauth/health")));

    QNetworkReply* reply = network->get(req);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    bool health = false;
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument json = QJsonDocument::fromJson(reply->readAll());

        if (!json.isNull()) {
            QJsonValue value = json.object().value("status");

            if (!value.isNull()) {
                health = QString::compare(QLatin1String("OK"), value.toString(), Qt::CaseInsensitive) == 0;
            }
        }
    }

    reply->deleteLater();

    return health;
}

double SynClient::getUptime()
{
    QNetworkRequest req(QUrl(BASE_URL + QLatin1String("/rest/system/status")));
    req.setRawHeader(QByteArray("X-API-Key"), SynUtils::getApiKey().toLatin1());

    QNetworkReply* reply = network->get(req);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    double uptime = 0.0;
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument json = QJsonDocument::fromJson(reply->readAll());

        if (!json.isNull()) {
            QJsonValue value = json.object().value("uptime");

            if (!value.isNull()) {
                uptime = value.toDouble();
            }
        }
    }

    reply->deleteLater();

    return uptime;
}

QList<Folder*> SynClient::getFolders()
{
    QNetworkRequest req(QUrl(BASE_URL + QLatin1String("/rest/config/folders")));
    req.setRawHeader(QByteArray("X-API-Key"), SynUtils::getApiKey().toLatin1());

    QNetworkReply* reply = network->get(req);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    getFolderStats();

    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument json = QJsonDocument::fromJson(reply->readAll());

        if (!json.isNull()) {
            Q_FOREACH(const QJsonValue obj, json.array()) {
                QJsonObject folder = obj.toObject();

                Folder *f = new Folder();
                f->setId(folder.value("id").toString());
                f->setLabel(folder.value("label").toString());
                f->setPath(folder.value("path").toString());
                f->setPaused(folder.value("paused").toBool());
                f->setStats(m_folderstats.value(f->id()));

                m_folders.append(f);
            }
        }
    }

    reply->deleteLater();

    return m_folders;
}

void SynClient::getFolderStats()
{
    QNetworkRequest req(QUrl(BASE_URL + QLatin1String("/rest/stats/folder")));
    req.setRawHeader(QByteArray("X-API-Key"), SynUtils::getApiKey().toLatin1());

    QNetworkReply* reply = network->get(req);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument json = QJsonDocument::fromJson(reply->readAll());

        if (!json.isNull()) {
            QJsonObject list = json.object();

            Q_FOREACH(const QString folder, list.keys()) {
                QJsonObject folderstats = list.value(folder).toObject();
                QJsonObject lastFile = folderstats.value("lastFile").toObject();

                FolderStats *f = new FolderStats();
                f->setLastFileAt(QDateTime::fromString(lastFile.value("at").toString(), Qt::ISODate));
                f->setLastFileFilename(lastFile.value("filename").toString());
                f->setLastFileDeleted(lastFile.value("deleted").toBool());
                f->setLastScan(QDateTime::fromString(folderstats.value("lastScan").toString(), Qt::ISODate));

                m_folderstats.insert(folder, f);
            }
        }
    }

    reply->deleteLater();
}
