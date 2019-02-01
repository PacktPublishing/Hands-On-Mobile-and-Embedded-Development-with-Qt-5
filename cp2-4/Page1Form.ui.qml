import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.0

Page {
    width: 600
    height: 400

    header: Label {
        text: qsTr("Page 1")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Label {
        text: qsTr("You are on Page 1.")
        anchors.centerIn: parent
    }

    RowLayout {
        x: 92
        y: 19

        Rectangle {
            id: rectangle1
            color: "#ffffff"
            Layout.preferredHeight: 200
            Layout.preferredWidth: 200
            border.width: 4
            border.color: "#ef1919"
        }

        Rectangle {
            id: rectangle2
            color: "#ffffff"
            Layout.preferredHeight: 200
            Layout.preferredWidth: 200
            border.width: 4
            border.color: "#1313e8"
        }
    }
}
