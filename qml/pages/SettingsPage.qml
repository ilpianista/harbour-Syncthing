/*
    Copyright (C) 2024 Andrea Scarpino <andrea@scarpino.dev>
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

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: content.height

        Column {
            id: content
            width: parent.width

            PageHeader {
                title: qsTr("Settings")
            }

            SectionHeader {
                text: qsTr("General")
            }

            TextSwitch {
                id: keepRunningSwitch
                text: qsTr("Keep running in background")
                description: qsTr("Leave the syncthing daemon running when the application quits")

                checked: app.keepRunning
                onCheckedChanged: {
                    app.keepRunning = checked;
                    if (checked) {
                        systemd.typedCall('EnableUnitFiles', [
                            {
                                "type": 'as',
                                "value": ['syncthing.service']
                            },
                            {
                                "type": 'b',
                                "value": false
                            },
                            {
                                "type": 'b',
                                "value": false
                            }
                        ], function (result) {}, function (error, message) {
                            console.log("failed (" + error + ") with:", message);
                        });
                    } else {
                        systemd.typedCall('DisableUnitFiles', [
                            {
                                "type": 'as',
                                "value": ['syncthing.service']
                            },
                            {
                                "type": 'b',
                                "value": false
                            }
                        ], function (result) {}, function (error, message) {
                            console.log("failed (" + error + ") with:", message);
                        });
                    }
                    settings.keepRunning = checked;
                }
            }
        }

        VerticalScrollDecorator {}
    }
}
