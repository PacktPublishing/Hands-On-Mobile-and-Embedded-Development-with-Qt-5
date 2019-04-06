import QtQuick 2.12
import QtQuick.Window 2.12
import QtCharts 2.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ChartView {
        title: "Australian Rain"
        anchors.fill: parent
     //   legend.alignment: Qt.AlignBottom
        antialiasing: true

        BarSeries {
            id: mySeries
            axisX: BarCategoryAxis {
                categories: ["2015", "2016", "2017" ]
            }
            BarSet { label: "Adelaide"; values: [536, 821, 395] }
            BarSet { label: "Brisbane"; values: [1076, 759, 1263] }
            BarSet { label: "Darwin"; values: [2201, 1363, 1744] }
            BarSet { label: "Melbourne"; values: [526, 601, 401] }
            BarSet { label: "Perth"; values: [729, 674, 578] }
            BarSet { label: "Sydney"; values: [1076, 1386, 1338] }
        }
    }
}
