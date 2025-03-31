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
    property string qmltextTime:            qsTr("TIME")
    property string qmltextEnergy:          qsTr("ENERGY")
    property string qmltextPeakPower:       qsTr("PEAK POWER")
    property string qmltextGroundDetect:    qsTr("GROUND DETECT")
    property string qmltextAbsoluteDistance:qsTr("ABSOLUTE DISTANCE")
    property string qmltextCollapseDistance:qsTr("COLLAPSE DISTANCE")
    property var qmlTextArray: [qmltextTime, qmltextEnergy, qmltextPeakPower, qmltextGroundDetect,
        qmltextAbsoluteDistance, qmltextCollapseDistance]
    signal signalCurrentWeldModeIdxChanged(int index)

    function updateLanguage()
    {
        qmlTextArray = languageConfig.getLanguageStringList(UIScreenEnum.RECIPES_LAB_WELDMODE, qmlTextArray)
        qmltextTime = qmlTextArray[textEnum.textTimeIdx]
        qmltextEnergy = qmlTextArray[textEnum.textEnergyIdx]
        qmltextPeakPower = qmlTextArray[textEnum.textPeakPowerIdx]
        qmltextGroundDetect = qmlTextArray[textEnum.textGroudDetectIdx]
        qmltextAbsoluteDistance = qmlTextArray[textEnum.textAbsoluteDistanceIdx]
        qmltextCollapseDistance = qmlTextArray[textEnum.textCollapseDistanceIdx]
        recipeModeModel.setProperty(textEnum.textTimeIdx, "modeName", qmltextTime)
        recipeModeModel.setProperty(textEnum.textEnergyIdx, "modeName", qmltextEnergy)
        recipeModeModel.setProperty(textEnum.textPeakPowerIdx, "modeName", qmltextPeakPower)
        recipeModeModel.setProperty(textEnum.textGroudDetectIdx, "modeName", qmltextGroundDetect)
//        recipeModeModel.setProperty(textEnum.textAbsoluteDistanceIdx, "modeName", qmltextAbsoluteDistance)
//        recipeModeModel.setProperty(textEnum.textCollapseDistanceIdx, "modeName", qmltextCollapseDistance)
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted: {
        recipeModeModel.resetModel()
        updateLanguage()
    }

    QtObject {
        id: textEnum
        readonly property int textTimeIdx:              0
        readonly property int textEnergyIdx:            1
        readonly property int textPeakPowerIdx:         2
        readonly property int textGroudDetectIdx:       3
        readonly property int textAbsoluteDistanceIdx:  4
        readonly property int textCollapseDistanceIdx:  5
    }

    ListModel {
        id: recipeModeModel
        function resetModel()
        {
            recipeModeModel.append({"modeName": qmltextTime,
                                   "modeIndex": RecipeEnum.TIME_IDX,
                                   "checked": true})
            recipeModeModel.append({"modeName": qmltextEnergy,
                                   "modeIndex": RecipeEnum.ENERGY_IDX,
                                   "checked": false})
            recipeModeModel.append({"modeName": qmltextPeakPower,
                                   "modeIndex": RecipeEnum.PEAKPOWER_IDX,
                                   "checked": false})
            recipeModeModel.append({"modeName": qmltextGroundDetect,
                                   "modeIndex": RecipeEnum.GROUND_IDX,
                                   "checked": false})
        }
    }

    BransonGridView {
        id: reciepModelGridView
        anchors.fill: parent
        gridViewModel: recipeModeModel
        gridViewDelegate: recipeModeDelegate
        gridViewCellHeight: Math.round(parent.height / 3.5)
        gridViewCellWidth: Math.round(parent.width / 2) - 1
        ExclusiveGroup {
            id: checkGroup
        }
    }

    Component {
        id: recipeModeDelegate
        BransonLeftBorderRectangle
        {
            id: btnRecipeMode
            width: Math.round(reciepModelGridView.gridViewCellWidth - Math.round(11 * Style.scaleHint))
            height: Math.round(reciepModelGridView.gridViewCellHeight - Math.round(8 * Style.scaleHint))
            Text {
                anchors.left: parent.left
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: Math.round(7 * Style.scaleHint)
                text: model.modeName
                color: Style.blackFontColor
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
            }

            RadioButton {
                id: radioBtnRecipeMode
                visible: false
                exclusiveGroup: checkGroup
                checked: model.checked
                onCheckedChanged: {
                    if(radioBtnRecipeMode.checked)
                        btnRecipeMode.checked = true
                    else
                        btnRecipeMode.checked = false
                }
            }
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onReleased: {
                    radioBtnRecipeMode.checked = true
                    signalCurrentWeldModeIdxChanged(model.modeIndex)
                }
            }
        }
    }
}
