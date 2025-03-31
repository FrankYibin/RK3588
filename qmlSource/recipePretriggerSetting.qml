/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 Recipe Pretrigger Setting
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtQml.Models 2.15
import QtQuick.Controls 1.4
import Style 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
Item {
    property string qmltextMenuName:            qsTr("PRETRIGGER")
    property string qmltextDistance:            qsTr("DISTANCE")
    property string qmltextAuto:                qsTr("AUTO")
    property string qmltextPretriggerAmplitude: qsTr("PRETRIGGER AMPLITUDE")
    property string qmltextTurnAllOff:          qsTr("Turn all off")
    property var qmlTextArray: [qmltextDistance, qmltextAuto, qmltextPretriggerAmplitude,
        qmltextTurnAllOff]

    function updateLanguage()
    {
        qmlTextArray = languageConfig.getLanguageStringList(UIScreenEnum.RECIPES_LAB_WELDPROCESS_PRETRIGGER, qmlTextArray)
        qmltextDistance = qmlTextArray[textEnum.textDistanceIdx]
        qmltextAuto = qmlTextArray[textEnum.textAutoIdx]
        qmltextPretriggerAmplitude = qmlTextArray[textEnum.textPretriggerAmplitudeIdx]
        qmltextTurnAllOff = qmlTextArray[textEnum.textTurnAllOffIdx]
        qmltextMenuName = languageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_WELDPROCESS_PRETRIGGER, qmltextMenuName)
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
        readonly property int textDistanceIdx:              0
        readonly property int textAutoIdx:                  1
        readonly property int textPretriggerAmplitudeIdx:   2
        readonly property int textTurnAllOffIdx:            3
    }

    BransonLeftBorderRectangle {
        id: switchPretrigger
        width: Math.round(parent.width - pretriggerDetails.spacing)
        height: Math.round(parent.height / 3.5 - Math.round(8 * Style.scaleHint))
        property bool isTurnAllOn: false
        checked: isTurnAllOn
        Text {
            id: txtPretriggerTitle
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
            anchors.verticalCenter: txtPretriggerTitle.verticalCenter
            text: qmltextTurnAllOff
            color: Style.blackFontColor
            font.family: Style.italic.name
            font.italic: true
            font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
        }
        BransonSwitch {
            id: pretriggerSwitch
            anchors.horizontalCenter: txtTurnAllOffTitle.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(13 * Style.scaleHint)
            onCheckedChanged: {
                if(pretriggerSwitch.checked === true)
                    switchPretrigger.isTurnAllOn = true
                else
                    switchPretrigger.isTurnAllOn = false
            }
        }
    }

    Row {
        id: pretriggerDetails
        anchors.top: switchPretrigger.bottom
        anchors.topMargin: Math.round(8 * Style.scaleHint)
        width: parent.width
        height: parent.height
        spacing: Math.round(11 * Style.scaleHint)
        BransonLeftBorderRectangle {
            id: switchDistanceAuto
            width: Math.round(parent.width / 2 - pretriggerDetails.spacing)
            height: switchPretrigger.height
            checked: switchPretrigger.isTurnAllOn
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
                    enabled: switchDistanceAuto.checked
                }
                BransonRadioButton {
                    buttonGroup: pretriggerOptionGroup
                    labelText: qmltextAuto
                    checked: false
                    enabled: switchDistanceAuto.checked
                }
            }

        }
        BransonLeftBorderRectangle {
            id: pretriggerAmplitudeSetting
            width: Math.round(parent.width / 2 - pretriggerDetails.spacing)
            height: switchPretrigger.height
            checked: switchPretrigger.isTurnAllOn
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onReleased: {
                    if(switchPretriggerAmplitude.checked === true)
                        mainWindow.showPrimaryNumpad(qmltextPretriggerAmplitude, "%", 0, 0, 100, txtPertriggerAmplitudeValue.text)
                }
            }

            Text {
                id: txtPertriggerAmplitudeTitle
                anchors.left: parent.left
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: Math.round(7 * Style.scaleHint)
                text: qmltextPretriggerAmplitude
                color: Style.blackFontColor
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
            }

            BransonSwitch {
                id: switchPretriggerAmplitude
                anchors.left: parent.left
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(13 * Style.scaleHint)
                enabled: pretriggerAmplitudeSetting.checked
                onCheckedChanged: {
                    if(switchPretriggerAmplitude.checked === true)
                    {

                    }
                }
            }

            Text {
                id: txtPertriggerAmplitudeValue
                anchors.right: parent.right
                anchors.rightMargin: Math.round(14 * Style.scaleHint)
                anchors.verticalCenter: switchPretriggerAmplitude.verticalCenter
                text: "100%"
                color: Style.blackFontColor
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                visible: switchPretriggerAmplitude.checked
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}
