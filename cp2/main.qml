import QtQuick 2.12
import QtQuick.Window 2.12

Window  {
    visible: true
    width: 500
    height: 500

    Rectangle {

        Text {
            id: textLabel
            text: "Hands-On Mobile and Embedded"
            color: "purple"
            font.pointSize: 20
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
