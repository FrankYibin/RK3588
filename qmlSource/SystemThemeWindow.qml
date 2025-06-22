import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_HISTORY_DATA

    Component.onCompleted:
    {
        themeModel.resetModel()
    }

    Rectangle
    {
        id: background
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: parent.height
        gradient: Gradient {
            GradientStop { position: 0.0; color: Style.backgroundLightColor }
            GradientStop { position: 1.0; color: Style.backgroundDeepColor }
        }
    }

    QtObject {
        id: themeIndex
        readonly property int background1:      0
        readonly property int background2:      1
        readonly property int background3:      2
    }

    ListModel {
        id: themeModel
        function resetModel()
        {
            themeModel.clear()
            themeModel.append({"Title":      qsTr("主题1"),
                                  "Source":     "qrc:/images/bg1.png",
                                  "Index":      themeIndex.background1})
            themeModel.append({"Title":      qsTr("主题2"),
                                  "Source":     "qrc:/images/bg2.png",
                                  "Index":      themeIndex.background2})
            themeModel.append({"Title":      qsTr("主题3"),
                                  "Source":     "qrc:/images/bg3.png",
                                  "Index":      themeIndex.background3})

        }
    }

    Row {
        id: themeLayout
        anchors.centerIn: parent
        width: Math.round((3 * 150 + 2 * 50)  * Style.scaleHint)
        height: Math.round(300 * Style.scaleHint)
        spacing: Math.round(50 * Style.scaleHint)
        ExclusiveGroup {id: buttonOptionGroup}
        property int currentIndex: 0
        Repeater {
            id: themebtn

            model: themeModel
            delegate: Item
            {
                width: Math.round(150 * Style.scaleHint)
                height: Math.round(300 * Style.scaleHint)
                Image{
                    id: themeBackground
                    width: parent.width
                    height: parent.height - Math.round(50 * Style.scaleHint)
                    source: model.Source

                    sourceSize.width: parent.width
                    sourceSize.height: parent.height
                    smooth: true
                    HBPrimaryButton {
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: Math.round(10 * Style.scaleHint)
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: Math.round(100 * Style.scaleHint)
                        height: Math.round(30 * Style.scaleHint)
                        text: (checked === true) ? qsTr("应用中") : qsTr("应用")
                        fontSize: Math.round(Style.style4 * Style.scaleHint)
                        checked: (themeLayout.currentIndex === model.Index)
                        onClicked: {
                            themeLayout.currentIndex = index
                            Configuration.setThemeIndex(model.Index)
                            console.debug("11111111111:", themeLayout.currentIndex)
                            // updateTabBar(model.Index)
                        }
                    }
                }
                Text{
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: model.Title
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }
        }
        Component.onCompleted:
        {
            themeModel.resetModel()
            themeLayout.currentIndex = parseInt(Configuration.ThemeIndex)
        }
    }
}


