/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtQml.Models 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item {
    id: leftNavigateMenuItem
    readonly property int imageSize: Math.round(50 * Style.scaleHint)
    property var menuName: "主页"
    property var screenIndex: -1
    property var parentMenuEnabledIndex: -1
    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted:
    {
        modelMenuData.resetModel()
        modelMenuData.set(0, {"MenuEnabled": true})

    }

    function updateModel(index, menuName)
    {
        var menuEnabled = modelMenuData.get(index).MenuEnabled
        if(menuEnabled === true)
            return
        var menuIndex = modelMenuData.get(index).MenuIndex
        var isSubmenu = modelMenuData.get(index).IsSubmenu
        if(isSubmenu === true)
            parentMenuEnabledIndex = index

        else if(menuIndex === UIScreenEnum.HB_RETURN)
        {
            mainWindow.menuOptionLookAt(screenIndex)
            modelMenuData.resetModel()
            modelMenuData.set(1, {"MenuEnabled": true})
            return
        }

        for(var i = 0; i < modelMenuData.count; i++)
        {
            modelMenuData.set(i, {"MenuEnabled": false})
        }
        modelMenuData.set(index, {"MenuEnabled": true})
        mainWindow.menuParentOptionSelect(menuIndex)

    }

    function updateChildModel(index, menuName)
    {
        screenIndex = index
        switch(index)
        {
        case UIScreenEnum.HB_HISTORY_DATA:
            modelMenuData.historyModel()
            break;
        case UIScreenEnum.HB_SYSTEM_CONFIG:
            modelMenuData.systemModel()
            break;
        case UIScreenEnum.HB_WELL_PARAMETERS:
            modelMenuData.wellModel()
            break;
        case UIScreenEnum.HB_TENSIONS_SETTING:
            modelMenuData.tensionsModel()
            break;
        case UIScreenEnum.HB_DEPTH_SETTING:
            modelMenuData.depthModel()
            break;
        case UIScreenEnum.HB_USER_MANAGEMENT:
            modelMenuData.userModel()
            break;
        case UIScreenEnum.HB_HELP:
            modelMenuData.helpModel()
            break;
        default:
            break;
        }
    }

    ListModel {
        id: modelMenuData
        function resetModel()
        {
            modelMenuData.clear()
            modelMenuData.append({"MenuName":       qsTr("主页"),
                                  "MenuIcon":       "qrc:/images/homePage.png",
                                  "IsSubmenu":      false,
                                  "MenuIndex":      UIScreenEnum.HB_DASHBOARD,
                                  "ImageSize":      Math.round(50 * Style.scaleHint),
                                  "FontSize":       Math.round(Style.style4 * Style.scaleHint),
                                  "MenuEnabled":    false,
                                      })
            modelMenuData.append({"MenuName":       qsTr("设置"),
                                  "MenuIcon":       "qrc:/images/setting.png",
                                  "IsSubmenu":      true,
                                  "MenuIndex":      UIScreenEnum.HB_SETTING,
                                  "ImageSize":      Math.round(45 * Style.scaleHint),
                                  "FontSize":       Math.round(Style.style4 * Style.scaleHint),
                                  "MenuEnabled":    false,
                                      })
            modelMenuData.append({"MenuName":       qsTr("控速"),
                                    "MenuIcon":     "qrc:/images/velocity.png",
                                    "IsSubmenu":    false,
                                    "MenuIndex":    UIScreenEnum.HB_VELOCITY,
                                    "ImageSize":    Math.round(50 * Style.scaleHint),
                                    "FontSize":       Math.round(Style.style4 * Style.scaleHint),
                                    "MenuEnabled":  false,
                                      })
            modelMenuData.append({"MenuName":       qsTr("地面仪界面"),
                                  "MenuIcon":       "qrc:/images/hdmi.jpg",
                                  "IsSubmenu":      false,
                                  "MenuIndex":      UIScreenEnum.HB_HDMI,
                                  "ImageSize":      Math.round(50 * Style.scaleHint),
                                  "FontSize":       Math.round(Style.style3 * Style.scaleHint),
                                  "MenuEnabled":    false})
            modelMenuData.append({"MenuName":       qsTr("井口监控"),
                                  "MenuIcon":       "qrc:/images/video.jpg",
                                  "IsSubmenu":      false,
                                  "MenuIndex":      UIScreenEnum.HB_VIDEO,
                                  "ImageSize":      Math.round(50 * Style.scaleHint),
                                  "FontSize":       Math.round(Style.style4 * Style.scaleHint),
                                  "MenuEnabled":    false})
        }

        function historyModel()
        {
            modelMenuData.clear()
            modelMenuData.append({"MenuName":   "历史数据",
                                 "MenuIcon":    "qrc:/images/history.png",
                                 "IsSubmenu":   false,
                                 "MenuIndex":   UIScreenEnum.HB_HISTORY_DATA,
                                 "ImageSize":   Math.round(45 * Style.scaleHint),
                                 "FontSize":    Math.round(Style.style4 * Style.scaleHint),
                                 "MenuEnabled": true
                                 })
            modelMenuData.append({"MenuName":   "返回",
                                 "MenuIcon":    "qrc:/images/back.png",
                                 "IsSubmenu":   false,
                                 "MenuIndex":   UIScreenEnum.HB_RETURN,
                                 "ImageSize":   Math.round(40 * Style.scaleHint),
                                 "FontSize":    Math.round(Style.style4 * Style.scaleHint),
                                 "MenuEnabled": false
                                 })

        }

        function systemModel()
        {
            modelMenuData.clear()
            modelMenuData.append({"MenuName":   "系统设置",
                                 "MenuIcon":    "qrc:/images/system.png",
                                 "IsSubmenu":   false,
                                 "MenuIndex":   UIScreenEnum.HB_SYSTEM_CONFIG,
                                 "ImageSize":   Math.round(40 * Style.scaleHint),
                                 "FontSize":    Math.round(Style.style4 * Style.scaleHint),
                                 "MenuEnabled": true
                                 })
            modelMenuData.append({"MenuName":   "返回",
                                 "MenuIcon":    "qrc:/images/back.png",
                                 "IsSubmenu":   false,
                                 "MenuIndex":   UIScreenEnum.HB_RETURN,
                                 "ImageSize":   Math.round(40 * Style.scaleHint),
                                 "FontSize":    Math.round(Style.style4 * Style.scaleHint),
                                 "MenuEnabled": false
                                 })

        }

        function wellModel()
        {
            modelMenuData.clear()
            modelMenuData.append({"MenuName":   "井况参数",
                                 "MenuIcon":    "qrc:/images/parameter.png",
                                 "IsSubmenu":   false,
                                 "MenuIndex":   UIScreenEnum.HB_WELL_PARAMETERS,
                                 "ImageSize":   Math.round(40 * Style.scaleHint),
                                 "FontSize":    Math.round(Style.style4 * Style.scaleHint),
                                 "MenuEnabled": true
                                 })
            modelMenuData.append({"MenuName":   "返回",
                                 "MenuIcon":    "qrc:/images/back.png",
                                 "IsSubmenu":   false,
                                 "MenuIndex":   UIScreenEnum.HB_RETURN,
                                 "ImageSize":   Math.round(40 * Style.scaleHint),
                                 "FontSize":    Math.round(Style.style4 * Style.scaleHint),
                                 "MenuEnabled": false
                                 })

        }

        function tensionsModel()
        {
            modelMenuData.clear()
            modelMenuData.append({"MenuName":   "张力设置",
                                 "MenuIcon":    "qrc:/images/tension.png",
                                 "IsSubmenu":   false,
                                 "MenuIndex":   UIScreenEnum.HB_TENSIONS_SETTING,
                                 "ImageSize":   Math.round(55 * Style.scaleHint),
                                 "FontSize":    Math.round(Style.style4 * Style.scaleHint),
                                 "MenuEnabled": true
                                 })
            modelMenuData.append({"MenuName":   "返回",
                                 "MenuIcon":    "qrc:/images/back.png",
                                 "IsSubmenu":   false,
                                 "MenuIndex":   UIScreenEnum.HB_RETURN,
                                 "ImageSize":   Math.round(40 * Style.scaleHint),
                                 "FontSize":    Math.round(Style.style4 * Style.scaleHint),
                                 "MenuEnabled": false
                                 })

        }

        function depthModel()
        {
            modelMenuData.clear()
            modelMenuData.append({"MenuName":   "深度设置",
                                 "MenuIcon":    "qrc:/images/depth.png",
                                 "IsSubmenu":   false,
                                 "MenuIndex":   UIScreenEnum.HB_DEPTH_SETTING,
                                 "ImageSize":   Math.round(50 * Style.scaleHint),
                                 "FontSize":    Math.round(Style.style4 * Style.scaleHint),
                                 "MenuEnabled": true
                                 })
            modelMenuData.append({"MenuName":   "返回",
                                 "MenuIcon":    "qrc:/images/back.png",
                                 "IsSubmenu":   false,
                                 "MenuIndex":   UIScreenEnum.HB_RETURN,
                                 "ImageSize":   Math.round(40 * Style.scaleHint),
                                 "FontSize":    Math.round(Style.style4 * Style.scaleHint),
                                 "MenuEnabled": false
                                 })

        }

        function userModel()
        {
            modelMenuData.clear()
            modelMenuData.append({"MenuName":   "用户管理",
                                 "MenuIcon":    "qrc:/images/user.png",
                                 "IsSubmenu":   false,
                                 "MenuIndex":   UIScreenEnum.HB_USER_MANAGEMENT,
                                 "ImageSize":   Math.round(40 * Style.scaleHint),
                                 "FontSize":    Math.round(Style.style4 * Style.scaleHint),
                                 "MenuEnabled": true
                                 })
            modelMenuData.append({"MenuName":   "返回",
                                 "MenuIcon":    "qrc:/images/back.png",
                                 "IsSubmenu":   false,
                                 "MenuIndex":   UIScreenEnum.HB_RETURN,
                                 "ImageSize":   Math.round(40 * Style.scaleHint),
                                 "FontSize":    Math.round(Style.style4 * Style.scaleHint),
                                 "MenuEnabled": false
                                 })
        }

        function helpModel()
        {
            modelMenuData.clear()
            modelMenuData.append({"MenuName":   "帮助",
                                 "MenuIcon":    "qrc:/images/help.png",
                                 "IsSubmenu":   false,
                                 "MenuIndex":   UIScreenEnum.HB_HELP,
                                 "ImageSize":   Math.round(45 * Style.scaleHint),
                                 "FontSize":    Math.round(Style.style4 * Style.scaleHint),
                                 "MenuEnabled": true
                                 })
            modelMenuData.append({"MenuName":   "返回",
                                 "MenuIcon":    "qrc:/images/back.png",
                                 "IsSubmenu":   false,
                                 "MenuIndex":   UIScreenEnum.HB_RETURN,
                                 "ImageSize":   Math.round(40 * Style.scaleHint),
                                 "FontSize":    Math.round(Style.style4 * Style.scaleHint),
                                 "MenuEnabled": false
                                 })
        }

    }

    Item{
        id: rootRectangle
        anchors.top: parent.top
        anchors.left: parent.left
        width:  parent.width
        height: parent.height

        Column
        {
            id: menuOptionLayout
            anchors.fill: parent
            spacing: Math.round(10 * Style.scaleHint)
            Repeater
            {
                model: modelMenuData
                delegate: Item
                {
                    id: menuOptionDelegate
                    width: parent.width
                    height: Math.round(width * 1.2)
                    Rectangle{
                        id: menuImageTextLayout
                        width: parent.width
                        height: parent.height
                        color: (model.MenuEnabled === true) ? Style.hbButtonBackgroundColor : Style.backgroundDeepColor
                        radius: 4
                        Item{
                            width: model.ImageSize
                            height: width + Math.round(20 * Style.scaleHint) + Math.round(3 * Style.scaleHint)
                            anchors.centerIn: parent
                            Column
                            {
                                anchors.horizontalCenter: parent.horizontalCenter
                                spacing: Math.round(3 * Style.scaleHint)
                                Image{
                                    id: menuOptionImage
                                    width: model.ImageSize
                                    height: model.ImageSize
                                    source: model.MenuIcon
                                    fillMode: Image.PreserveAspectFit
                                    smooth: true
                                    sourceSize.width: model.ImageSize
                                    sourceSize.height: model.ImageSize
                                }
                                Text{
                                    height: Math.round(20 * Style.scaleHint)
                                    width: model.ImageSize
                                    color: Style.whiteFontColor
                                    font.family: "宋体"
                                    text: model.MenuName
                                    anchors.horizontalCenter: menuOptionImage.horizontalCenter
                                    horizontalAlignment: Text.AlignHCenter
                                    font.pixelSize: model.FontSize
                                }
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
                                menuName = model.MenuName
                                updateModel(index, menuName)
                            }
                        }
                    }
                }
            }
        }
    }
}
