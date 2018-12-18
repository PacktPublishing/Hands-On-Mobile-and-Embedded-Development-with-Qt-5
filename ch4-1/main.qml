import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 1.4
import QtQuick.VirtualKeyboard 2.3

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Mobile and Embedded")
    color: "blue"

    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: window.height
        width: window.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: window.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }

    TextField {
        anchors {
            bottom: inputPanel.top
            top: parent.top
            right: parent.right
            left: parent.left
        }

        placeholderText: qsTr("Enter something")
    }

}
