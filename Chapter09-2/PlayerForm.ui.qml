import QtQuick 2.4
import QtQuick.Controls 2.3

Item {
    width: 400
    height: 400

    Image {
        id: playIcon

        source: "content/play.svg"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: stopIcon
        x: 136
        y: 284
        source: "content/stop-circle.svg"
        fillMode: Image.PreserveAspectFit
    }

    ProgressBar {
        id: progressBar
        x: 100
        y: 222
        value: 0.5
    }

    Image {
        id: skipForwardIcon
        x: 196
        y: 289
        width: 19
        height: 24
        source: "content/skip-forward.svg"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: fastForwardIcon
        x: 221
        y: 289
        source: "content/fast-forward.svg"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: skipBackIcon
        x: 100
        y: 289
        source: "content/skip-back.svg"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: rewindIcon
        x: 71
        y: 289
        source: "content/rewind.svg"
        fillMode: Image.PreserveAspectFit
    }

    RoundButton {
        id: roundButton
        x: 158
        y: 98
        text: "+"
        font.letterSpacing: -0.6
        display: AbstractButton.IconOnly
        icon: playIcon
    }
}
