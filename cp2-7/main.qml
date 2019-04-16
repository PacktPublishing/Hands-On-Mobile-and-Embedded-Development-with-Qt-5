import QtQuick 2.12
import QtQuick.Window 2.12
import QtDataVisualization 1.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Australian Rain")
    Bars3D {
        width: parent.width
        height: parent.height
        theme: Theme3D {
            type: Theme3D.ThemeQt
            labelBorderEnabled: true
            font.pointSize: 75
            labelBackgroundEnabled: true
        }
        Bar3DSeries {
            itemLabelFormat: "@colLabel, @rowLabel: @valueLabel"

            ItemModelBarDataProxy {
                itemModel: dataModel
                rowRole: "year"
                columnRole: "city"
                valueRole: "total"
            }
        }
    }

    ListModel {
        id: dataModel
        ListElement{ year: "2017"; city: "Adelaide"; total: "536"; }
        ListElement{ year: "2016"; city: "Adelaide"; total: "821"; }
        ListElement{ year: "2015"; city: "Adelaide"; total: "395"; }
        ListElement{ year: "2017"; city: "Brisbane"; total: "1076"; }
        ListElement{ year: "2016"; city: "Brisbane"; total: "759"; }
        ListElement{ year: "2015"; city: "Brisbane"; total: "1263"; }
        ListElement{ year: "2017"; city: "Darwin"; total: "2201"; }
        ListElement{ year: "2016"; city: "Darwin"; total: "1363"; }
        ListElement{ year: "2015"; city: "Darwin"; total: "1744"; }
        ListElement{ year: "2017"; city: "Melbourne"; total: "526"; }
        ListElement{ year: "2016"; city: "Melbourne"; total: "601"; }
        ListElement{ year: "2015"; city: "Melbourne"; total: "401"; }
        ListElement{ year: "2017"; city: "Perth"; total: "729"; }
        ListElement{ year: "2016"; city: "Perth"; total: "674"; }
        ListElement{ year: "2015"; city: "Perth"; total: "578"; }
        ListElement{ year: "2017"; city: "Sydney"; total: "1076"; }
        ListElement{ year: "2016"; city: "Sydney"; total: "1386"; }
        ListElement{ year: "2015"; city: "Sydney"; total: "1338"; }
    }

}
