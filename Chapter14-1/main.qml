import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.13

Window {
    visible: tru
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
