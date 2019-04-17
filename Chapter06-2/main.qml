import QtQuick 2.12
import QtQuick.Window 2.12
import QtBluetooth 5.12
import QtQuick.Controls 2.4

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello Bluetooth LE")


    BluetoothDiscoveryModel {
        id: discoveryModel
        discoveryMode: BluetoothDiscoveryModel.DeviceDiscovery
        onDeviceDiscovered: {
            if (/*device == "01:01:01:01:01:01" && */discoveryMode == BluetoothDiscoveryModel.DeviceDiscovery) {
                discoveryModel.running = false
                discoveryModel.discoveryMode = BluetoothDiscoveryModel.FullServiceDiscovery
                discoveryModel.remoteAddress = device
                discoveryModel.running = true
            }
        }
    }

    ListView {
        id: mainList
        anchors.top: busy.bottom
        anchors.fill: parent
        model: discoveryModel

        delegate: Rectangle {
            id: btDelegate
            width: parent.width
            height: column.height + 10
            focus: true
            Column {
                id: column
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    id: btText
                    text: deviceName ? deviceName : name
                    font.pointSize: 14
                }
            }
        }
    }

    BusyIndicator {
        id: busy
        width: mainWindow.width *.6
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: mainWindow.top
        height: mainWindow.height / 8
        running: discoveryModel.running
    }
}



//BluetoothSocket {
//    id: btSocket

//    onServiceDiscovered {
//        if (service.serviceName == "Magical Service")
//           btSocket.setService(service)

//    }

//}

//        onSocketStateChanged: {
//             switch (socketState) {
//                case BluetoothSocket.Unconnected:
//                case BluetoothSocket.NoServiceSet:
//                break;
//                case BluetoothSocket.Connected:
//                    console.log("Connected");
//                break;
//                case BluetoothSocket.Connecting:
//                    console.log("Connecting...");
//                break;
//                case BluetoothSocket.ServiceLookup:
//                    console.log("Looking up Service");
//                break;
//                case BluetoothSocket.Closing:
//                    console.log("Closing connection");
//                break;
//                case BluetoothSocket.Listening:
//                    console.log("Listening for incoming connections");
//                break;
//                case BluetoothSocket.Bound:
//                    console.log("Bound to local address")
//                break;
//             }
//         }
