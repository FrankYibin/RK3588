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
    property string qmltextAfterburstTime:      qsTr("AFTERBURST TIME")
    property string qmltextDistance:            qsTr("DISTANCE")
    property string qmltextAuto:                qsTr("AUTO")
    property string qmltextExtraCooling:        qsTr("EXTRA COOLING")
    property string qmltextHoldRampForceTime:   qsTr("HOLD RAMP FORCE TIME")
    property string qmltextMaxTimeout:          qsTr("MAX TIMEOUT")
    property string qmltextPostWeldSeek:        qsTr("POST-WELD SEEK")
    property string qmltextPreweldSeek:         qsTr("PRE-WELD SEEK")
    property string qmltextPretrigger:          qsTr("PRETRIGGER")
    property string qmltextPretriggerAmplitude: qsTr("PRETRIGGER AMPLITUDE")
    property string qmltextPretriggerDistance:  qsTr("PRETRIGGER DISTANCE")
    property var qmlTextArray: [qmltextAfterburstTime, qmltextDistance, qmltextAuto,
        qmltextExtraCooling, qmltextHoldRampForceTime, qmltextMaxTimeout, qmltextPostWeldSeek,
        qmltextPreweldSeek, qmltextPretrigger, qmltextPretriggerAmplitude, qmltextPretriggerDistance]
    function updateLanguage()
    {
        qmlTextArray = languageConfig.getLanguageStringList(UIScreenEnum.RECIPES_LAB_PARAMETERA2Z, qmlTextArray)
        qmltextAfterburstTime = qmlTextArray[textEnum.textAfterburstTimeIdx]
        qmltextDistance = qmlTextArray[textEnum.textDistanceIdx]
        qmltextAuto = qmlTextArray[textEnum.textAutoIdx]
        qmltextExtraCooling = qmlTextArray[textEnum.textExtraCoolingIdx]
        qmltextHoldRampForceTime = qmlTextArray[textEnum.textHoldRampForceTimeIdx]
        qmltextMaxTimeout = qmlTextArray[textEnum.textMaxTimeoutIdx]
        qmltextPostWeldSeek = qmlTextArray[textEnum.textPostWeldSeekIdx]
        qmltextPreweldSeek = qmlTextArray[textEnum.textPreweldSeekIdx]
        qmltextPretrigger = qmlTextArray[textEnum.textPretriggerIdx]
        qmltextPretriggerAmplitude = qmlTextArray[textEnum.textPretriggerAmplitudeIdx]
        qmltextPretriggerDistance = qmlTextArray[textEnum.textPretriggerDistanceIdx]
        recipeParametersModel.setProperty(textEnum.textAfterburstTimeIdx, "Title", qmltextAfterburstTime)
        recipeParametersModel.setProperty(textEnum.textExtraCoolingIdx - 1, "Title", qmltextExtraCooling)
        recipeParametersModel.setProperty(textEnum.textHoldRampForceTimeIdx - 1, "Title", qmltextHoldRampForceTime)
        recipeParametersModel.setProperty(textEnum.textMaxTimeoutIdx - 1, "Title", qmltextMaxTimeout)
        recipeParametersModel.setProperty(textEnum.textPostWeldSeekIdx - 1, "Title", qmltextPostWeldSeek)
        recipeParametersModel.setProperty(textEnum.textPreweldSeekIdx - 1, "Title", qmltextPreweldSeek)
        recipeParametersModel.setProperty(textEnum.textPretriggerIdx - 1, "Title", qmltextPretrigger)
        recipeParametersModel.setProperty(textEnum.textPretriggerAmplitudeIdx - 1, "Title", qmltextPretriggerAmplitude)
        recipeParametersModel.setProperty(textEnum.textPretriggerDistanceIdx - 1, "Title", qmltextPretriggerDistance)
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted: {
        recipeParametersModel.resetModel()
        updateLanguage()
    }

    QtObject {
        id: textEnum
        readonly property int textAfterburstTimeIdx:        0
        readonly property int textDistanceIdx:              1
        readonly property int textAutoIdx:                  2
        readonly property int textExtraCoolingIdx:          3
        readonly property int textHoldRampForceTimeIdx:     4
        readonly property int textMaxTimeoutIdx:            5
        readonly property int textPostWeldSeekIdx:          6
        readonly property int textPreweldSeekIdx:           7
        readonly property int textPretriggerIdx:            8
        readonly property int textPretriggerAmplitudeIdx:   9
        readonly property int textPretriggerDistanceIdx:    10
    }

    ListModel {
        id: recipeParametersModel
        function resetModel()
        {
            recipeParametersModel.append({"Title":          qmltextAfterburstTime,
                                          "Enabled":        false,
                                          "IsSwitchBtn":    true,
                                          "IsValueSetting": true,
                                          "Value":          "0.500",
                                          "Unit":           "S",
                                          "Minimum":        0.000,
                                          "Maximum":        5.000,
                                          "Decimals":       3,
                                          "Index":          0})
            recipeParametersModel.append({"Title":          "",
                                          "Enabled":        false,
                                          "IsSwitchBtn":    false,
                                          "IsValueSetting": false,
                                          "Value":          "",
                                          "Unit":           "",
                                          "Minimum":        -1,
                                          "Maximum":        -1,
                                          "Decimals":       -1,
                                          "Index":          1})
            recipeParametersModel.append({"Title":          qmltextExtraCooling,
                                          "Enabled":        false,
                                          "IsSwitchBtn":    true,
                                          "IsValueSetting": false,
                                          "Value":          "",
                                          "Unit":           "",
                                          "Minimum":        -1,
                                          "Maximum":        -1,
                                          "Decimals":       -1,
                                          "Index":          2})
            recipeParametersModel.append({"Title":          qmltextHoldRampForceTime,
                                          "Enabled":        false,
                                          "IsSwitchBtn":    true,
                                          "IsValueSetting": true,
                                          "Value":          "0.500",
                                          "Unit":           "S",
                                          "Minimum":        0.000,
                                          "Maximum":        5.000,
                                          "Decimals":       3,
                                          "Index":          3})
            recipeParametersModel.append({"Title":          qmltextMaxTimeout,
                                          "Enabled":        false,
                                          "IsSwitchBtn":    true,
                                          "IsValueSetting": true,
                                          "Value":          "0.500",
                                          "Unit":           "S",
                                          "Minimum":        0.000,
                                          "Maximum":        6.000,
                                          "Decimals":       3,
                                          "Index":          4})
            recipeParametersModel.append({"Title":          qmltextPostWeldSeek,
                                          "Enabled":        false,
                                          "IsSwitchBtn":    true,
                                          "IsValueSetting": false,
                                          "Value":          "",
                                          "Unit":           "",
                                          "Minimum":        -1,
                                          "Maximum":        -1,
                                          "Decimals":       -1,
                                          "Index":          5})
            recipeParametersModel.append({"Title":          qmltextPreweldSeek,
                                          "Enabled":        false,
                                          "IsSwitchBtn":    true,
                                          "IsValueSetting": false,
                                          "Value":          "",
                                          "Unit":           "",
                                          "Minimum":        -1,
                                          "Maximum":        -1,
                                          "Decimals":       -1,
                                          "Index":          6})
            recipeParametersModel.append({"Title":          qmltextPretrigger,
                                          "Enabled":        false,
                                          "IsSwitchBtn":    true,
                                          "IsValueSetting": false,
                                          "Value":          "",
                                          "Unit":           "",
                                          "Minimum":        -1,
                                          "Maximum":        -1,
                                          "Decimals":       -1,
                                          "Index":          7})
            recipeParametersModel.append({"Title":          qmltextPretriggerAmplitude,
                                          "Enabled":        false,
                                          "IsSwitchBtn":    true,
                                          "IsValueSetting": true,
                                          "Value":          "100",
                                          "Unit":           "%",
                                          "Minimum":        0,
                                          "Maximum":        100,
                                          "Decimals":       0,
                                          "Index":          8})
            recipeParametersModel.append({"Title":          qmltextPretriggerDistance,
                                          "Enabled":        false,
                                          "IsSwitchBtn":    true,
                                          "IsValueSetting": true,
                                          "Value":          "3.00",
                                          "Unit":           "mm",
                                          "Minimum":        3.00,
                                          "Maximum":        125.00,
                                          "Decimals":       2,
                                          "Index":          9})

        }
    }

    BransonGridView {
        id: parametersGridView
        anchors.fill: parent
        gridViewModel: recipeParametersModel
        gridViewDelegate: parametersDelegate
        gridViewCellHeight: Math.round(parent.height / 3.5)
        gridViewCellWidth: Math.round(parent.width / 2) - 1
    }

    Component {
        id: parametersDelegate
        BransonLeftBorderRectangle
        {
            id: parametersOption
            width: Math.round(parametersGridView.gridViewCellWidth - Math.round(11 * Style.scaleHint))
            height: Math.round(parametersGridView.gridViewCellHeight - Math.round(8 * Style.scaleHint))
            checked: true
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onReleased: {
                    if(switchButton.checked === true && model.IsValueSetting === true)
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
                id: switchButton
                anchors.left: parent.left
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(13 * Style.scaleHint)
                visible: model.IsSwitchBtn
                enabled: parametersOption.checked
            }

            ExclusiveGroup {id: pretriggerOptionGroup}
            Row {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: Math.round(30 * Style.scaleHint)
                spacing: Math.round(8 * Style.scaleHint)
                BransonRadioButton {
                    buttonGroup: pretriggerOptionGroup
                    labelText: qmltextDistance
                    checked: true
                    enabled: parametersOption.checked
                }
                BransonRadioButton {
                    buttonGroup: pretriggerOptionGroup
                    labelText: qmltextAuto
                    checked: false
                    enabled: parametersOption.checked
                }
                visible: !model.IsSwitchBtn
            }

            Text {
                id: txtValue
                anchors.right: parent.right
                anchors.rightMargin: Math.round(14 * Style.scaleHint)
                anchors.verticalCenter: switchButton.verticalCenter
                text: model.Value + model.Unit
                color: Style.blackFontColor
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                visible: switchButton.checked && model.IsValueSetting
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}
