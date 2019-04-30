import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.1

ApplicationWindow {
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
}
