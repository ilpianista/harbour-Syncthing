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

#include <QBuffer>
#include <QEventLoop>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMetaEnum>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>

#include "folder.h"
#include "folderstats.h"
#include "folderstatus.h"
#include "synutils.h"

const static QString BASE_URL = QStringLiteral("http://localhost:8384");

SynClient::SynClient(QObject *parent)
    : QObject(parent)
    , network(new QNetworkAccessManager(this))
{}

SynClient::~SynClient()
{
    delete network;
}

bool SynClient::getHealth()
{
    QNetworkRequest req(QUrl(BASE_URL + QLatin1String("/rest/noauth/health")));

    QNetworkReply *reply = network->get(req);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    bool health = false;
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument json = QJsonDocument::fromJson(reply->readAll());

        if (!json.isNull()) {
            QJsonValue value = json.object().value("status");

            if (!value.isNull()) {
                health = QString::compare(QLatin1String("OK"), value.toString(), Qt::CaseInsensitive)
                         == 0;
            }
        }
    }

    reply->deleteLater();

    return health;
}

QList<Folder *> SynClient::getFolders()
{
    QList<Folder *> folders;

    QNetworkRequest req(QUrl(BASE_URL + QLatin1String("/rest/config/folders")));
    req.setRawHeader(QByteArray("X-API-Key"), SynUtils::getApiKey().toLatin1());

    QNetworkReply *reply = network->get(req);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QMap<QString, FolderStats *> folderstats = getFolderStats();

    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument json = QJsonDocument::fromJson(reply->readAll());

        if (!json.isNull()) {
            Q_FOREACH (const QJsonValue obj, json.array()) {
                QJsonObject folder = obj.toObject();

                Folder *f = new Folder();
                f->setId(folder.value("id").toString());
                f->setLabel(folder.value("label").toString());
                f->setPath(folder.value("path").toString());
                f->setPaused(folder.value("paused").toBool());
                FolderStats *stats = folderstats.take(f->id());
                if (stats) {
                    f->setStats(stats);
                }
                f->setStatus(getFolderStatus(f->id()));

                folders.append(f);
            }
        }
    }

    qDeleteAll(folderstats);

    reply->deleteLater();

    return folders;
}

void SynClient::setFolderPaused(const QString &id, bool paused)
{
    QUrl url(BASE_URL + QLatin1String("/rest/config/folders/") + id);

    QNetworkRequest req(url);
    req.setRawHeader(QByteArray("X-API-Key"), SynUtils::getApiKey().toLatin1());
    req.setHeader(QNetworkRequest::ContentTypeHeader, QLatin1String("application/json"));

    QJsonObject body;
    body.insert(QStringLiteral("paused"), paused);

    QByteArray data = QJsonDocument(body).toJson();
    QBuffer buffer(&data);
    buffer.open(QIODevice::ReadOnly);
    QNetworkReply *reply = network->sendCustomRequest(req, QByteArrayLiteral("PATCH"), &buffer);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    reply->deleteLater();
}

QMap<QString, FolderStats *> SynClient::getFolderStats()
{
    QMap<QString, FolderStats *> folderstats;

    QNetworkRequest req(QUrl(BASE_URL + QLatin1String("/rest/stats/folder")));
    req.setRawHeader(QByteArray("X-API-Key"), SynUtils::getApiKey().toLatin1());

    QNetworkReply *reply = network->get(req);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument json = QJsonDocument::fromJson(reply->readAll());

        if (!json.isNull()) {
            QJsonObject list = json.object();

            Q_FOREACH (const QString folder, list.keys()) {
                QJsonObject folderstatsObj = list.value(folder).toObject();
                QJsonObject lastFile = folderstatsObj.value("lastFile").toObject();

                FolderStats *f = new FolderStats();
                f->setLastFileAt(
                    QDateTime::fromString(lastFile.value("at").toString(), Qt::ISODate));
                f->setLastFileFilename(lastFile.value("filename").toString());
                f->setLastFileDeleted(lastFile.value("deleted").toBool());
                f->setLastScan(QDateTime::fromString(folderstatsObj.value("lastScan").toString(),
                                                     Qt::ISODate));

                folderstats.insert(folder, f);
            }
        }
    }

    reply->deleteLater();

    return folderstats;
}

FolderStatus *SynClient::getFolderStatus(const QString folderId)
{
    FolderStatus *s = new FolderStatus();

    QUrl url(BASE_URL + QLatin1String("/rest/db/status"));
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("folder"), folderId);
    url.setQuery(query);

    QNetworkRequest req(url);
    req.setRawHeader(QByteArray("X-API-Key"), SynUtils::getApiKey().toLatin1());

    QNetworkReply *reply = network->get(req);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument json = QJsonDocument::fromJson(reply->readAll());

        if (!json.isNull()) {
            QJsonObject status = json.object();

            QString value = status.value("state").toString();

            if (value.length() > 0) {
                value.replace(0, 1, value.at(0).toUpper());

                int dash = value.indexOf("-");
                if (dash > 0) {
                    value.remove("-");
                    value.replace(dash, 1, value.at(dash).toUpper());
                }

                auto &&metaEnum = QMetaEnum::fromType<FolderStatus::FolderState>();
                s->setState(static_cast<FolderStatus::FolderState>(
                    metaEnum.keyToValue(value.toLocal8Bit())));
            }
        }
    }

    reply->deleteLater();

    return s;
}
