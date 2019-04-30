import QtQuick 2.12
import QtQuick.Window 2.12
import QtMultimedia 5.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Audio {
        id: audioPlayer
        source: "sample.mp3"
        autoPlay: true
        volume: .75
        loops: 4
        notifyInterval: 100
        onPositionChanged: {
            console.log(position)
        }
        onStatusChanged: {
            console.log("Status " + status)
        }
        metaData {
            onMetaDataChanged: {
                titleLabel.text = "Title: " + metaData.title
                artistLabel.text = "Artist: " + metaData.contributingArtist
                albumLabel.text = "Album: " + metaData.albumTitle
                console.log(metaData.size)

            }
        }
    }

    Text {
        id: titleLabel
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Text {
        id: artistLabel
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: titleLabel.bottom
    }
    Text {
        id: albumLabel
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: artistLabel.bottom
    }

//        Component.onCompleted:  {
//    //    audioPlayer.play()
//    }
}
