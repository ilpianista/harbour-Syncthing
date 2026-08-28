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
import QtQuick 2.0
import Sailfish.Silica 1.0

ListItem {
    id: listItem

    width: ListView.view.width
    contentHeight: col.height + Theme.paddingLarge * 2

    property var syncthingModel: ListView.view.model
    property string folderId: id
    property bool folderPaused: paused

    menu: ContextMenu {
        id: contextMenu

        MenuItem {
            text: listItem.folderPaused ? qsTr("Resume") : qsTr("Pause")
            onClicked: listItem.syncthingModel.setFolderPaused(listItem.folderId, !listItem.folderPaused)
        }
    }

    property string stateIcon: {
        switch (folderStatusText) {
        case "Scanning":
        case "ScanWaiting":
            return "image://theme/icon-m-search";
        case "SyncWaiting":
        case "SyncPreparing":
        case "Syncing":
            return "image://theme/icon-m-sync";
        case "Cleaning":
        case "CleanWaiting":
            return "image://theme/icon-m-delete";
        case "Error":
            return "image://theme/icon-m-warning";
        case "Idle":
            return "image://theme/icon-m-acknowledge";
        default:
            return "";
        }
    }

    Column {
        id: col
        x: Theme.horizontalPageMargin
        width: parent.width - Theme.horizontalPageMargin * 2

        Row {
            width: parent.width - 2 * x
            spacing: Theme.paddingMedium

            Image {
                id: statusIcon
                height: parent.height - 2 * Theme.paddingSmall
                width: parent.height - 2 * Theme.paddingSmall
                anchors.verticalCenter: parent.verticalCenter
                source: paused ? "image://theme/icon-m-pause" : stateIcon
                visible: paused || stateIcon != ""
            }

            Label {
                color: listItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                width: parent.width
                text: label
                font.pixelSize: Theme.fontSizeMedium
            }
        }

        Label {
            width: parent.width - 2 * x
            color: listItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
            font.pixelSize: Theme.fontSizeSmall
            text: path
            truncationMode: TruncationMode.Fade
            wrapMode: Text.WordWrap
        }

        Label {
            width: parent.width - 2 * x
            color: listItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
            font.pixelSize: Theme.fontSizeExtraSmall
            text: paused ? "" : qsTr("Last scan: %1").arg(Qt.formatDateTime(lastScan, "yyyy/MM/dd hh:mm:ss"))
        }
    }
}
