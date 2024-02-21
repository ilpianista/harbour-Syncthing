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

#include "folder.h"
#include "folderstats.h"

#include "folder_p.h"

Folder::Folder(QObject *parent) : QObject(parent)
  , d(new FolderPrivate)
{
    d->stats = new FolderStats(this);
}

Folder::~Folder()
{
    delete d->stats;
    delete d;
}

QString Folder::id() const
{
    return d->id;
}

void Folder::setId(const QString id)
{
    d->id = id;
}

QString Folder::label() const
{
    return d->label;
}

void Folder::setLabel(const QString label)
{
    d->label = label;
}

QString Folder::path() const
{
    return d->path;
}

void Folder::setPath(const QString path)
{
    d->path = path;
}

bool Folder::paused() const
{
    return d->paused;
}

void Folder::setPaused(const bool paused)
{
    d->paused = paused;
}

FolderStats* Folder::stats()
{
    return d->stats;
}

void Folder::setStats(FolderStats* stats)
{
    d->stats = stats;
}
