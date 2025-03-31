/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 xxxxx

 **********************************************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import Style 1.0


Item {

    id: bransonInfoElement

    width: Math.round(374 * Style.scaleHint)
    height: Math.round(35 * Style.scaleHint)

    property alias heightImg : backgroundImage.height
    property alias widthImg: backgroundImage.width

    property alias protyName:  elementName.text
    property alias protyValue: elementResult.text

    Image{
        id: backgroundImage
        source: "qrc:/images/InformationRectangle.svg"
        anchors.fill: parent
        height: parent.height
        width: parent.width
        Text{
            id: elementName
            anchors.left: parent.left
            anchors.leftMargin: Math.round(11 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
        }
        Text{
            id: dwukropek
            anchors.left: parent.left
            anchors.leftMargin: Math.round(182 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
            text: ": "
        }
        Text{
            id: elementResult
            anchors.left: dwukropek.right
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
        }

    }
}
