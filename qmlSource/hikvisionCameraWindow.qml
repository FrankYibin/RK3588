import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtMultimedia 5.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import HB.Modbus 1.0
import HB.Enums 1.0
import DepthGlobalDefine 1.0

Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_VIDEO


    MediaPlayer {
        id: mediaPlayer
        autoPlay: true
        source: "rtsp://admin:a123456789@192.168.1.64/h264/ch1/main/av_stream"
        onError: {
            console.error("MediaPlayer error:", errorString)
        }
    }

    Item {
        id: videoContainer
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        VideoOutput {
            id: videoOutput
            anchors.fill: parent
            source: mediaPlayer
            fillMode: VideoOutput.Stretch
        }
    }

    Column {
        spacing: Math.round(10 * Style.scaleHint)
        anchors.top: parent.top
        anchors.right: parent.right
        Text {
                id: textCurrentTime
                text: "时间：" + Qt.formatDateTime(new Date(), "yyyy-MM-dd HH:mm:ss")
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                color: Style.whiteFontColor

                Timer {
                    interval: 1000
                    running: true
                    repeat: true
                    onTriggered: {
                        textCurrentTime.text = "时间：" + Qt.formatDateTime(new Date(), "yyyy-MM-dd HH:mm:ss")
                    }
                }
            }

        Text {
            text: "深度：" + HBHome.DepthCurrent + " " + DepthGlobalDefine.distanceUnitModel[Depth.DistanceUnit]
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            color: Style.whiteFontColor
        }

        Text {
            text: "速度：" + HBHome.VelocityCurrent + " " + DepthGlobalDefine.velocityUnitModel[Depth.VelocityUnit]
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            color: Style.whiteFontColor
        }

        Text {
            text: "张力：" + HBHome.TensionCurrent + " " + TensionsGlobalDefine.tensionUnitModel[TensionSetting.TensionUnit]
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            color: Style.whiteFontColor
        }

        Text {
            text: "张力增量：" + HBHome.TensionCurrentDelta + " " + TensionsGlobalDefine.tensionUnitModel[TensionSetting.TensionUnit] + "/s"
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            color: Style.whiteFontColor
        }
    }
}



