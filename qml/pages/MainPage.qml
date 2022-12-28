/*
    Copyright (C) 2021 Andrea Scarpino <andrea@scarpino.dev>
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

Page {

    allowedOrientations: Orientation.All

    DBusInterface {
        id: systemd

        service: 'org.freedesktop.systemd1'
        path: '/org/freedesktop/systemd1'
        iface: 'org.freedesktop.systemd1.Manager'
    }

    function startSyncthing() {
        systemd.typedCall('StartUnit',
            [
                { 'type': 's', 'value': 'syncthing.service' },
                { 'type': 's', 'value': 'fail' }
            ],
            function(result) {
                status.text = qsTr("Syncthing is running");
                stop.enabled = true;
                start.enabled = false;
            },
            function(error, message) {
                status.text = qsTr("Syncthing is stopped");
                console.log("failed (" + error + ") with:", message)
            }
       );
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        PullDownMenu {
            MenuItem {
                id: stop
                text: qsTr("Stop")
                enabled: client.getUptime() > 0

                onClicked: {
                    systemd.typedCall('StopUnit',
                        [
                            { 'type': 's', 'value': 'syncthing.service' },
                            { 'type': 's', 'value': 'fail' }
                        ],
                        function(result) {
                            status.text = qsTr("Syncthing is stopped");
                        }
                    );
                }
            }

            MenuItem {
                id: start
                text: qsTr("Start")
                enabled: client.getUptime() === 0

                onClicked: {
                    startSyncthing();
                }
            }
        }

        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingLarge

            PageHeader {
                title: "Syncthing"
            }

            Label {
                id: status
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width
            }
        }
    }

    Component.onCompleted: {
        startSyncthing();
    }
}
