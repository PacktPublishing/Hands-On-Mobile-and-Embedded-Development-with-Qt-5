import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    color: "black"
    title: qsTr("You can touch this!")

    MultiPointTouchArea {
        anchors.fill: parent
        touchPoints: [
            TouchPoint { id: touch1 },
            TouchPoint { id: touch2 },
            TouchPoint { id: touch3 }
        ]
        Rectangle {
            width: 45; height: 45
            color: "#80c342"
            x: touch1.x
            y: touch1.y
            radius: 50
            Behavior on x  {
                 PropertyAnimation {easing.type: Easing.OutBounce; duration: 500 }
             }
            Behavior on y  {
                 PropertyAnimation {easing.type: Easing.OutBounce; duration: 500 }
             }
        }

        Rectangle {
            width: 45; height: 45
            color: "#b40000"
            x: touch2.x
            y: touch2.y
            radius: 50
            Behavior on x  {
                 PropertyAnimation {easing.type: Easing.OutBounce; duration: 500 }
             }
            Behavior on y  {
                 PropertyAnimation {easing.type: Easing.OutBounce; duration: 500 }
             }
        }

        Rectangle {
            width: 45; height: 45
            color: "#6b11d8"
            x: touch2.x
            y: touch2.y
            radius: 50
            Behavior on x  {
                 PropertyAnimation {easing.type: Easing.OutBounce; duration: 500 }
             }
            Behavior on y  {
                 PropertyAnimation {easing.type: Easing.OutBounce; duration: 500 }
             }
        }

    }
}
