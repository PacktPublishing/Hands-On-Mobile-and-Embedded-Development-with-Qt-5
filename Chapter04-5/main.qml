import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    MultiPointTouchArea {
          anchors.fill: parent
          touchPoints: [
              TouchPoint { id: finger1 },
              TouchPoint { id: finger2 },
              TouchPoint { id: finger3 },
              TouchPoint { id: finger4 },
              TouchPoint { id: finger5 }
          ]
      }

      Rectangle {
          width: 30; height: 30
          color: "green"
          radius: 50
          x: finger1.x
          y: finger1.y
      }

      Rectangle {
          width: 30; height: 30
          color: "red"
          radius: 50
          x: finger2.x
          y: finger2.y
      }
      Rectangle {
          width: 30; height: 30
          color: "gold"
          radius: 50
          x: finger3.x
          y: finger3.y
      }
      Rectangle {
          width: 30; height: 30
          color: "black"
          radius: 50
          x: finger4.x
          y: finger5.y
      }
      Rectangle {
          width: 30; height: 30
          color: "purple"
          radius: 50
          x: finger5.x
          y: finger5.y
      }
}
