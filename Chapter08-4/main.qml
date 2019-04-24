import QtQuick 2.11
import QtQuick.Window 2.11
import QtLocation 5.11
import QtPositioning 5.11

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello Map")
    property variant startCoordinate: QtPositioning.coordinate(-28.0, 153.4)
    property variant endCoordinate: QtPositioning.coordinate(-27.579744, 153.100175)

    Map {
        id: map
        anchors.fill: parent
        center: QtPositioning.coordinate(-28.0, 153.4)
        zoomLevel: 12
        plugin: Plugin {
            id: mapPlugin
            name: "osm"
            PluginParameter {
//                name: 'osm.mapping.highdpi_tiles'
                name: 'here.mapping.highdpi_tiles'
                value: false
            }
            PluginParameter {
                id: appId
                name: 'here.app_id'
                value: 'your_here_app_id_here'
            }
            PluginParameter {
                name: 'here.token'
                value: 'your_here_token_here'
            }
        }

        MapCircle {
            center {
                latitude: -28.0
                longitude: 153.4
            }
            radius: 5000.0
            border.color: 'red'
            border.width: 3
            opacity: 0.5
        }

        RouteQuery {
            id: routeQuery
        }

        RouteModel {
            id: routeModel
            plugin : map.plugin
            query: routeQuery
        }

        MapItemView {
            id: mapView
            model: routeModel
            delegate: routeDelegate
        }

        Component {
            id: routeDelegate

            MapRoute {
                id: route
                route: routeData
                line.color: "#46a2da"
                line.width: 5
                smooth: true
                opacity: 0.8
            }
        }

        MapItemView {
            id: searchView
            model: searchModel
            delegate: MapQuickItem {
                coordinate: place.location.coordinate

                anchorPoint.x: image.width * 0.5
                anchorPoint.y: image.height

                sourceItem: Column {
                    Image { id: image; source: "map-pin.png" }
                    Text { text: title; font.bold: true; color: "red"}
                }
            }
        }

        Component.onCompleted: {
            if (appId.name === 'here.app_id') {
                console.log("You need to set HERE app id and HERE token")
            } else {
                routeQuery.clearWaypoints();
                routeQuery.addWaypoint(startCoordinate)
                routeQuery.addWaypoint(endCoordinate)
                routeQuery.travelModes = RouteQuery.CarTravel
                routeQuery.routeOptimizations = RouteQuery.FastestRoute

                routeModel.update();
            }
        }
    }

    PlaceSearchModel {
        id: searchModel
        plugin: mapPlugin
        searchTerm: "coffee"
        searchArea: routeDelegate.route ? QtPositioning.path(map.routeModel.routeDelegate.route.path) : ''
        Component.onCompleted: {
            if (appId.name === 'here.app_id') {
                console.log("You need to set HERE app id and HERE token")
            } else {
                update()
            }
        }
    }
}
