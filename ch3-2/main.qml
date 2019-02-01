import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Particles 2.11
import QtGraphicalEffects 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Mobile and Embedded")

    MouseArea {
        id: mousey
        anchors.fill: parent
        onClicked: {particles.burst(25) }
        hoverEnabled: true
    }

    Rectangle {
        anchors.fill: parent
        gradient:
           Gradient {
                GradientStop { position: 0.0; color: "green"; }
                GradientStop { position: 0.25; color: "purple"; }
                GradientStop { position: 0.75; color: "yellow"; }
                GradientStop { position: 1.0; color: "black"; }

        }
        Text {
            id: textLabel
            text: "Hands-On Mobile and Embedded"
            color: "purple"
            font.pointSize: 20
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }
        DropShadow {
            anchors.fill: textLabel
            horizontalOffset: 2
            verticalOffset: 2
            radius: 10
            samples: 25
            color: "white"
            source: textLabel
        }
//        Glow {
//            id: glow
//            anchors.fill: textLabel
//            radius: 10
//            samples: 25
//            color: "lightblue"
//            source: textLabel
//        }
    }


//    ParticleSystem {
//        id: particelSystem
//        anchors.fill: parent

//        ItemParticle {
//            delegate: Rectangle {
//                height: 30; width: 30
//                id: particleSquare
//                color: "transparent"
//                radius: 65
//                border.color: "green"
//                border.width: 4
//            }
//        }
//        Turbulence {
//            anchors.fill: parent
//              strength: 300
//          }
//        Gravity {
//            anchors.fill: parent
//            angle: 270
//            magnitude: 8
//        }
//    }
//    Emitter {
//        id: particles
//        system: particelSystem
//      //  anchors { horizontalCenter: parent.horizontalCenter; }
//        y: mousey.mouseY
//        x: mousey.mouseX
//        width: 10
//        height: 10
//        lifeSpan: 5000
//        velocityFromMovement: 60
//        sizeVariation: 15
//        emitRate: 50
//        enabled: false

//        velocity: AngleDirection {
//            angle: 90
//            magnitude: 150
//            angleVariation: 25
//            magnitudeVariation: 50
//        }
//    }

}
