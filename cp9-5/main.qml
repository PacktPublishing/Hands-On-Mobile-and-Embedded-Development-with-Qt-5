import QtQuick 2.11
import QtQuick.Window 2.11
import QtMultimedia 5.8
import QtQuick.Controls 2.4

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Sounds and Visions")

    property bool isCameraAvailable: QtMultimedia.availableCameras.length > 0

    Camera {
        id: camera
        position: Camera.BackFace
        onCameraStateChanged: console.log("cameraState " + cameraState)
        imageCapture {
            onImageCaptured: {
                console.log("Image captured")
            }
        }
        onCameraStatusChanged: console.log("status "+cameraStatus)
        videoRecorder {
            //       audioEncodingMode: CameraRecorder.ConstantBitrateEncoding;
            audioBitRate: 128000
            mediaContainer: "mp4"
            onRecorderStateChanged: {
                console.log("recorderState " + recorderState)
                if (recorderState === CameraRecorder.StoppedState
                        && errorCode != Camera.NoError)
                    console.log("[qmlvideo] CameraRecorder.onError error " + error + " errorString " + errorString)
            }
            onDurationChanged: {
                console.log("duration "+ duration)
            }
            onActualLocationChanged: {
                console.log("actualLocation "+ actualLocation)
            }
            onRecorderStatusChanged: console.log("recorder status "+ recorderStatus)
        }

        onError: {
            if (error != Camera.NoError) {
                console.log("[qmlvideo] CameraItem.onError error " + error + " errorString " + errorString)
            }
        }
    }

    VideoOutput {
        id: viewfinder
        source: camera
        autoOrientation: true

        MouseArea {
            anchors.fill: parent
            onPressAndHold: {
                captureMode: captureSwitch.position === 0 ? Camera.CaptureStillImage
                                                          : Camera.CaptureVideo
                if (captureSwitch.position === 0)
                    camera.imageCapture.capture()
                else {
                    console.log("record video")
                    camera.start()
                    camera.videoRecorder.record()
                    console.log("recorder status "+ camera.recorderStatus)
                    console.log("recorderState " + camera.videoRecorder.recorderState)
                    console.log("error "+ camera.videoRecorder.errorString)
                }
            }

            onClicked: {
                console.log("recorderState " + camera.videoRecorder.recorderState)
                if (camera.videoRecorder.recorderState === CameraRecorder.RecordingState) {
                    console.log("stop recording video")
                    camer.stop()
                    camera.videoRecorder.stop()
                } else {
                    if (camera.lockStatus == Camera.Unlocked)
                        camera.unlock();

                    camera.searchAndLock();
                }
            }
        }
    }

    Switch {
        id: captureSwitch
        text: position == 0 ? "Capture Image" : "Capture Video"
        onPositionChanged: {
            console.log("position "+ position)

        }
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
    }
}
