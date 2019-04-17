import QtQuick 2.11
import QtQuick.Window 2.11
import QtGraphicalEffects 1.0


Window {
    visible: true
    width: 640
    height: 480
    color: "black"
    title:  "Hands-On Mobile and Embedded"

    Item {
        width: 250; height: 250
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        RadialGradient {
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.0; color: "red" }
                GradientStop { position: 0.3; color: "green" }
                GradientStop { position: 1.0; color: "purple" }
            }
        }
    }
}
