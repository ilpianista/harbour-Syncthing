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

#include "folderstats.h"

#include "folderstats_p.h"

FolderStats::FolderStats(QObject *parent) : QObject(parent)
  , d(new FolderStatsPrivate)
{
}

FolderStats::~FolderStats()
{
    delete d;
}

QDateTime FolderStats::lastFileAt() const
{
    return d->lastFileAt;
}

void FolderStats::setLastFileAt(const QDateTime at)
{
    d->lastFileAt = at;
}

QString FolderStats::lastFileFilename() const
{
    return d->lastFileFilename;
}

void FolderStats::setLastFileFilename(const QString filename)
{
    d->lastFileFilename = filename;
}

bool FolderStats::lastFileDeleted() const
{
    return d->lastFileDeleted;
}

void FolderStats::setLastFileDeleted(const bool deleted)
{
    d->lastFileDeleted = deleted;
}

QDateTime FolderStats::lastScan() const
{
    return d->lastScan;
}

void FolderStats::setLastScan(const QDateTime lastScan)
{
    d->lastScan = lastScan;
}
