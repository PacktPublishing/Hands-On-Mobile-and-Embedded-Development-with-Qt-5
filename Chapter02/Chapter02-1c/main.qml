import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        anchors.fill: parent

     PathView {
         id: pathView
         anchors.fill: parent
         anchors.margins: 30

         model: myListModel

         delegate:  Rectangle {
             id: theDelegate
             Text {
                 text: carModel
             }
             Image {
                 source: "/icons8-sedan-64.png"
             }
         }
         path: Path {
             startX: 0; startY: 40
             PathArc { x: 0; y: 400; radiusX:5; radiusY: 5 }
         }

     }

     ListModel {
         id: myListModel
         ListElement { carModel: "Tesla" }
         ListElement { carModel: "Ford Sync 3" }
         ListElement { carModel: "Unknown" }
         ListElement { carModel: "Tesla" }
         ListElement { carModel: "Ford Sync 3" }
         ListElement { carModel: "Unknown" }
         ListElement { carModel: "Tesla" }
         ListElement { carModel: "Ford Sync 3" }
         ListElement { carModel: "Unknown" }
     }



    }
}
