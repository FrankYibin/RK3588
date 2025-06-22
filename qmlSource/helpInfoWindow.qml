import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    property int qmlscreenIndicator:  UIScreenEnum.HB_HELP

    Component.onCompleted:
    {
        helpModel.resetModel()
    }

    QtObject {
        id: manualScreenIndex
        readonly property int manual:   0
        readonly property int device:   1
    }

    function updateTabBar(index)
    {
        screenLoader.source = ""
        switch(index)
        {
        case manualScreenIndex.manual:
            screenLoader.source = "qrc:/qmlSource/HelpOperateWindow.qml"
            break;
            // case manualScreenIndex.device:
            //     screenLoader.source = "qrc:/qmlSource/HelpDeviceWindow.qml"
            //     break;
        default:
            break;
        }
    }

    ListModel {
        id: helpModel
        function resetModel()
        {
            helpModel.clear()
            helpModel.append({"Title":  qsTr("操作说明"),
                                 "Width":  100,
                                 "Index":  0})
            // helpModel.append({"Title":  qsTr("设备说明"),
            //                      "Width":  100,
            //                      "Index":  1})

        }
    }


    TabBar {
        id: manualTabBar
        anchors.left: parent.left
        anchors.top: parent.top
        width: parent.width
        height: Math.round(30 * Style.scaleHint)
        spacing: 20
        background: Image {
            source: "qrc:/images/bg1.png"
            anchors.fill: parent
            smooth: true
        }

        Repeater {
            id: tabbtn
            model: helpModel
            delegate: HBTabButton {
                anchors.top: parent.top
                width: Math.round(model.Width * Style.scaleHint)
                height: parent.height
                tabbtnText: model.Title
                onClicked: {
                    updateTabBar(model.Index)
                }
            }
        }
    }

    Row {
        id: versionInfoRow
        anchors.top: parent.top
        anchors.topMargin: Math.round(7 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(150 * Style.scaleHint)
        spacing: Math.round(20 * Style.scaleHint)
        z:10

        Text {
            id: deviceIDInfo
            text: qsTr("设备ID") + ": " + Configuration.DeviceID
            font.family: "宋体"
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            verticalAlignment: Text.AlignVCenter
            color: Style.whiteFontColor
        }
        Text {
            id: softwareVersionInfo
            text: qsTr("软件版本") + ": " + Configuration.SoftwareVersion
            font.family: "宋体"
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            verticalAlignment: Text.AlignVCenter
            color: Style.whiteFontColor
        }
        Text {
            id: hardwareVersionInfo
            text: qsTr("硬件版本") + ": " + Configuration.HardwareVersion
            font.family: "宋体"
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            verticalAlignment: Text.AlignVCenter
            color: Style.whiteFontColor
        }
    }

    Loader{
        id: screenLoader
        width: parent.width
        anchors.top: manualTabBar.bottom
        anchors.topMargin: Math.round(20 * Style.scaleHint)
        anchors.bottom: parent.bottom
        source:  "qrc:/qmlSource/HelpOperateWindow.qml"
    }
}


