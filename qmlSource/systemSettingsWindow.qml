import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    property int qmlscreenIndicator:  UIScreenEnum.HB_SYSTEM_CONFIG

    Component.onCompleted:
    {
        systemSettingModel.resetModel()
    }

    QtObject {
        id: systemScreenIndex
        readonly property int serial:   0
        readonly property int network:  1
        readonly property int theme:    2
        readonly property int language: 3
    }

    function updateTabBar(index)
    {
        screenLoader.source = ""
        switch(index)
        {
        case systemScreenIndex.serial:
            screenLoader.source = "qrc:/qmlSource/SystemSerialWindow.qml"
            break;
        case systemScreenIndex.network:
            screenLoader.source = "qrc:/qmlSource/SystemNetworkWindow.qml"
            break;
        case systemScreenIndex.theme:
            screenLoader.source = "qrc:/qmlSource/SystemThemeWindow.qml"
            break;
        case systemScreenIndex.language:
            screenLoader.source = "qrc:/qmlSource/SystemLanguageWindow.qml"
            break;
        default:
            break;
        }
    }


    ListModel {
        id: systemSettingModel
        function resetModel()
        {
            systemSettingModel.clear()
            systemSettingModel.append({"Title":      "地面系统串口",
                                        "Width":      100,
                                        "Index":      systemScreenIndex.serial})
            systemSettingModel.append({"Title":      "网络设置",
                                        "Width":      100,
                                        "Index":      systemScreenIndex.network})
            systemSettingModel.append({"Title":      "主题切换",
                                        "Width":      100,
                                        "Index":      systemScreenIndex.theme})
            systemSettingModel.append({"Title":      "时间和语言设置",
                                        "Width":      110,
                                        "Index":      systemScreenIndex.language})

        }
    }


    TabBar {
        id: systemTabBar
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
            model: systemSettingModel
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
        anchors.top: systemTabBar.bottom
        anchors.topMargin: Math.round(20 * Style.scaleHint)
        anchors.bottom: parent.bottom
        source:  "qrc:/qmlSource/SystemSerialWindow.qml"
    }
}


