/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtGraphicalEffects 1.0
import Style 1.0

Item {
    property color activatedBigBackgroundColor: "#E1EAEA"
    property color activatedBigBackgroundBorderColor: "#E1EAEA"
    property color activatedBackgroundColor: Style.titleBackgroundColor
    property color activatedBackgroundBorderColor: Style.titleBackgroundColor
    property color normalBigBackgroundColor: Style.backgroundColor
    property color normalBigBackgroundBorderColor: Style.backgroundColor
    property color normalBackgroundColor: Style.frameBorderColor
    property color normalBackgroundBorderColor: Style.frameBorderColor
    property bool checked: false
    Rectangle
    {
        id:root
        implicitWidth: parent.width
        implicitHeight: parent.height
        color: "transparent"
        DropShadow{
            anchors.fill: leftBorderRectAll
            horizontalOffset: 1
            verticalOffset: 1
            color: "#000000"
            opacity: 0.2
            source: leftBorderRectAll
        }
        Rectangle {
            /* The Largest rectangle */
            id: leftBorderRectAll
            implicitWidth: parent.width
            implicitHeight: parent.height
            color: (checked === true) ? activatedBigBackgroundColor : normalBigBackgroundColor
            radius: Math.round(3 * Style.scaleHint)
            border.color: (checked === true) ? activatedBigBackgroundBorderColor : normalBigBackgroundBorderColor
            border.width: Style.scaleHint === 1.0 ? 1 : 3
            Rectangle {
                /* The Border rectangle */
                id: leftBorderRectBorder
                width: Math.round(9 * Style.scaleHint)
                height: parent.height
                anchors.left: parent.left
                anchors.leftMargin: 0
                radius: Math.round(3 * Style.scaleHint)
                color: (checked === true) ? activatedBackgroundColor : normalBackgroundColor
                border.color: (checked === true) ? activatedBackgroundBorderColor : normalBackgroundBorderColor
                Rectangle{
                    id: paramRec
                    width: Math.round(7 * Style.scaleHint)
                    height: parent.height
                    color: (checked === true) ? activatedBackgroundColor : normalBackgroundColor
                    border.color: (checked === true) ? activatedBackgroundBorderColor : normalBackgroundBorderColor
                    anchors.left: leftBorderRectBorder.left
                    anchors.leftMargin: Math.round(3 * Style.scaleHint)
                    radius: 0
                }
            }
        }
    }
}
