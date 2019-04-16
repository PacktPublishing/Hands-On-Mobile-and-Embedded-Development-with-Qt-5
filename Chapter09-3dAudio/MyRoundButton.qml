import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

RoundButton {
    id: control
    radius: width * 0.5
    implicitWidth: 100
    implicitHeight: width
    contentItem: textControl
    autoRepeat: true

    RadialGradient {
        anchors.fill: control
        horizontalRadius: 45
        verticalRadius: 45
        source: control
        gradient: Gradient {
            GradientStop { position: 0; color: "blue" }
            GradientStop { position: 0.2; color: "green" }
            GradientStop { position: 0.4; color: "red" }
            GradientStop { position: 0.6; color: "yellow" }
            GradientStop { position: 1; color: "purple" }
        }
    }
    Text {
        id: textControl
        text: control.text
        color: control.down ? "cyan" : "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 20
        layer.enabled: true
        layer.effect: DropShadow {
            anchors.fill: control
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8.0
            samples: 17
            color: "#000000"
            source: textControl
        }
    }
}
