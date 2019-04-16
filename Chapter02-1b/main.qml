import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        anchors.fill: parent

     GridView {
         id: gridView
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


         flow: GridView.FlowTopToBottom //FlowLeftToRight //FlowTopToBottom
         layoutDirection: Qt.LeftToRight // RightToLeft // LeftToRight
         verticalLayoutDirection: GridView.BottomToTop //  BottomToTop // TopToBottom


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
