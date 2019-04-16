import QtQuick 2.11
import QtQuick.Controls 2.4

Page {
    id: page
    width: 600
    height: 400
    property alias button: button
    property alias gridView: gridView

    header: Label {
        text: qsTr("Your colors")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    GridView {
        id: gridView
        anchors.fill: parent
        delegate: listDelegate
        cellWidth: 70
        cellHeight: 70
    }
    Component {
    id: listDelegate
        Rectangle {
            width: gridView.cellWidth
            height: gridView.cellHeight
            color: colorCode
        }
    }

Button {
        id: button
        y: 297
        text: qsTr("Restore")
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 12
    }
}


/*##^## Designer {
    D{i:2;anchors_height:140;anchors_width:140;anchors_x:237;anchors_y:59}D{i:7;anchors_x:257}
}
 ##^##*/
