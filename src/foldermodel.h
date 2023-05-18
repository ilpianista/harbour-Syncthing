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

#ifndef FOLDERMODEL_H
#define FOLDERMODEL_H

#include <QAbstractListModel>

class Folder;
class SynClient;

class FolderModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum FolderRoles {
        IdRole = Qt::UserRole + 1,
        LabelRole = Qt::UserRole + 2,
        PathRole = Qt::UserRole + 3,
        LastFileAtRole = Qt::UserRole + 4,
        LastFileFilenameRole = Qt::UserRole + 5,
        LastFileDeletedRole = Qt::UserRole + 6,
        LastScanRole = Qt::UserRole + 7,
    };

    explicit FolderModel(QObject *parent = 0);
    virtual ~FolderModel();

    virtual int rowCount(const QModelIndex&) const { return backing.size(); }
    virtual QVariant data(const QModelIndex &index, int role) const;

    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void getFolders();

private:
    QVector<Folder*> backing;
    SynClient *client;
};

#endif // FOLDERMODEL_H
