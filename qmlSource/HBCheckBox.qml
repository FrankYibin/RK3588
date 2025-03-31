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
import QtGraphicalEffects 1.0
import Style 1.0

Item {
    readonly property string qmltextCheckBox : qsTr("CheckBox")
    property int minWidth: Math.round(16 * Style.scaleHint)
    property int maxHeight: Math.round(16 * Style.scaleHint)
    property int fontSize: Math.round(Style.style2  * Style.scaleHint)
    property color backgroundcolor: "#E9ECEF"
    property color textcolor: "#272727"
    property color checkcolor: "#272727"
    Rectangle
    {
        id:root
        implicitWidth: minWidth
        implicitHeight: maxHeight
        color: "transparent"
        /*Text on the right side of the Checkbox*/
        Text {
            id: checkBoxText
            anchors.left: checkBoxId.right
            anchors.leftMargin: Math.round(15 * Style.scaleHint)
            anchors.top: checkBoxId.top
            font.pixelSize: fontSize
            font.family: Style.regular.name
            text: qmltextCheckBox
            wrapMode: Text.Wrap
            color:textcolor
        }
        /*Check the box section*/
        CheckBox{
            id:checkBoxId
            checked: false
            style: CheckBoxStyle{
                indicator:  Rectangle {
                    id:comborect
                    implicitWidth: root.width
                    implicitHeight: root.height/*-Math.round(100 * Style.scaleHint)*/
                    radius: 3
                    color:backgroundcolor
                    layer.enabled: true
                    layer.effect: DropShadow{
                        anchors.fill: comborect
                        horizontalOffset: 0
                        verticalOffset: 1
                        color: "#60000000"
                        opacity: 0.2
                        source: comborect
                    }
                    Image {
                        id:checkMarkImage
                        width:parent.width
                        height: parent.height
                        source: "qrc:/images/true.svg"
                        sourceSize.width: checkMarkImage.width
                        sourceSize.height: checkMarkImage.height
                        smooth: true
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                        visible: checkBoxId.checked==true
                    }
                    ColorOverlay {
                        anchors.fill: checkMarkImage
                        source: checkMarkImage
                        color: checkcolor
                        visible: checkBoxId.checked==true
                    }
                }
            }
        }
    }
}
