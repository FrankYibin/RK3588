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
    property color radioEnableColor: "#004b8d"

    readonly property int circleSize: Math.round(20 * Style.scaleHint)

    text: labelText

    style: RadioButtonStyle {
        spacing: 5
        indicator: Rectangle {
            implicitWidth: circleSize
            implicitHeight: circleSize
            radius: 45
            border.color: (checked === true && enabled === true) ? radioEnableColor : Style.frameBorderColor
            border.width: Math.round(2 * Style.scaleHint)
            Rectangle {
                anchors.fill: parent
                visible: checked
                color: enabled === true ? radioEnableColor : Style.frameBorderColor
                radius: 45
                anchors.margins: Math.round(4 * Style.scaleHint)
            }
        }
        label: Text {
            color: (checked === true && enabled === true) ? onColor : offColor
            text: radioButton.text
            wrapMode: Text.WordWrap
            font.family: Style.regular.name
            font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
        }
    }
    onClicked: {
        radioButtonClick()
    }
}
