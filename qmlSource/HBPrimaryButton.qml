/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.6
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.1
import Style 1.0

Button {
    readonly property string qmltextPrimary: qsTr("PRIMARY")
    id: primaryButton
    text: qmltextPrimary

    property int minWidth: 140
    property int maxHeight: 40
    property int radiusWidth: 4
    property color buttonColor: Style.hbButtonBackgroundColor
    property color textColor : Style.whiteFontColor
    property color shadowColor: "#80000000"
    property int fontSize: Math.round(Style.style6 * Style.scaleHint)
    contentItem: Text {
        text: qsTr(primaryButton.text)
        font{
            family: "宋体"
            pixelSize: fontSize
            // capitalization: Font.AllUppercase
            bold: true
        }
        color: textColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }
    background: Rectangle {
        id: buttonRect
        implicitWidth: parent.width < minWidth ? minWidth : parent.width
        implicitHeight: parent.height > maxHeight ? maxHeight : parent.height
        color: (checked === true) ? Style.frameBorderColor : buttonColor
        radius: radiusWidth
        layer.enabled: primaryButton.pressed ? false : true
        layer.effect: DropShadow {
            horizontalOffset: primaryButton.pressed ? 0 : 3
            verticalOffset: primaryButton.pressed ? 0 : 3
            color:  shadowColor
            opacity: 0.2
            samples: 10
        }
    }
}

