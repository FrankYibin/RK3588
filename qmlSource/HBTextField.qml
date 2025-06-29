/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Style 1.0

TextField {
    id: hbTextField
    property alias text: hbTextField.text
    property bool onlyForNumpad: true
    property bool isSelectedAll: false
    property int fontSize: Math.round(Style.style5 * Style.scaleHint)
    property string backgroundColor: Style.hbFrameBackgroundColor
    signal signalClickedEvent()
    implicitWidth: parent.width
    implicitHeight: parent.height
    focus: true
    maximumLength: 8
    horizontalAlignment: Text.AlignLeft
    verticalAlignment: Text.AlignVCenter
    placeholderText: ""
    validator: RegExpValidator
    {
        regExp:  /^((?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){0,3}(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/
    }
    Component.onCompleted:
    {
        Qt.inputMethod.hide()
    }

    /*TextField style*/
    style: TextFieldStyle {
        id: textStyleId
        font.pixelSize: fontSize
        font.family: Style.regular.name
        textColor: Style.whiteFontColor
        background: Rectangle {
            id:backGroundId
            radius: 2
            color: (enabled === true) ? backgroundColor : backgroundColor
            border.color: Style.hbFrameBorderColor
            border.width: 2
        }
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked:
        {
            if(parent.onlyForNumpad === true)
            {
                parent.selectAll()
                isSelectedAll = true
            }
            signalClickedEvent()
            parent.focus = false
            Qt.inputMethod.hide()
        }
        onDoubleClicked:
        {
            if(parent.onlyForNumpad === true)
            {
                parent.deselect()
                input.focus = true
                Qt.inputMethod.hide()
                isSelectedAll = false
            }
            signalClickedEvent()
        }
    }
}
