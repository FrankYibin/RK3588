import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_DEPTH_SETTING

    Component.onCompleted:
    {
        depthSettingModel.resetModel()
    }

    QtObject {
        id: depthScreenIndex
        readonly property int configuration:   0
        readonly property int upperSetting:  1
        readonly property int countdown:    2
    }

    function updateTabBar(index)
    {
        screenLoader.source = ""
        switch(index)
        {
        case depthScreenIndex.configuration:
            screenLoader.source = "qrc:/qmlSource/DepthConfigurationWindow.qml"
            break;
        case depthScreenIndex.upperSetting:
            screenLoader.source = "qrc:/qmlSource/DepthUpperSettingWindow.qml"
            break;
        case depthScreenIndex.countdown:
            screenLoader.source = "qrc:/qmlSource/DepthCountDownWindow.qml"
            break;
        default:
            break;
        }
    }


    ListModel {
        id: depthSettingModel
        function resetModel()
        {
            depthSettingModel.clear()
            depthSettingModel.append({"Title":      "深度设置",
                                        "Width":      100,
                                        "Index":      0})
            depthSettingModel.append({"Title":      "深度安全设置",
                                        "Width":      100,
                                        "Index":      1})
            depthSettingModel.append({"Title":      "深度倒计",
                                        "Width":      100,
                                        "Index":      2})

        }
    }


    TabBar {
        id: depthTabBar
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
            model: depthSettingModel
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
        anchors.top: depthTabBar.bottom
        anchors.topMargin: Math.round(20 * Style.scaleHint)
        anchors.bottom: parent.bottom
        source:  "qrc:/qmlSource/DepthConfigurationWindow.qml"
    }

}


