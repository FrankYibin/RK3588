/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick.Controls 2.15
import QtQuick 2.15
import Style 1.0

Rectangle {
    id: hbGroupBox
    // Title styling using an Item inside the GroupBox
    property color fontcolor: Style.whiteFontColor // Replace with the actual color variable
    property color borderColor: Style.hbFrameBorderColor // Replace with the actual color variable
    property color backgroundColor: Style.backgroundLightColor
    property int fontSize: Math.round(Style.style3)
    property string title: "default"
    implicitWidth: parent.width
    implicitHeight: parent.height
    // Use a Rectangle or Item to style the border and content
    // Title styling using an Item inside the GroupBox

    Label {
        text: qsTr(hbGroupBox.title)
        font.family: "宋体"
        font.pointSize: fontSize
        color: fontcolor
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: -10
        background: Rectangle
        {
            color: backgroundColor
        }
    }

    border.color: borderColor
    border.width: 1
    color: "transparent"
}
