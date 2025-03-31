import QtQuick 2.0
import QtGraphicalEffects 1.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{

    id: leftNavigateMenuItem
    readonly property int imageSize: Math.round(45 * Style.scaleHint)
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_SETTING
    property int menuIndex: 0
    property string menuName: "历史数据"

    Rectangle
    {
        id: background
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: parent.height
        gradient: Gradient
        {
            GradientStop { position: 0.0; color: Style.backgroundLightColor }
            GradientStop { position: 1.0; color: Style.backgroundDeepColor }
        }
    }

    // Connections {
    //     target: mainWindow
    //     function onSignalCurrentLanguageChanged()
    //     {
    //         updateLanguage()
    //     }
    // }

    Component.onCompleted:
    {
        modelMenuData.resetModel()
    }

    function updateModel(index, menuName)
    {
        modelMenuData.resetModel()
        modelMenuData.set(index, {"MenuEnabled": true})
        var menuIndex = modelMenuData.get(index).MenuIndex
        mainWindow.menuChildOptionSelect(UIScreenEnum.HB_SETTING, menuIndex)
    }

    ListModel {
        id: modelMenuData
        function resetModel()
        {
            modelMenuData.clear()
            modelMenuData.append({"MenuName":   "历史数据",
                                    "MenuIcon":     "qrc:/images/history.png",
                                    "IsSubmenu":    false,
                                    "MenuIndex":    UIScreenEnum.HB_HISTORY_DATA,
                                    "MenuEnabled":  false,
                                    "ImageSize":    imageSize
                                      })
            modelMenuData.append({"MenuName":   "系统设置",
                                    "MenuIcon":     "qrc:/images/system.png",
                                    "IsSubmenu":    true,
                                    "MenuIndex":    UIScreenEnum.HB_SYSTEM_CONFIG,
                                    "MenuEnabled":  false,
                                    "ImageSize":    Math.round(40 * Style.scaleHint)
                                      })
            modelMenuData.append({"MenuName":   "井况参数",
                                    "MenuIcon":     "qrc:/images/parameter.png",
                                    "IsSubmenu":    false,
                                    "MenuIndex":    UIScreenEnum.HB_WELL_PARAMETERS,
                                    "MenuEnabled":  false,
                                    "ImageSize":    Math.round(40 * Style.scaleHint)
                                      })

            modelMenuData.append({"MenuName":   "张力设置",
                                    "MenuIcon":     "qrc:/images/tension.png",
                                    "IsSubmenu":    false,
                                    "MenuIndex":    UIScreenEnum.HB_TENSIONS_SETTING,
                                    "MenuEnabled":  false,
                                    "ImageSize":    Math.round(55 * Style.scaleHint)
                                      })
            modelMenuData.append({"MenuName":   "深度设置",
                                    "MenuIcon":     "qrc:/images/depth.png",
                                    "IsSubmenu":    true,
                                    "MenuIndex":    UIScreenEnum.HB_DEPTH_SETTING,
                                    "MenuEnabled":  false,
                                    "ImageSize":    Math.round(50 * Style.scaleHint)
                                      })
            modelMenuData.append({"MenuName":   "用户管理",
                                    "MenuIcon":     "qrc:/images/user.png",
                                    "IsSubmenu":    false,
                                    "MenuIndex":    UIScreenEnum.HB_USER_MANAGEMENT,
                                    "MenuEnabled":  false,
                                    "ImageSize":    imageSize
                                      })

            modelMenuData.append({"MenuName":   "帮助页面",
                                    "MenuIcon":     "qrc:/images/help.png",
                                    "IsSubmenu":    false,
                                    "MenuIndex":    UIScreenEnum.HB_HELP,
                                    "MenuEnabled":  false,
                                    "ImageSize":    imageSize
                                      })
        }
    }

    Item{
        id: rootRectangle
        anchors.top: parent.top
        anchors.topMargin: Math.round(50 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(50 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(50 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(50 * Style.scaleHint)

        Grid
        {
            id: menuOptionLayout
            anchors.fill: parent
            rows: 3
            columns: 3
            columnSpacing: Math.round(50 * Style.scaleHint)
            rowSpacing: Math.round(50 * Style.scaleHint)
            Repeater
            {
                model: modelMenuData
                delegate: Item
                {
                    id: menuOptionDelegate
                    width: Math.round(160 * Style.scaleHint)
                    height: Math.round(80 * Style.scaleHint)
                    Rectangle{
                        id: menuImageTextLayout
                        width: parent.width
                        height: parent.height
                        color: "transparent"
                        border.color: Style.hbFrameBorderColor
                        border.width: 2
                        Row
                        {
                            anchors.centerIn: parent
                            spacing: Math.round(10 * Style.scaleHint)
                            Image{
                                id: menuOptionImage
                                width: model.ImageSize
                                height: model.ImageSize
                                source: model.MenuIcon
                                fillMode: Image.PreserveAspectFit
                                sourceSize.width: model.ImageSize
                                sourceSize.height: model.ImageSize
                                smooth: true
                            }
                            Text{
                                height: imageSize
                                color: Style.whiteFontColor
                                font.family: "宋体"
                                text: model.MenuName
                                anchors.verticalCenter: menuOptionImage.verticalCenter
                                verticalAlignment: Text.AlignVCenter
                                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                            }
                        }
                        MouseArea
                        {
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered:
                            {
                                cursorShape = Qt.PointingHandCursor
                            }
                            onClicked:
                            {
                                menuIndex = index
                                menuName = model.MenuName
                                updateModel(menuIndex, menuName)
                            }

                        }
                    }
                }
            }
        }
    }

}


