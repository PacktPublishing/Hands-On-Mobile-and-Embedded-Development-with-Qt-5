import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.0
import QtQuick.Controls.Styles 1.4
import QtPurchasing 1.0

ApplicationWindow {
    id: app
    visible: true
    width: 640
    height: 480
    title: qsTr("Tabs")
    property color appColor
    property alias colorMode: colorModel

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1Form {
            id: page1
            button.onClicked: {
                colorDialog.open()
            }
        }

        Page2Form {
            id: page2
            gridView.onCountChanged: console.log("count changed " + gridView.count)
            gridView.model: ListModel {
                id: colorModel
            }

            button.onClicked: {
                console.log("restore colors here")
                appStore.restorePurchases()
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Purchase color")
        }
        TabButton {
            text: qsTr("Colors")
        }
    }

    ColorDialog {
        id: colorDialog
        title: "Please choose a color"
        onAccepted: {
            console.log("Color chosen: " + colorDialog.color.toString())
            page1.dialogColor = colorDialog.color
            colorProduct.purchase()
        }
        onRejected: {
        }
    }

    Store {
        id: appStore
    }

    Product {
        id: colorProduct
        identifier: "your.app.cp11.colors"
        type: Product.Consumable
        store: appStore

        onPurchaseSucceeded: {
            console.log("sale succeeeded " + transaction.status +" : "+  transaction.orderId)
            colorModel.append({colorCode : page1.dialogColor.toString()})
            transaction.finalize()
        }
        onPurchaseRestored: {
            console.log("restored " + transaction.orderId)
        }
        onPurchaseFailed: {
            console.log("sale failed " + transaction.errorString +" : "+ transaction.failureReason)
            transaction.finalize()
        }
    }
 }
