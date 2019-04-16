import QtQuick 2.11
import QtQuick.Controls 2.4

Page {
    width: 600
    height: 400
    property alias button: button
    property color dialogColor: "white"
    header: Label {
        text: qsTr("Pick a color to purchase")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Rectangle {
        id: page
        anchors.fill: parent
        color: dialogColor
        Button {
            id: button
            x: 250
            y: 129
            text: qsTr("Pick a color")
        }
    }
}
