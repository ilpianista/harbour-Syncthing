/*
  The MIT License (MIT)

  Copyright (c) 2015-2021 Andrea Scarpino <andrea@scarpino.dev>

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

#include "foldermodel.h"

#include <QDebug>

#include "folder.h"
#include "folderstats.h"
#include "synclient.h"

FolderModel::FolderModel(QObject *parent) :
    QAbstractListModel(parent)
  , client(new SynClient(this))
{
    getFolders();
}

FolderModel::~FolderModel()
{
    if (!backing.isEmpty()) {
        qDeleteAll(backing);
        backing.clear();
    }

    delete client;
}

QHash<int, QByteArray> FolderModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[LabelRole] = "label";
    roles[PathRole] = "path";
    roles[LastFileAtRole] = "lastFileAt";
    roles[LastFileFilenameRole] = "lastFileFilename";
    roles[LastFileDeletedRole] = "lastFileDeleted";
    roles[LastScanRole] = "lastScan";
    return roles;
}

void FolderModel::getFolders()
{
    Q_FOREACH(Folder *f, client->getFolders()) {
        beginInsertRows(QModelIndex(), backing.size(), backing.size());
        qDebug() << "Adding" << f->path();
        backing.append(f);
        endInsertRows();
    }
}

QVariant FolderModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    Folder *folder = backing[index.row()];
    switch (role) {
        case IdRole: return folder->id();
        case LabelRole: return folder->label();
        case PathRole: return folder->path();
        case LastFileAtRole: return folder->stats()->lastFileAt();
        case LastFileFilenameRole: return folder->stats()->lastFileFilename();
        case LastFileDeletedRole: return folder->stats()->lastFileDeleted();
        case LastScanRole: return folder->stats()->lastScan();
        default: qCritical() << "Unrecognized role" << role;
    }

    return QVariant();
}
