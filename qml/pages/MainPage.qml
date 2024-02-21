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
import Nemo.DBus 2.0
import harbour.syncthing 1.0

Page {

    allowedOrientations: Orientation.All

    DBusInterface {
        id: systemd

        service: 'org.freedesktop.systemd1'
        path: '/org/freedesktop/systemd1'
        iface: 'org.freedesktop.systemd1.Manager'
    }

    SilicaListView {
        id: list
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                id: browser
                text: qsTr("Open in browser")
                enabled: client.getHealth()

                onClicked: Qt.openUrlExternally("http://localhost:8384")
            }
        }

        header: PageHeader {
            title: "Folders"
        }

        model: FolderModel {
            id: model
        }

        delegate: FolderDelegate {}
    }

    Timer {
        id: sleep
        interval: 100
        repeat: true

        onTriggered: {
            if (client.getHealth()) {
                sleep.running = false;
                model.getFolders();
            }
        }
    }

    Component.onCompleted: {
        systemd.typedCall('StartUnit',
            [
                { 'type': 's', 'value': 'syncthing.service' },
                { 'type': 's', 'value': 'fail' }
            ],
            function(result) {
                sleep.running = true;
            },
            function(error, message) {
                console.log("failed (" + error + ") with:", message)
            }
       );
    }

    Component.onDestruction: {
        systemd.typedCall('StopUnit',
            [
                { 'type': 's', 'value': 'syncthing.service' },
                { 'type': 's', 'value': 'fail' }
            ],
            function(result) {},
            function(error, message) {
                console.log("failed (" + error + ") with:", message)
            }
        );
    }
}
