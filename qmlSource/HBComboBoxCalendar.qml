/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import Style 1.0

Rectangle {
    id: comboboxId
    property int imageSize: Math.round(Style.scaleHint * 30)
    property bool  menuStatus: false
    property bool  isNormal: true
    property int   radiusWidth: Math.round(5 * Style.scaleHint)
    property color comboBoxTextColor: Style.whiteFontColor
    property color comboBoxBorderColor: Style.activeFrameBorderColor
    property color comboBoxColor : Style.hbFrameBackgroundColor
    property color shadowColor: "#80000000"
    property alias dropDownImg:img
    property string comboBoxText
    property int fontSize: Math.round(Style.style5 * Style.scaleHint)
    property string fontFamily: Style.regular.name
    property alias text: currentText.text
    property bool isPopUp: false
    signal signalPopUp(var isShow)

    // anchors.fill: parent
    color: comboBoxColor
    border.color: comboBoxBorderColor
    border.width: 1
    height: Math.round(25 * Style.scaleHint)
    radius: Math.round(3 * Style.scaleHint)

    /**
       *@breif: On click change image
       **/
    function changeImageUp() {
        img.source = "qrc:/images/drop-up-arrow.svg"
        isPopUp = true
    }

    /**
       *@breif: On click change image
       **/
    function changeImageDown() {
        img.source = "qrc:/images/drop-down-arrow_blue.svg"
        isPopUp = false
    }

    Text{
        id: currentText
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        font.family: fontFamily
        font.pixelSize: fontSize
        color: Style.whiteFontColor
    }

    Image {
        id: img
        anchors.right: comboboxId.right
        anchors.top:comboboxId.top
        anchors.verticalCenter: comboboxId.verticalCenter
        width: imageSize
        height: imageSize
        sourceSize.width: comboboxId.width
        sourceSize.height:  comboboxId.height
        fillMode: Image.PreserveAspectFit
        source: comboboxId.changeImageDown()
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {
            if(isPopUp === false)
            {
                changeImageUp()
            }
            else
            {
                changeImageDown()
            }
            signalPopUp(isPopUp)
        }
    }
}
