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
        VideoOutput {
            id: videoOutput
            anchors.fill: parent
            source: "v4l2src device=/dev/video0 ! video/x-raw,format=BGR,framerate=60/1 ! videoconvert ! video/x-raw,format=RGBA ! qtvideo"
        }
    }
}


