﻿import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    property int qmlscreenIndicator:  UIScreenEnum.HB_TENSIONS_SETTING
    Component.onCompleted:
    {
        tensionsSettingModel.resetModel()
    }
    QtObject {
        id: tensionsScreenIndex
        readonly property int meterScale:       0
        readonly property int upperSetting:     1
        readonly property int configuration:    2
    }

    function updateTabBar(index)
    {
        screenLoader.source = ""
        switch(index)
        {
        case tensionsScreenIndex.meterScale:
            screenLoader.source = "qrc:/qmlSource/TensionsMeterScaleWindow.qml"
            break;
        case tensionsScreenIndex.upperSetting:
            screenLoader.source = "qrc:/qmlSource/TensionsUpperSettingWindow.qml"
            break;
        case tensionsScreenIndex.configuration:
            screenLoader.source = "qrc:/qmlSource/TensionsConfigurationWindow.qml"
            break;
        default:
            break;
        }
    }

    ListModel {
        id: tensionsSettingModel
        function resetModel()
        {
            tensionsSettingModel.clear()
            tensionsSettingModel.append({"Title":      "张力计刻度",
                                        "Width":      100,
                                        "Index":      tensionsScreenIndex.meterScale})
            tensionsSettingModel.append({"Title":      "安全张力",
                                        "Width":      100,
                                        "Index":      tensionsScreenIndex.upperSetting})
            tensionsSettingModel.append({"Title":      "张力设置",
                                        "Width":      110,
                                        "Index":      tensionsScreenIndex.configuration})

        }
    }


    TabBar {
        id: tensionsTabBar
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
            model: tensionsSettingModel
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
        anchors.top: tensionsTabBar.bottom
        anchors.topMargin: Math.round(20 * Style.scaleHint)
        anchors.bottom: parent.bottom
        source:  "qrc:/qmlSource/TensionsMeterScaleWindow.qml"
    }
}


