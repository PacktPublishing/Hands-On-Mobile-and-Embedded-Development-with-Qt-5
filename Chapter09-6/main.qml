import QtQuick 2.11
import QtQuick.Window 2.11
import QtMultimedia 5.8

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("cp9-6")

    MediaPlayer {
        id: player
        autoPlay: false
        source: "qrc:hellowindow.mp2"
        onStatusChanged: {
            console.log("status: " + status)
        }
        onError: console.log("Error: " + errorString)
    }

    VideoOutput {
        source: player
        anchors.fill : parent
    }
    MouseArea {
        id: playArea
        anchors.fill: parent
        onPressed: player.play();
    }
}
