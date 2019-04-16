import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.1
import QtQuick.Controls.Material 2.1

ApplicationWindow {
    height: 1024
    width: 480
    visible: true
    title: "Mobile and Embedded"
    menuBar: MenuBar {
        Menu { title: "File"
            MenuItem { text: "Open "
                onTriggered: helloDialog.open()
            }
        }
    }
    header: TextField {
        placeholderText: "Remember the Qt 4 Dance video?"
    }
    MessageDialog {
        id: helloDialog
        title: "Hello Mobile!"
        text: "Qt for Embedded devices to rule the world!"
    }
    SwipeView {
        id: swipeView
        anchors.fill: parent

        Page {
            id: page1
            anchors.fill: parent.fill
            header: Label {
                text: "Working"
                font.pixelSize: Qt.application.font.pixelSize * 2
                padding: 10
            }
            BusyIndicator {
                id: busyId
                anchors.centerIn: parent
                running: true;
            }
            Label {
                text: "Busy Working"
                anchors.top: busyId.bottom
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        Page {
            id: page2
            anchors.fill: parent.fill
            header: Label {
                text: "Go Back"
                font.pixelSize: Qt.application.font.pixelSize * 2
                padding: 10
            }
            Column {

                anchors.centerIn: parent
                Button {
                    text: "Click to go back"
                    background: Rectangle {
                        color: "#673AB7"
                        radius: 50
                        border.color: "#4CAF50"
                        border.width: 2
                    }
                    onClicked: swipeView.currentIndex = 0
                }
                Label {
                    text: "Nothing here to see. Move along, move along."
                }
            }
        }

    }
    PageIndicator {
        id: indicator
        count: swipeView.count
        currentIndex: swipeView.currentIndex

        anchors.bottom: swipeView.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
