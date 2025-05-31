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
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_VEDIO

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
}



