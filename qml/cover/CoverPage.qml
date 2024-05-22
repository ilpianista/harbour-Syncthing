/*
    Copyright (C) 2021-2023 Andrea Scarpino <andrea@scarpino.dev>
    All rights reserved.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.syncthing 1.0

CoverBackground {

    CoverPlaceholder {
        id: placeholder
        text: "Syncthing"
        icon.source: "/usr/share/icons/hicolor/86x86/apps/harbour-syncthing.png"

        visible: folders.count == 0
    }

    SilicaListView {
        id: folders

        anchors.fill: parent
        width: parent.width

        visible: folders.count > 0

        model: FolderModel {
            id: model
        }

        delegate: FolderCoverDelegate {}
    }

    CoverActionList {
        CoverAction {
            iconSource: "image://theme/icon-cover-sync"
            onTriggered: function() {
                model.getFolders();
            }
        }
    }

}
