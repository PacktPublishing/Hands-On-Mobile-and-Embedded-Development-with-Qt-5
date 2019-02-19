import QtQuick 2.11
import QtQuick.Window 2.11
import QtAudioEngine 1.0
import QtGraphicalEffects 1.0

Window {
    id: window
    visible: true
    width: 640
    height: 640
    title: qsTr("3D Positional Audio")
    color: "white"

    property real leftRightValue: 0;
    property real forwardBacktValue: 0;
    property real upDownValue: 0;
    property real mousePositionX;
    property real mousePositionY;
    property real dropShadowLength : audioPositioner.height;

    MouseArea {
        //mouse first to help propagate clicks to buttons
        anchors.fill: parent
        hoverEnabled: true
        propagateComposedEvents: true
        acceptedButtons: Qt.AllButtons
        onPositionChanged: {
            leftRightValue = -((window.width / 2) - mouse.x)
            forwardBacktValue = (window.height / 2) - mouse.y
        }
        onWheel: {
            if (wheel.angleDelta.y > 0) {
                upDownValue++
                audioPositioner.width++
                audioPositioner.height++
            } else {
                upDownValue--
                audioPositioner.width--
                audioPositioner.height--
            }
          //  dropShadowLength = audioPositioner.height
            console.log(wheel.angleDelta )
        }
    }
    PinchArea {
        onSmartZoom: {
            if (pinch.scale > 0) {
                upDownValue++
                audioPositioner.width++
                audioPositioner.height++
            } else {
                upDownValue--
                audioPositioner.width--
                audioPositioner.height--
            }
        }
    }

    MyRoundButton {
        id: frontControl
        text: "Front"
        anchors {
            horizontalCenter: parent.horizontalCenter;
            top: parent.top
            topMargin: 25
        }
        onClicked: forwardBacktValue++

    }
    MyRoundButton {
        id: rightControl
        text: "Right"
        anchors {
            verticalCenter: parent.verticalCenter;
            right: parent.right
            rightMargin: 25
        }
        onClicked: {
            console.log("clicker")
            leftRightValue++
        }
    }
    MyRoundButton {
        id: backControl
        text: "Back"
        anchors {
            horizontalCenter: parent.horizontalCenter;
            bottom: parent.bottom
            bottomMargin: 25
        }
        onClicked: forwardBacktValue--
    }
    MyRoundButton {
        id: leftControl
        text: "Left"
        anchors {
            verticalCenter: parent.verticalCenter;
            left: parent.left
            leftMargin: 25
        }
        onClicked: leftRightValue--
    }

    MyRoundButton {
        id: upControl
        text: "Up"
        anchors {
            left: frontControl.right
            leftMargin: 25
            bottom: rightControl.top
            bottomMargin: 25
        }
        onClicked: {
            audioPositioner.width++
            audioPositioner.height++
            dropShadowLength = audioPositioner.height
            upDownValue++
        }
    }

    MyRoundButton {
        id: downControl
        text: "Down"
        anchors {
            right: backControl.left
            rightMargin: 25
            top: leftControl.bottom
            topMargin: 25
        }
        onClicked: {
            audioPositioner.width--
            audioPositioner.height--
       //     dropShadowLength = audioPositioner.height

            upDownValue--
        }
    }

    //////////////////////////////////////////////////////////////

    AudioEngine {
        id: audioEngine
        dopplerFactor: 1
        speedOfSound: 343.33

        listener.up:"0,0,1"
        listener.position:"0,0,0"
        listener.velocity:"0,0,0"
        listener.direction:"0,1,0"

        AudioSample {
            name:"plink"
            source: "thunder.wav"
            preloaded: true
        }

        Sound {
            name: "thunderengine"
            attenuationModel: "thunderModel"

            PlayVariation {
                looping: true
                sample: "plink"
                maxGain: 0.5
                minGain: 0.3
            }
        }
    }

    AttenuationModelInverse {
        name:"default"
        start: 20
        end: 1000
        rolloff: 0.1
    }

    AttenuationModelLinear {
        name: "thunderModel"
        start: 20
        end: 180
    }
    //        direction: {
    //            var a = (starship.rotation / 360) * root.twoPi;
    //            return Qt.vector3d(Math.sin(a), -Math.cos(a), 0);
    //        }
    //        velocity: {
    //            var speed = root.twoPi * root.radius / 4;
    //            return shipSound.direction.times(speed);
    //        }

    SoundInstance {
        id:  plinkSound
        engine: audioEngine
        sound: "thunderengine"
        position: Qt.vector3d(leftRightValue, forwardBacktValue, upDownValue)

        onPositionChanged: console.log("Sound position changed "+leftRightValue+" "+forwardBacktValue +" "+ upDownValue)

        Component.onCompleted: plinkSound.play()
    }

    Rectangle {
        color: "green"
        id: audioPositioner
        width: 16
        height: 16
        x: Math.abs(leftRightValue + 2 + window.width / 2)
        y: Math.abs(forwardBacktValue + 2 - window.height / 2)
        radius: 50
        layer.enabled: true
        layer.effect: DropShadow {

            anchors.fill: audioPositioner
            horizontalOffset: dropShadowLength
            verticalOffset: dropShadowLength
            radius: dropShadowLength
            samples: 17
            color: "#000000"
            source: audioPositioner
        }
    }
}
