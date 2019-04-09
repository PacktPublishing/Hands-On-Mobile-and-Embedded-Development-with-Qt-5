import QtQuick 2.12
import QtQuick.Controls 2.4
import QtWebSockets 1.0

Page {
    width: 600
    height: 400

    header: Label {
        text: qsTr("WebSocket Client")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }


    Button {
        id: socketButton
        anchors.top: parent.top
        anchors.left: parent.left
        text: webSocket.active ? "Disconnect" : "Connect"
        onClicked: webSocket.active = !webSocket.active;
    }
    Row {
        id: textRow
        anchors.top: socketButton.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        TextField {
            id: clientTextField
            placeholderText: "send a message!"
        }
        Button {
            text: "Send"
            enabled: webSocket.active
            onClicked: {
                webSocket.sendTextMessage(clientTextField.text)
                clientTextField.text = ""
            }
        }
    }
    TextArea {
        id: clientTextArea
         placeholderText: webSocket.active ? "Connected" : "Disconnected"
        anchors.top: textRow.bottom
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }


    WebSocket {
        id: webSocket
        url : "ws://127.0.0.1:33343"
        onTextMessageReceived: {
            clientTextArea.text = message + "\n" + clientTextArea.text
        }
        onStatusChanged: {
            if (status == WebSocket.Error) {
                    clientTextArea.text = webSocket.errorString
                    webSocket.active = false
             } else if (status == WebSocket.Open) {
                    console.log("WebSocket.Open")
             } else if (status == WebSocket.Closed) {
                 console.log("WebSocket.Closed")
             }
            }

    }
}
