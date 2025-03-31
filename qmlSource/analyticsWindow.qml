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
Item {
    Component.onCompleted: {

    }

    Loader
    {
        id: loader
        anchors.left: parent.left
        anchors.leftMargin: Math.round(8 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(7 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(49 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(8 * Style.scaleHint)
        source: "qrc:/qmlSource/normalGraphWindow.qml"
    }

}
