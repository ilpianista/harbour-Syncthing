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

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "synutils.h"

const static QString BASE_URL = QStringLiteral("http://localhost:8384");

SynClient::SynClient(QObject *parent) :
    QObject(parent)
  , network(new QNetworkAccessManager(this))
{

}

SynClient::~SynClient()
{
    delete network;
}

double SynClient::getUptime() const
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
