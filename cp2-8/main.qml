import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    color: "black"
    title: qsTr("Red Bouncy Box")

    Rectangle {
        id: redBox
        width: 50; height: 50
        color: "black"
        border.width: 4
        border.color: "red"

        Behavior on x { SpringAnimation { spring: 10; damping: 10; } }
        Behavior on y { SpringAnimation { spring: 10; damping: .1;  mass: 10 } }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onClicked: animation.start()

        onPositionChanged: {
            redBox.x = mouse.x - redBox.width/2
            redBox.y = mouse.y - redBox.height/2
        }
    }

    ParallelAnimation {
        id: animation
        NumberAnimation { target: redBox; property: "x"; to: 35; duration: 1500 }
        NumberAnimation { target: redBox; property: "y"; to: 65; duration: 1500 }
    }
}
