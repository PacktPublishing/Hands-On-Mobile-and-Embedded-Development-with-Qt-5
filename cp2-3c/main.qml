import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    GridLayout {
        rows: 3
        columns: 2

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
            Layout.fillHeight: true
         }
    }
}
