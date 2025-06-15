/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import Style 1.0
TextField {
    id: input
    property int minWidth: Math.round(140 * Style.scaleHint)
    property int maxHeight: Math.round(30 * Style.scaleHint)
    //    property alias readOnlyText: input.readOnly
    //    property alias echoMode: input.echoMode
    //    property alias text: input.text
    property color backgroundcolor: Style.hbFrameBackgroundColor
    property color textfieldcolor: Style.whiteFontColor
    property color bordercolor: Style.hbFrameBorderColor
    font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
    font.family: Style.regular.name
    font.bold: false
    implicitWidth: minWidth
    implicitHeight: maxHeight
    maximumLength: 32
    echoMode:TextInput.Normal
    readOnly: false
    verticalAlignment: TextInput.AlignVCenter
    validator: RegExpValidator
    {
        regExp: /^[a-zA-Z0-9`!@#$%&*()_+={}:;<>.?-]*$/
    }

    /*TextField style*/
    style: TextFieldStyle {
        id: textStyleId
        font.pixelSize:Math.round(Style.style6 * Style.scaleHint)
        textColor: textfieldcolor
        background: Rectangle {
            id:backGroundId
            radius: 2
            color: backgroundcolor
            border.color: bordercolor
            border.width: 2
        }
    }




    Keys.onReturnPressed: {
        event.accepted = true
        accepted()
    }

    onFocusChanged: if (!focus) accepted()
}
