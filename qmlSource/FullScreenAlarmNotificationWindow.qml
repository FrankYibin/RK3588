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
import Style 1.0
import AlarmDefine 1.0
import Com.Branson.AlarmIndexEnum 1.0
Item {
    id: alarmNotificationFullScreen
    property string qmltextAlarm:                   AlarmDefine.qmltextAlarm
    property string qmltextErrorDescriptionTitle:   AlarmDefine.qmltextErrorDescriptionTitle
    property string qmltextReset:                   AlarmDefine.qmltextReset
    property string qmltextHide:                    AlarmDefine.qmltextHide
    property string qmltextErrorDescription:    ""
    property string qmltextAlarmId:             ""
    property string qmltextAlarmTitle:          ""
    property string qmltextDate: "2021/03/17"
    property string qmltextTime: "02:54:57"
    property int imageSize: Math.round(Style.scaleHint * 30)
    property int alarmIndex: alarmNotification.AlarmIndex

    onAlarmIndexChanged:
    {
        if(alarmIndex === 0)
        {
            alarmNotificationFullScreen.visible = false
            return
        }
        if(AlarmDefine.isCriticalAlarm(alarmIndex) === false)
            return
        qmltextAlarmTitle = AlarmDefine.getAlarmName(alarmIndex)
        qmltextAlarmId = alarmIndex.toString(16)
        qmltextErrorDescription = AlarmDefine.getAlarmDescription(alarmIndex)
        alarmNotificationFullScreen.visible = true
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {
        }
    }

    Component.onCompleted: {
        dateTimeModel.resetModel()
    }

    ListModel{
        id: dateTimeModel
        function resetModel()
        {
            dateTimeModel.clear()
            dateTimeModel.append({"ImageUrl": "qrc:/images/date-time.svg", "Text": qmltextDate})
            dateTimeModel.append({"ImageUrl": "qrc:/images/Time.png", "Text": qmltextTime})

        }
    }

    Rectangle {
        id: alarmNotificationHeader
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: Math.round(100 * Style.scaleHint)
        color: Style.headerBackgroundColor
        Rectangle {
            id: alarmTitleRec
            anchors.left: parent.left
            anchors.top: parent.top
            width: txtTitle.width + Math.round(50 * Style.scaleHint)
            height: parent.height
            color: Style.headerBackgroundColor
            Text {
                id: txtTitle
                text: qmltextAlarm
                anchors.centerIn: parent
                font.pixelSize: Math.round(Style.style8 * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.whiteFontColor
            }
        }

    }

    Rectangle {
        id: alarmNotificationMessage
        anchors.top: alarmNotificationHeader.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width * 2/3
        Text {
            id: txtAlarmTitle
            anchors.top: parent.top
            anchors.topMargin: Math.round(50 * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin: Math.round(100 * Style.scaleHint)
            anchors.right: parent.right
            font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
            wrapMode: Text.WordWrap
            text: qmltextAlarmId + ": " + qmltextAlarmTitle
        }

        Text {
            id: txtAlarmDescriptionTitle
            anchors.left: txtAlarmTitle.left
            anchors.top: txtAlarmTitle.bottom
            anchors.topMargin: Math.round(20 * Style.scaleHint)
            font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
            text: qmltextErrorDescriptionTitle
        }

        Text {
            id: txtAlarmDescription
            anchors.left: txtAlarmDescriptionTitle.left
            anchors.top: txtAlarmDescriptionTitle.bottom
            anchors.topMargin: Math.round(5 * Style.scaleHint)
            anchors.right: parent.right
            font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
            wrapMode: Text.WordWrap
            text: qmltextErrorDescription
        }

        Rectangle {
            anchors.top: txtAlarmDescription.bottom
            anchors.bottom: parent.bottom
            anchors.left: txtAlarmDescription.left
            anchors.right: parent.right

            Column {
                id: alarmDateTime
                width: parent.width
                height: Math.round(80 * Style.scaleHint)
                spacing: Math.round(10 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                Repeater {
                    model: dateTimeModel
                    delegate: Item{
                        height: imageSize
                        width: parent.width
                        Image {
                            id: titleImage
                            width: parent.height
                            height: parent.height
                            sourceSize.width: titleImage.width
                            sourceSize.height: titleImage.height
                            source: model.ImageUrl
                            smooth: true
                            fillMode: Image.PreserveAspectFit
                        }
                        Text {
                            height: parent.height
                            anchors.left: titleImage.right
                            anchors.leftMargin: Math.round(10 * Style.scaleHint)
                            font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                            font.family: Style.regular.name
                            color: Style.blackFontColor
                            text: model.Text
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        id: buttonsFrame
        anchors.top: alarmNotificationHeader.bottom
        anchors.bottom: parent.bottom
        anchors.left: alarmNotificationMessage.right
        anchors.right: parent.right

        Column {
            spacing: Math.round(10 * Style.scaleHint)
            width: Math.round(125 * Style.scaleHint)
            height: Math.round(80 * Style.scaleHint)
            anchors.centerIn: parent
            BransonPrimaryButton{
                id: saveButton
                width: Math.round(130 * Style.scaleHint)
                height: Math.round(40 * Style.scaleHint)
                text: qmltextReset
                fontSize: Math.round(Style.style4 * Style.scaleHint)
                onClicked: {
                    alarmNotificationFullScreen.visible = false
                }
            }

            BransonPrimaryButton{
                id: cancelButton
                width: Math.round(130 * Style.scaleHint)
                height: Math.round(40 * Style.scaleHint)
                text: qmltextHide
                fontSize: Math.round(Style.style4 * Style.scaleHint)
                onClicked: {
                    alarmNotificationFullScreen.visible = false
                }
            }
        }
    }
}
