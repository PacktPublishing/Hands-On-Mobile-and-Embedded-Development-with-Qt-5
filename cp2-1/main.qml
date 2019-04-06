import QtQuick 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.0

Window  {
    visible: true
    width: 500
    height: 500
    Rectangle {
anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "green"; }
            GradientStop { position: 0.25; color: "purple"; }
            GradientStop { position: 0.75; color: "yellow"; }
            GradientStop { position: 1.0; color: "black"; }
        }
        Text {
            id: textLabel
            text: "Hands-On Mobile and Embedded"
            color: "purple"
            font.pointSize: 20
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }

        GaussianBlur {
            anchors.fill: textLabel
            source: textLabel
            radius: 36
            samples: 16
        }
    }
}
