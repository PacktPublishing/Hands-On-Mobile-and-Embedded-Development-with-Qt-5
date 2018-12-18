import QtQuick 2.9
//import QtQuick.Window 2.2

Rectangle {
    width: 500
    height: 500
    Column {
        Rectangle {
            width: 35
            height: 35
            gradient: Gradient {
                GradientStop { position: 0.0; color: "green"; }
                GradientStop { position: 0.25; color: "purple"; }
                GradientStop { position: 0.5; color: "yellow"; }
                GradientStop { position: 1.0; color: "black"; }
            }
        }

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
        }
    }
}
