/*
  The MIT License (MIT)

  Copyright (c) 2023 Andrea Scarpino <andrea@scarpino.dev>

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

#ifndef FOLDERSTATS_H
#define FOLDERSTATS_H

#include <QDateTime>
#include <QObject>
#include <QString>

class FolderStatsPrivate;

class FolderStats : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDateTime lastFileAt READ lastFileAt)
    Q_PROPERTY(QString lastFileFilename READ lastFileFilename)
    Q_PROPERTY(bool lastFileDeleted READ lastFileDeleted)
    Q_PROPERTY(QDateTime lastScan READ lastScan)

public:
    explicit FolderStats(QObject *parent = 0);
    virtual ~FolderStats();

    QDateTime lastFileAt() const;
    void setLastFileAt(const QDateTime at);

    QString lastFileFilename() const;
    void setLastFileFilename(const QString filename);

    bool lastFileDeleted() const;
    void setLastFileDeleted(const bool deleted);

    QDateTime lastScan() const;
    void setLastScan(const QDateTime lastScan);

private:
    FolderStatsPrivate *d;

};

#endif // FOLDERSTATS_H
