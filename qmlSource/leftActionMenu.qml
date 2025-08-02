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
//    width: Math.round(800 * Style.scaleHint) //while using as element that value will over write this values
//    height: Math.round(480 * Style.scaleHint)

    id: leftActionCenterItem

    property string qmltextMenu: qsTr("MENU")

    property int arcWidth: Math.round((732-359) * Style.scaleHint)
    readonly property int arcRadius: Math.round(732 / 2 * Style.scaleHint)
    readonly property int centerX: Math.round(arcWidth - arcRadius)
    readonly property int centerY: Math.round(height / 2)
    readonly property int imageSize: Math.round(30 * Style.scaleHint)
    readonly property int menuSepratorHeight: (Style.scaleHint == 1.0)? 1 : 2
    property alias leftActionAnimation: leftActionAnimation

    //qsTr can keep the word with English as the default without any messy code on the others Windows OS.
    property string qmltextDashboard:  qsTr("DASHBOARD")
    property string qmltextRecipe:     qsTr("RECIPES")
    property string qmltextProduction: qsTr("PRODUCTION")
    property string qmltextAnalytics:  qsTr("ANALYTICS")
    property string qmltextSystem:     qsTr("SYSTEM")

    property var qmlTextArray: [qmltextMenu, qmltextRecipe, qmltextProduction, qmltextAnalytics, qmltextSystem]

    property var menuIndex: UIScreenEnum.PRODUCTION
    property var menuName: qmltextProduction




    function updateLanguage()
    {
        qmlTextArray = languageConfig.getLanguageStringList(UIScreenEnum.LEFTMENU, qmlTextArray)
        qmltextMenu = qmlTextArray[textEnum.menuIdx]
        for(var i = 0; i < leftMenuModelData.count; i++)
        {
            leftMenuModelData.set(i, {"MenuName": qmlTextArray[i+1]})
        }
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted:
    {
        leftActionAnimationReturn.restart()
        leftMenuModelData.resetModel()
        updateLanguage()
    }

    QtObject {
        id: textEnum
        readonly property int menuIdx:          0
        readonly property int recipeIdx:        1
        readonly property int productionIdx:    2
        readonly property int analyticsIdx:     3
        readonly property int systemIdx:        4
    }

    ListModel {
        id: leftMenuModelData
        function resetModel()
        {
            leftMenuModelData.clear()
            leftMenuModelData.append({"MenuName":   qmltextRecipe,
                                    "MenuIcon":     "qrc:/images/recipe.svg",
                                    "MenuAction":   "RecipeListView.qml",
                                    "MenuColor":    "#ffffff",
                                    "MenuIndex":    UIScreenEnum.RECIPES,
                                    "MenuVisible":  true,
                                    "MenuSeparator": true
                                      })
            leftMenuModelData.append({"MenuName":   qmltextProduction,
                                     "MenuIcon":     "qrc:/images/production.svg",
                                    "MenuAction":   "ProductionView.qml",
                                    "MenuColor":    "#ffffff",
                                    "MenuIndex":    UIScreenEnum.PRODUCTION,
                                    "MenuVisible":  true,
                                    "MenuSeparator": true
                                      })
            leftMenuModelData.append({"MenuName":   qmltextAnalytics,
                                     "MenuIcon":     "qrc:/images/analytics.svg",
                                    "MenuAction":   "AnalyticsView.qml",
                                    "MenuColor":    "#ffffff",
                                    "MenuIndex":    UIScreenEnum.ANALYTICS,
                                    "MenuVisible":  true,
                                    "MenuSeparator": true
                                      })
            leftMenuModelData.append({"MenuName":   qmltextSystem,
                                    "MenuIcon":     "qrc:/images/system.svg",
                                    "MenuAction":   "System.qml",
                                    "MenuColor":    "#ffffff",
                                    "MenuIndex":    UIScreenEnum.SYSTEM,
                                    "MenuVisible":  true,
                                    "MenuSeparator": false
                                     })
        }
    }

    NumberAnimation on x
    {
        id: leftActionAnimationReturn
        from: 0
        to: -width
        duration: 250

    }


    NumberAnimation on x
    {
        id: leftActionAnimation
        from: -width
        to: 0
        duration: 250
    }

    Item{
        id: rootRectangle
//        color: "transparent"
        anchors.top: parent.top
        anchors.left: parent.left
        width:  arcWidth
        height: parent.height
        //For mobile screen and small screen Canvas element is not required
        z: 3
        Canvas{
            id: canvash
            anchors.left: parent.left
            anchors.top: parent.top
            width: parent.width
            height: parent.height
            opacity: 0.8
            onPaint:
            {
                var ctx = getContext("2d")
                ctx.fillStyle = Style.navigationMenuBackgroundColor
                ctx.beginPath()
                ctx.arc(0, centerY, arcRadius, 0.5 * Math.PI, 1.5 * Math.PI, true)
                ctx.fill()
            }
            MouseArea
            {
                anchors.fill: parent
            }
        }

        Item{
            id: menuDetails
            width: parent.width
            height: parent.height
            anchors.left: parent.left
            anchors.top: parent.top
            Item {
                id: backMenuButton
                anchors.left: parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: Math.round(14 * Style.scaleHint)
                height: imageSize
                width: Math.round(110 * Style.scaleHint)
                Rectangle{
                    anchors.fill: parent
                    border.color: "transparent"
                    color: "transparent"
                    Row{
                        id: menuLayout
                        spacing: Math.round(12 * Style.scaleHint)
                        Image
                        {
                            id: imageMenu
                            width: imageSize
                            height: imageSize
                            sourceSize.width: imageSize
                            sourceSize.height: imageSize
                            source: "qrc:/images/menu_close_arrow.svg"
                            fillMode: Image.PreserveAspectFit
                        }

                        Text {
                            text: qmltextMenu
                            height: imageSize
                            font.family: Style.regular.name
                            anchors.verticalCenter: imageMenu.verticalCenter
                            font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                            color: Style.whiteFontColor
                        }
                    }
                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:
                        {
                            leftActionAnimationReturn.restart()
                            mainWindow.hideMainWindowOpacity()
                        }
                    }
                }
            }

            Item {
                id: menuParentList
                anchors.left: parent.left
                anchors.leftMargin: Math.round(48 * Style.scaleHint)
                anchors.top: backMenuButton.bottom
                anchors.topMargin: Math.round(30 * Style.scaleHint)
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                Column
                {
                    id: menuOptionLayout
                    anchors.fill: parent
                    spacing: Math.round(22 * Style.scaleHint)
                    Repeater
                    {
                        model: leftMenuModelData
                        delegate: Item
                        {
                            id: menuOptionDelegate
                            height: imageSize + Math.round(22 * Style.scaleHint)
                            width: parent.width
                            Rectangle{
                                id: menuImageTextLayout
                                height: imageSize
                                width: parent.width
                                color: "transparent"
                                border.color: "transparent"
                                Row
                                {
                                    spacing: Math.round(21 * Style.scaleHint)
                                    Image{
                                        id: menuOptionImage
                                        width: imageSize
                                        height: imageSize
                                        source: model.MenuIcon
                                        fillMode: Image.PreserveAspectFit
                                        sourceSize.width: imageSize
                                        sourceSize.height: imageSize
                                        smooth: true
                                    }
                                    Text{
                                        height: imageSize
                                        color: model.MenuColor
                                        font.family: Style.regular.name
                                        text: model.MenuName
                                        anchors.verticalCenter: menuOptionImage.verticalCenter
                                        verticalAlignment: Text.AlignVCenter
                                        font.pixelSize: Math.round(Style.style7 * Style.scaleHint)
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
                                        leftActionAnimationReturn.restart()
                                        mainWindow.hideMainWindowOpacity()
                                        menuIndex = model.MenuIndex
                                        menuName = model.MenuName
                                        mainWindow.menuParentOptionSelect(menuIndex)
                                    }

                                }
                            }

                            Rectangle{
                                id: lineSeparator
                                width: Math.round(221 * Style.scaleHint)
                                height: menuSepratorHeight
                                anchors.left: menuImageTextLayout.left
                                anchors.top: menuImageTextLayout.bottom
                                anchors.topMargin: Math.round(20 * Style.scaleHint)
                                color: Style.whiteFontColor
                                visible: model.MenuSeparator
                            }
                        }
                    }
                }
            }
        }

    }

    Rectangle {
        id: leftMenuOutsideArea
        width: parent.width/5 + parent.width - arcWidth
        height: parent.height
        opacity: 0
        anchors.right: parent.right
        anchors.top: parent.top
        color: "transparent"
        visible: true
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                leftActionAnimationReturn.restart()
                mainWindow.hideMainWindowOpacity()
            }
        }
    }
}
