/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item {
    //qsTr can keep the word with English as the default without any messy code on the others Windows OS.
    readonly property int qmlscreenIndicator:  UIScreenEnum.PRODUCTION
    property string qmltextMenuName:        qsTr("Production")
    property string qmltextActiveRecipe:    qsTr("Active Recipe")
    property string qmltextTotalCycleTIme:  qsTr("Total Cycle Time")
    property string qmltextCycleCount:      qsTr("Cycle Count")
    property string qmltextPeakPower:       qsTr("Peak Power")

    readonly property int marginSize: Math.round(20 * Style.scaleHint)
    readonly property int topHeightSize: Math.round(140 * Style.scaleHint)
    readonly property int midHeightSize: Math.round(150 * Style.scaleHint)
    readonly property int widthSize: Math.round(350 * Style.scaleHint)
    readonly property int titleSize: Math.round(30 * Style.scaleHint)

    property var qmlTextArray: [qmltextActiveRecipe, qmltextTotalCycleTIme, qmltextCycleCount, qmltextPeakPower]

    id: productionWindowItem

    function updateLanguage()
    {
        qmlTextArray = languageConfig.getLanguageStringList(UIScreenEnum.PRODUCTION, qmlTextArray)
        qmltextActiveRecipe = qmlTextArray[textEnum.activeRecipeIdx]
        qmltextTotalCycleTIme = qmlTextArray[textEnum.totalCycleTImeIdx]
        qmltextCycleCount = qmlTextArray[textEnum.cycleCountnIdx]
        qmltextPeakPower = qmlTextArray[textEnum.peakPowerIdx]
        qmltextMenuName = languageConfig.getLanguageMenuName(UIScreenEnum.PRODUCTION, qmltextMenuName)
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
        updateLanguage()
        mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.PRODUCTION)
    }

    QtObject {
        id: textEnum
        readonly property int activeRecipeIdx:      0
        readonly property int totalCycleTImeIdx:    1
        readonly property int cycleCountnIdx:       2
        readonly property int peakPowerIdx:         3
    }

    Rectangle {
        id: rectBackground
        anchors.fill: parent
        color: Style.backgroundColor
    }

    Rectangle {
        id: rectActionRecipe
        anchors.left: parent.left
        anchors.leftMargin: marginSize
        anchors.top: parent.top
        anchors.topMargin: marginSize
        height: topHeightSize
        width: widthSize
        border.width: Style.scaleHint === 1.0 ? 1 : 3
        border.color: Style.frameBorderColor
        Rectangle {
            id: rectActionRecipeTitle
            anchors.left: parent.left
            anchors.top: parent.top
            width: parent.width
            height: titleSize
            color: Style.titleBackgroundColor
            Text {
                anchors.centerIn: parent
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                color: Style.whiteFontColor
                text: qmltextActiveRecipe
            }
        }
        Rectangle{
           id: rectActionRecipeInfo
           anchors.left: parent.left
           anchors.leftMargin: parent.border.width
           anchors.top: rectActionRecipeTitle.bottom
           width: parent.width - 2 * parent.border.width
           anchors.bottom: parent.bottom
           anchors.bottomMargin: parent.border.width
           Column{
               anchors.centerIn: parent
               spacing: 10
               Text {
                   id: txtRecipeName
                   anchors.horizontalCenter: parent.horizontalCenter
                   font.family: Style.regular.name
                   font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                   color: Style.blackFontColor
                   text: productionRunInterface.ActiveRecipeNum + ": " + productionRunInterface.ActiveRecipeName
               }
               Text {
                   id: txtRecipeMode
                   anchors.horizontalCenter: parent.horizontalCenter
                   font.family: Style.regular.name
                   font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                   color: Style.blackFontColor
                   text: mainWindow.getWeldModeText(productionRunInterface.RecipeWeldMode) + ": " +
                         productionRunInterface.RecipeWeldModeValue +
                         productionRunInterface.RecipeWeldModeUnit//"Collapse Distance: 0.40 mm"
               }

           }
        }
    }

    Rectangle {
        id: rectTotalCycleTime
        anchors.right: parent.right
        anchors.rightMargin: marginSize
        anchors.top: parent.top
        anchors.topMargin: marginSize
        height: topHeightSize
        width: widthSize
        border.width: Style.scaleHint === 1.0 ? 1 : 3
        border.color: Style.frameBorderColor
        Rectangle {
            id: rectTotalCycleTimeTitle
            anchors.left: parent.left
            anchors.top: parent.top
            width: parent.width
            height: titleSize
            color: Style.titleBackgroundColor
            Text {
                anchors.centerIn: parent
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                color: Style.whiteFontColor
                text: qmltextTotalCycleTIme + " (s)"
            }
        }
        Rectangle {
           id: rectTotalCycleTimeValue
           anchors.left: parent.left
           anchors.leftMargin: parent.border.width
           anchors.top: rectTotalCycleTimeTitle.bottom
           width: parent.width - 2 * parent.border.width
           anchors.bottom: parent.bottom
           anchors.bottomMargin: parent.border.width
           Text {
               anchors.centerIn: parent
               font.family: Style.regular.name
               font.pixelSize: Math.round(Style.style8 * Style.scaleHint)
               color: Style.blackFontColor
               text: productionRunInterface.TotalCycleTime
           }
        }
    }

    Rectangle {
        id: rectCycleCount
        anchors.left: parent.left
        anchors.leftMargin: marginSize
        anchors.right: parent.right
        anchors.rightMargin: marginSize
        anchors.top: rectTotalCycleTime.bottom
        anchors.topMargin: marginSize
        height: midHeightSize
        border.width: Style.scaleHint === 1.0 ? 1 : 3
        border.color: Style.frameBorderColor
        Rectangle {
            id: rectCycleCountTitle
            anchors.left: parent.left
            anchors.top: parent.top
            width: parent.width
            height: titleSize
            color: Style.titleBackgroundColor
            Text {
                anchors.centerIn: parent
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                color: Style.whiteFontColor
                text: qmltextCycleCount
            }
        }
        Rectangle {
           id: rectCycleCountValue
           anchors.left: parent.left
           anchors.leftMargin: parent.border.width
           anchors.top: rectCycleCountTitle.bottom
           width: parent.width - 2 * parent.border.width
           anchors.bottom: parent.bottom
           anchors.bottomMargin: parent.border.width
           Text {
               anchors.centerIn: parent
               font.family: Style.regular.name
               font.pixelSize: Math.round(Style.style9 * Style.scaleHint)
               color: Style.blackFontColor
               text: productionRunInterface.CycleCount
           }
        }
    }

    BransonProgressBar {
        id: recPeakPower
        anchors.left: parent.left
        anchors.leftMargin: marginSize
        anchors.right: parent.right
        anchors.rightMargin: marginSize
        anchors.top: rectCycleCount.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: marginSize
        fontFamily: Style.regular.name
        progressValue: productionRunInterface.PeakPowerRatio
        progressTitle: qmltextPeakPower
    }
}
