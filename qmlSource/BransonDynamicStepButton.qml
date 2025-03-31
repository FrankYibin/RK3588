/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4
import Style 1.0
Rectangle {
    id: rec
    property int stepIndex: 1
    property alias exclusiveGroup: stepRadioBtn.exclusiveGroup
    property alias checked: stepRadioBtn.checked
    signal signalClickAction(int index)
    color: (stepRadioBtn.checked === true) ? BransonStyle.activeFrameBorderColor : "#ffffff"
    border.width: (BransonStyle.scaleHint === 1.0) ? 1 : 2
    border.color: BransonStyle.frameBorderColor
    Component.onCompleted: {
        stepRadioBtn.checked = true
    }

    Text {
        id: txtStepIndex
        anchors.left: parent.left
        anchors.leftMargin: Math.round(15 * Style.scaleHint)
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: Math.round(Style.style4  * Style.scaleHint)
        font.family: Style.regular.name
        color: (stepRadioBtn.checked === true) ? "#ffffff" : BransonStyle.blackFontColor
        text: stepIndex
    }

    RadioButton {
        id: stepRadioBtn
        checked: false
        visible: false
        onCheckedChanged: {
            if(stepRadioBtn.checked)
                stepRadioBtn.checked = true
            else
                stepRadioBtn.checked = false
        }
    }
    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onReleased: {
            stepRadioBtn.checked = true
            signalClickAction(stepIndex)
        }
    }
}
