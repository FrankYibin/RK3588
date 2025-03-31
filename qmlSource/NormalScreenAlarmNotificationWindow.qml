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
import AlarmDefine 1.0
Item {
    id: alarmNotificationNormalScreen
    property var scaleRate:  1
    property string qmltextAlarm:       AlarmDefine.qmltextAlarm
    property string qmltextReset:       AlarmDefine.qmltextReset
    property string qmltextHide:        AlarmDefine.qmltextHide
    property string qmltextAlarmTitle:  ""
    property string qmltextAlarmId:     ""
    property int    alarmIndex:            alarmNotification.AlarmIndex

    onAlarmIndexChanged:
    {
        if(alarmIndex === 0)
        {
            alarmNotificationNormalScreen.visible = false
            return
        }
        if(AlarmDefine.isCriticalAlarm(alarmIndex) === true)
            return
        qmltextAlarmTitle = AlarmDefine.getAlarmName(alarmIndex)
        qmltextAlarmId = alarmIndex.toString(16)
        alarmNotificationNormalScreen.visible = true
    }

    Rectangle {
        id: alarmNotificationHeader
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: Math.round(100 * Style.scaleHint * scaleRate)
        color: "#f79428"//Style.navigationMenuBackgroundColor
        Rectangle {
            id: alarmTitleRec
            anchors.left: parent.left
            anchors.top: parent.top
            width: parent.height
            height: parent.height
            color: "#f79428"//Style.navigationMenuBackgroundColor
            Image {
                id: image
                width: Math.round(80 * Style.scaleHint * scaleRate)
                height: Math.round(80 * Style.scaleHint * scaleRate)
                sourceSize.width: image.width
                sourceSize.height: image.height
                source: "qrc:/images/part_icon_white.png"
                smooth: true
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
            }
        }
        Text {
            id: txtTitle
            text: qmltextAlarm
            anchors.left: alarmTitleRec.right
            anchors.leftMargin: Math.round(9 * Style.scaleHint * scaleRate)
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: Math.round(Style.style8 * Style.scaleHint * scaleRate)
            font.family: Style.regular.name
            font.bold: true
            color: Style.whiteFontColor
        }
    }

    Rectangle {
        id: alarmNotificationMessage
        anchors.top: alarmNotificationHeader.bottom
        anchors.bottom: buttonsFrame.top
        anchors.left: parent.left
        width: parent.width
        color: Style.navigationMenuBackgroundColor
        Text {
            id: txtAlarmTitle
            anchors.centerIn: parent
//            width: parent.width
            font.pixelSize: Math.round(Style.style8 * Style.scaleHint * scaleRate)
            font.family: Style.regular.name
            color: Style.whiteFontColor
            wrapMode: Text.WordWrap
            text: qmltextAlarmId + ": " + qmltextAlarmTitle
        }
    }

    Rectangle {
        id: buttonsFrame
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width
        height: Math.round(125 * Style.scaleHint * scaleRate)
        color: Style.navigationMenuBackgroundColor

        Row {
            id: btnArray
            spacing: Math.round(50 * Style.scaleHint * scaleRate)
            width: Math.round(700 * Style.scaleHint * scaleRate) + spacing
            height: Math.round(85 * Style.scaleHint * scaleRate)
            anchors.centerIn: parent
            BransonPrimaryButton{
                id: resetButton
                width: Math.round((parent.width - btnArray.spacing) / 2)
                height: parent.height
                text: qmltextReset
                fontSize: Math.round(Style.style8 * Style.scaleHint * scaleRate)
                onClicked: {
                    alarmNotification.resetSpecificAlarm(alarmIndex)
                    alarmNotificationNormalScreen.visible = false
                }
            }

            BransonPrimaryButton{
                id: hideButton
                width: Math.round((parent.width - btnArray.spacing) / 2)
                height: parent.height
                text: qmltextHide
                fontSize: Math.round(Style.style8 * Style.scaleHint * scaleRate)
                onClicked: {
                    alarmNotificationNormalScreen.visible = false
                }
            }
        }
    }

}
