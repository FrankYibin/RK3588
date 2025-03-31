/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
//import QtQuick.Controls 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import Style 1.0
//import NumpadDefine 1.0
Item {
    id: primaryNumpad
    property int minWidth: Math.round(400 * Style.scaleHint)
    property int maxHeight: Math.round(411 * Style.scaleHint)
    property int headermaxHeight: Math.round(30 * Style.scaleHint)
    property string headertext: "TRIGGER FORCE"
    property string suffix:  "%"
    property int decimals: 2
    property real minimumValue: 10
    property real maximumValue: 100
    property alias value: input.text

    function slotDigitalKeyPressed(data)
    {
        BransonNumpadDefine.handleWithDigitalKeyInput(data, input, suffix)
    }

    Component.onCompleted: {
        bransonprimary.signalButtonNum.connect(slotDigitalKeyPressed)
        bransonprimary.signalButtonFunc.connect(slotDigitalKeyPressed)
    }


    Rectangle {
        id: background
        anchors.fill: parent
        color: Style.dialogBackgroundColor
        opacity: 0.75
        MouseArea {
            anchors.fill: parent
        }
    }

    Rectangle
    {
        id:root
        implicitWidth: minWidth
        implicitHeight:maxHeight
        anchors.centerIn: parent
        color: "#FFFFFF"
        /*header title*/
        Rectangle
        {
            id: numpadHeader
            width: parent.width
            implicitHeight: headermaxHeight
            color: Style.headerBackgroundColor
            Text {
                id: headername
                anchors.left: numpadHeader.left
                anchors.top: numpadHeader.top
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                text: headertext
                color: Style.whiteFontColor
                font{
                    family: Style.regular.name
                    pixelSize: Math.round(Style.style2 * Style.scaleHint)
                }
            }

            Rectangle
            {
                id:rectimage
                implicitWidth: Math.round(24 * Style.scaleHint)
                implicitHeight: Math.round(24 * Style.scaleHint)
                anchors.right: numpadHeader.right
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                anchors.top: numpadHeader.top
                anchors.topMargin:Math.round(5 * Style.scaleHint)
                color: "transparent"
                Image {
                    id: headerClose
                    anchors.fill: parent
                    source: "qrc:/images/crossMark.svg"
                    sourceSize.width: headerClose.width
                    sourceSize.height: headerClose.height
                    smooth: true

                }
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        primaryNumpad.visible = false
                    }
                }
            }
        }
        /*main keyboard*/
        Rectangle
        {
            anchors.top: numpadHeader.bottom
            anchors.left: numpadHeader.left
            anchors.topMargin: Math.round(0* Style.scaleHint)
            anchors.leftMargin: Math.round(200 * Style.scaleHint)

            BransonTextField
            {
                id: input
                anchors.top: parent.top
                anchors.topMargin: Math.round(22 * Style.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
                width: Math.round(260 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                focus: true
                onlyForNumpad: true
                onTextChanged:
                {
                    BransonNumpadDefine.decimalsNumber(decimals,input)
                }
            }
            Text {
                id: txtUnit
                text: suffix
                anchors.right: input.right
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                anchors.top: input.top
                anchors.topMargin: Math.round(4 * Style.scaleHint)
                color: Style.blackFontColor
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                font.family: Style.regular.name
            }
            Label {
                id: labelMin
                text: BransonNumpadDefine.qmltextMinimun + ":" //qsTr("Min:")
                anchors.top: input.bottom
                anchors.left: input.left
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blueFontColor
            }
            Text {
                id: txtMin
                text: BransonNumpadDefine.numberToString(decimals, minimumValue)
                anchors.top: labelMin.top
                anchors.left: labelMin.right
                anchors.leftMargin:  Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blueFontColor

            }
            Label {
                id: labelMax
                text: BransonNumpadDefine.qmltextMaximum + ":" //qsTr("Max:")
                anchors.top: txtMax.top
                anchors.right: txtMax.left
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blueFontColor
            }
            Text {
                id: txtMax
                text: BransonNumpadDefine.numberToString(decimals, maximumValue)
                anchors.top: input.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                anchors.right:  input.right
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blueFontColor

            }
            BransonNumKeyboard
            {
                id:bransonprimary
                anchors.top:input.bottom
                anchors.topMargin: Math.round(8 * Style.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        /*bottom keyboard*/
        BransonPrimaryButton
        {
            id:cancel
            implicitWidth: Math.round(124 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style2  * Style.scaleHint)
            anchors.bottom: root.bottom
            anchors.bottomMargin: Math.round(15 * Style.scaleHint)
            anchors.left: root.left
            anchors.leftMargin: Math.round(60 * Style.scaleHint)
            text: BransonNumpadDefine.qmltextCancel
            font.family: Style.regular.name
            buttonColor: Style.backgroundColor
            textColor: "#000000"
            onClicked:
            {
                primaryNumpad.visible = false
            }
        }

        BransonPrimaryButton
        {
            id:done
            implicitWidth: Math.round(124 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style2  * Style.scaleHint)
            anchors.top: cancel.top
            anchors.left: cancel.right
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            text: BransonNumpadDefine.qmltextDone
            font.family: Style.regular.name
            onClicked:
            {
                //var validatedValue = recipe.ValidateParamRange(paramIndex, input.text)
                // recipe.updateParam(paramIndex, validateValue)
                primaryNumpad.visible = false
            }
        }
    }

}
