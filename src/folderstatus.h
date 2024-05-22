/*
  The MIT License (MIT)

  Copyright (c) 2024 Andrea Scarpino <andrea@scarpino.dev>

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

#ifndef FOLDERSTATUS_H
#define FOLDERSTATUS_H

#include <QObject>
#include <QString>

class FolderStatusPrivate;

class FolderStatus : public QObject
{
    Q_OBJECT
    Q_PROPERTY(FolderState state READ state)

public:
    enum FolderState {
        Idle,
        Scanning,
        ScanWaiting,
        SyncWaiting,
        SyncPreparing,
        Syncing,
        Cleaning,
        CleanWaiting,
        Error,
        Unknown
    };
    Q_ENUM(FolderState)

    explicit FolderStatus(QObject *parent = 0);
    virtual ~FolderStatus();

    FolderState state() const;
    void setState(const FolderState state);

private:
    FolderStatusPrivate *d;

};

#endif // FOLDERSTATUS_H
