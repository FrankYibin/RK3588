/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import Style 1.0


RadioButton {
    id: radioButton

    signal radioButtonClick()
    property alias buttonGroup: radioButton.exclusiveGroup
    property string labelText: ""
    property string offColor: Style.blackFontColor
    property string onColor: Style.blueFontColor
    property color radioEnableColor: "#00afe9"
    property color radioDisableColor: Style.backgroundDeepColor

    property int circleSize: Math.round(20 * Style.scaleHint)

    text: labelText

    style: RadioButtonStyle {
        spacing: 5
        indicator: Rectangle {
            implicitWidth: circleSize
            implicitHeight: circleSize
            radius: 5
            border.color: Style.hbRadioButtonBorderColor
            border.width: Math.round(5 * Style.scaleHint)
            color: "transparent"
            Rectangle {
                anchors.fill: parent
                visible: checked
                color: enabled === true ? radioEnableColor : "transparent"
                // radius: 5
                anchors.margins: Math.round(5 * Style.scaleHint)
            }
        }
        label: Text {
            height: circleSize
            color: Style.whiteFontColor
            text: radioButton.text
            wrapMode: Text.WordWrap
            font.family: "宋体"
            font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
            verticalAlignment: Text.AlignVCenter
        }
    }
    onClicked: {
        radioButtonClick()
    }
}
