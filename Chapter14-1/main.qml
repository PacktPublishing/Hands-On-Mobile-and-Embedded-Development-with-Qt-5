import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello Qt for WebAssembly!")
    TextArea {
        id: textArea
        anchors.fill: parent.fill
        text: "This is Qt for WebAssrmbly.\nI am a Qml app running in a web browser!"

    }
    RoundButton {
        text: "\u2712"
        anchors.top: textArea.bottom
        anchors.horizontalCenter: parent.horizontalCenter
//        onClicked:
    }
}
