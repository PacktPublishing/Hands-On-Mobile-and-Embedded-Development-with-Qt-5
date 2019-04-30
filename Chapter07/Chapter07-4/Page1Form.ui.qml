import QtQuick 2.12
import QtQuick.Controls 2.4
import QtWebSockets 1.0

Page {
    id: page
    width: 600
    height: 400

    header: Label {
        text: qsTr("WebSocket Server")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Button {
        id: socketButton
        anchors.top: parent.top
        anchors.left: parent.left
        text: socketServer.listen ? "Stop WebSocketServer" : "Start WebSocket Server"
        onClicked: socketServer.listen = !socketServer.listen;
    }

    Row {
        id: textRow
        anchors.top: socketButton.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        TextField {
            id: serverTextField
            placeholderText: "send a message!"
        }
        Button {
        id: sendButton
            text: "Send"
            enabled: remoteWebSocket.active
            onClicked: {
                wsClient.sendTextMessage(serverTextField.text)
                serverTextField.text = ""
            }
        }
    }
    TextArea {
        id: serverTextArea
        placeholderText:  socketServer.listen ? "WebSocket server listening..." : "WebSocket server NOT listening..."
        anchors.top: textRow.bottom
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

    WebSocketServer {
        id: socketServer
        host : "127.0.0.1"
        port: 33343
        listen: false

        onClientConnected: {
            wsClient = webSocket
            sendButton.enabled = true
            wsClient.sendTextMessage("Client OK!")
            webSocket.onTextMessageReceived.connect(function(message) {
                  serverTextArea.text = message + "\n" + serverTextArea.text
            });
            wsClient.onStatusChanged.connect(function(status) {
                if (status == WebSocket.Error) {
                        serverTextArea.text = webSocket.errorString
                        webSocket.active = false
                 } else if (status == WebSocket.Open) {
                        console.log("Client WebSocket.Open")
                 } else if (status == WebSocket.Closed) {
                     console.log("Client WebSocket.Closed")
                 }
                });
        }

        onErrorStringChanged: {
            serverTextArea.text = errorString
        }
    }

    property var wsClient: WebSocket {
        id: remoteWebSocket
    }
}
