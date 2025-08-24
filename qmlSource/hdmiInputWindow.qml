import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import HB.Modbus 1.0
import HB.Enums 1.0
import DepthGlobalDefine 1.0
import QtMultimedia 5.15

Item{
    readonly property int qmlscreenIndicator: UIScreenEnum.HB_HDMI
    Item {
        id: videoContainer
        width: parent.width
        height: parent.height
        anchors.centerIn: parent

        MediaPlayer {
            id: mediaPlayer
            autoPlay: true


            source: "gst-pipeline: v4l2src device=/dev/video0 !  videoconvert ! video/x-raw ! qtvideosink"

            onError: {
                console.error("MediaPlayer error:", errorString)


            }
            onPlaying:{
                console.log("MediaPlayer playing")

            }
        }

        Item {
            id: video
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

    }

    Column {
        spacing: Math.round(10 * Style.scaleHint)
        anchors.top: parent.top
        anchors.right: parent.right
        Text {
            id: textCurrentTime
            text: qsTr("时间") + "：" + Qt.formatDateTime(new Date(), "yyyy-MM-dd HH:mm:ss")
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            color: Style.whiteFontColor
            font.family: "宋体"
        }

        Text {
            text: qsTr("深度") + "：" + HBHome.DepthCurrent + " " + DepthGlobalDefine.distanceUnitModel[Depth.DistanceUnit]
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            color: Style.whiteFontColor
            font.family: "宋体"
        }

        Text {
            text: qsTr("速度") + "：" + HBHome.VelocityCurrent + " " + DepthGlobalDefine.velocityUnitModel[Depth.VelocityUnit]
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            color: Style.whiteFontColor
            font.family: "宋体"
        }

        Text {
            text: qsTr("张力") + "：" + HBHome.TensionCurrent + " " + TensionsGlobalDefine.tensionUnitModel[TensionSetting.TensionUnit]
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            color: Style.whiteFontColor
            font.family: "宋体"
        }

        Text {
            text: qsTr("张力增量") + "：" + HBHome.TensionCurrentDelta + " " + TensionsGlobalDefine.tensionUnitModel[TensionSetting.TensionUnit] + "/s"
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            color: Style.whiteFontColor
            font.family: "宋体"
        }
    }
    Timer {
        //id:myTimer
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            textCurrentTime.text = qsTr("时间") + "：" + Qt.formatDateTime(new Date(), "yyyy-MM-dd HH:mm:ss")
        }
    }


    HBPrimaryButton
    {
        id: btnClose
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(10 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(10 * Style.scaleHint)
        width: Math.round(100 * Style.scaleHint)
        height: Math.round(30 * Style.scaleHint)
        text: qsTr("返回")
        fontSize: Math.round(Style.style5 * Style.scaleHint)
        onClicked:
        {
           mainWindow.menuParentOptionSelect(UIScreenEnum.HB_DASHBOARD)
        }
    }
}



