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
import QtQuick.Controls 1.4
import Style 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
Item {
    property string qmltextMenuName:                qsTr("AFTERBURST")
    property string qmltextAfterburstTime:          qsTr("AFTERBURST TIME")
    property string qmltextAfterburstDelay:         qsTr("AFTERBURST DELAY")
    property string qmltextAfterburstAmplitude:     qsTr("AFTERBURST AMPLITUDE")
    property string qmltextTurnAllOff:              qsTr("Turn all off")
    property var qmlTextArray: [qmltextAfterburstTime, qmltextAfterburstDelay, qmltextAfterburstAmplitude,
        qmltextTurnAllOff]

    function updateLanguage()
    {
        qmlTextArray = languageConfig.getLanguageStringList(UIScreenEnum.RECIPES_LAB_WELDPROCESS_AFTERBURST, qmlTextArray)
        qmltextAfterburstTime = qmlTextArray[textEnum.textAfterburstTimeIdx]
        qmltextAfterburstDelay = qmlTextArray[textEnum.textAfterburstDelayIdx]
        qmltextAfterburstAmplitude = qmlTextArray[textEnum.textAfterburstAmplitudeIdx]
        qmltextTurnAllOff = qmlTextArray[textEnum.textTurnAllOffIdx]
        qmltextMenuName = languageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_WELDPROCESS_AFTERBURST, qmltextMenuName)
        recipeAfterburstModel.resetModel()

    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted: {
        updateLanguage()
    }

    QtObject {
        id: textEnum
        readonly property int textAfterburstTimeIdx:        0
        readonly property int textAfterburstDelayIdx:       1
        readonly property int textAfterburstAmplitudeIdx:   2
        readonly property int textTurnAllOffIdx:            3
    }

    BransonLeftBorderRectangle {
        id: switchAfterburstAll
        width: Math.round(parent.width - recipeAfterburstGridView.rowSpacing)
        height: Math.round(parent.height / 3.5 - recipeAfterburstGridView.columnSpacing)
        property bool isTurnAllOn: false
        checked: isTurnAllOn
        Text {
            id: txtAfterburstTitle
            anchors.left: parent.left
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(7 * Style.scaleHint)
            text: qmltextMenuName
            color: Style.blackFontColor
            font.family: Style.regular.name
            font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
        }

        Text {
            id: txtTurnAllOffTitle
            anchors.right: parent.right
            anchors.rightMargin: Math.round(13 * Style.scaleHint)
            anchors.verticalCenter: txtAfterburstTitle.verticalCenter
            text: qmltextTurnAllOff
            color: Style.blackFontColor
            font.family: Style.italic.name
            font.italic: true
            font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
        }
        BransonSwitch {
            id: afterburstSwitch
            anchors.right: parent.right
            anchors.rightMargin: Math.round(25 * Style.scaleHint)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(13 * Style.scaleHint)
            onCheckedChanged: {
                if(afterburstSwitch.checked === true)
                    switchAfterburstAll.isTurnAllOn = true
                else
                    switchAfterburstAll.isTurnAllOn = false
            }
        }
    }

    ListModel {
        id: recipeAfterburstModel
        function resetModel()
        {
            recipeAfterburstModel.clear()
            recipeAfterburstModel.append({"Title":      qmltextAfterburstTime,
                                          "Value":      "0.500",
                                          "Unit":       "S",
                                          "Minimum":    0.000,
                                          "Maximum":    5.000,
                                          "Decimals":   3,
                                          "Index":      0})
            recipeAfterburstModel.append({"Title":      qmltextAfterburstDelay,
                                          "Value":      "0.500",
                                          "Unit":       "S",
                                          "Minimum":    0.000,
                                          "Maximum":    5.000,
                                          "Decimals":   3,
                                          "Index":      1})
            recipeAfterburstModel.append({"Title":      qmltextAfterburstAmplitude,
                                          "Value":      "100",
                                          "Unit":       "%",
                                          "Minimum":     0,
                                          "Maximum":     100,
                                          "Decimals":    0,
                                          "Index":       2})
        }
    }

    Grid {
        id: recipeAfterburstGridView
        anchors.top: switchAfterburstAll.bottom
        anchors.topMargin: recipeAfterburstGridView.columnSpacing
        anchors.bottom: parent.bottom
        width: parent.width
        rows: 2
        columns: 2
        rowSpacing: Math.round(11 * Style.scaleHint)
        columnSpacing: Math.round(8 * Style.scaleHint)

        Repeater {
            model: recipeAfterburstModel
            delegate: BransonLeftBorderRectangle
            {
                id: optionAfterburst
                width: Math.round(parent.width / 2 - recipeAfterburstGridView.rowSpacing)
                height: switchAfterburstAll.height
                checked: switchAfterburstAll.isTurnAllOn
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onReleased: {
                        if(switchAfterburst.checked === true)
                            mainWindow.showPrimaryNumpad(model.Title, model.Unit, model.Decimals, model.Minimum, model.Maximum, model.Value)
                    }
                }

                Text {
                    id: txtTitle
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(20 * Style.scaleHint)
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(7 * Style.scaleHint)
                    text: model.Title
                    color: Style.blackFontColor
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                }

                BransonSwitch {
                    id: switchAfterburst
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(20 * Style.scaleHint)
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: Math.round(13 * Style.scaleHint)
                    enabled: optionAfterburst.checked
                }

                Text {
                    id: txtAfterburstValue
                    anchors.right: parent.right
                    anchors.rightMargin: Math.round(14 * Style.scaleHint)
                    anchors.verticalCenter: switchAfterburst.verticalCenter
                    text: model.Value + model.Unit
                    color: Style.blackFontColor
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    visible: switchAfterburst.checked
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }
}
