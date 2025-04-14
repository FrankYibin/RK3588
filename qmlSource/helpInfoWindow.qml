import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_HELP

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
        case manualScreenIndex.device:
            screenLoader.source = "qrc:/qmlSource/HelpDeviceWindow.qml"
            break;
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
            helpModel.append({"Title":  qsTr("设备说明"),
                              "Width":  100,
                              "Index":  1})

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

    Loader{
        id: screenLoader
        width: parent.width
        anchors.top: manualTabBar.bottom
        anchors.topMargin: Math.round(20 * Style.scaleHint)
        anchors.bottom: parent.bottom
        source:  "qrc:/qmlSource/HelpOperateWindow.qml"
    }
}


