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
    width: ListView.view.width
    height: col.height
    contentHeight: Theme.itemSizeLarge

    Column {
        id: col
        x: Theme.horizontalPageMargin
        width: parent.width - Theme.horizontalPageMargin * 2

        Row {
            width: parent.width - 2 * x
            spacing: Theme.paddingMedium

            Image {
                 id: pausedIcon
                 height: parent.height - 2 * Theme.paddingSmall
                 width: parent.height - 2 * Theme.paddingSmall
                 anchors.verticalCenter: parent.verticalCenter
                 source: "image://theme/icon-m-pause"
                 visible: paused
             }

            Label {
                color: Theme.primaryColor
                width: parent.width
                text: label
                font.pixelSize: Theme.fontSizeMedium
            }
        }

        Label {
            width: parent.width - 2 * x
            color: Theme.secondaryHighlightColor
            font.pixelSize: Theme.fontSizeSmall
            text: path
            truncationMode: TruncationMode.Fade
            wrapMode: Text.WordWrap
        }

        Label {
            width: parent.width - 2 * x
            color: Theme.secondaryHighlightColor
            font.pixelSize: Theme.fontSizeExtraSmall
            text: paused ? "" : qsTr("Last scan: %1").arg(Qt.formatDateTime(lastScan, "yyyy/MM/dd hh:mm:ss"))
        }
    }
}
