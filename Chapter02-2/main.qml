import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Flow {
        anchors.fill: parent
        anchors.margins: 4
        spacing: 10

        Rectangle {
            width: 35
            height: 35
            gradient: Gradient {
                GradientStop { position: 0.0; color: "green"; }
                GradientStop { position: 0.25; color: "purple"; }
                GradientStop { position: 0.5; color: "yellow"; }
                GradientStop { position: 1.0; color: "black"; }
            }
        }

        Text {
            text: "Hands-On"
            color: "purple"
            font.pointSize: 20
        }
        Text {
            text: "Mobile"
            color: "red"
            font.pointSize: 20
        }
        Text {
            text: "and Embedded"
            color: "blue"
            font.pointSize: 20
        }
    }
}
