import QtQuick 2.11
import QtQuick.Window 2.11
import QtPositioning 5.11
//import QtQuick.Controls 2.11

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    PositionSource {
        id: positionSource
        updateInterval: 1000
        active: true

        onPositionChanged: {
            var coord = positionSource.position.coordinate;
            console.log("Coordinate:", coord.longitude, coord.latitude);
            latitudeLabel.text = "Latitude: " + coord.latitude;
            longitudeLabel.text = "Longitude: " + coord.longitude;
            if (positionSource.position.altitudeValid)
                altitudeLabel.text = "Altitude: " + coord.altitude;
        }
    }
    Column {
        anchors.fill: parent
        Text {
            id: latitudeLabel
            text: "Latitude:"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: longitudeLabel.top
            font.pointSize: 24
        }
        Text {
            id: longitudeLabel
            text: "Longitude:"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: 24
        }
        Text {
            id: altitudeLabel
            text: "Altitude:"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: longitudeLabel.bottom
            font.pointSize: 24
        }
    }
}
