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

ComboBox {
    id: comboboxId
    property alias comboboxpopupheight:comboboxpopup.implicitHeight
    property int   minWidth: Math.round(120 * Style.scaleHint)
    property int   minHeight: Math.round(40 * Style.scaleHint)
    property int imageSize: Math.round(Style.scaleHint * 30)
    property bool  menuStatus: false
    property bool  isNormal: true
    property int   radiusWidth: Math.round(5 * Style.scaleHint)
    property color comboBoxTextColor: Style.whiteFontColor
    property color comboBoxBorderColor: Style.activeFrameBorderColor
    property color comboBoxColor : Style.hbFrameBackgroundColor
    property color shadowColor: "#80000000"
    property alias dropDownImg:img
    property alias dropDownText:combo_text
    property string comboBoxText
    property int fontSize: Math.round(Style.style5 * Style.scaleHint)
    property string fontFamily: Style.regular.name
    enabled: true
    implicitWidth: minWidth
    implicitHeight: minHeight
    background: Rectangle{
        anchors.fill: parent
        color: (enabled === true) ? comboBoxColor : BransonStyle.backgroundColor
        border.color: comboBoxBorderColor
        border.width: 1
        height: Math.round(25 * Style.scaleHint)
        radius: Math.round(3 * Style.scaleHint)
        layer.enabled: comboboxId.pressed ? false : true
                layer.effect: DropShadow {
                    horizontalOffset: comboboxId.pressed ? 0 : 1
                    verticalOffset: comboboxId.pressed ? 0 : 1
                    color:  shadowColor
                    opacity: 0.2
                    samples: 10
                }
    }
    popup: Popup {
        id:comboboxpopup
        y: comboboxId.height
        width: comboboxId.implicitWidth
        implicitHeight: contentItem.implicitHeight
        padding: 1
        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: comboboxId.popup.visible ? comboboxId.delegateModel : null
            ScrollIndicator.vertical: ScrollIndicator { }

        }

        background: Rectangle {

            border.color: comboBoxBorderColor
            id:comboBoxRectangle
            color: comboBoxColor
            radius: Math.round(2 * Style.scaleHint)
            layer.enabled: comboBoxRectangle
                       layer.effect: DropShadow {
                           horizontalOffset: 1
                           verticalOffset: 1
                           color:  shadowColor
                           opacity: 0.2
                           samples: 10
                       }
        }
        onAboutToHide:
        {
            changeImageDown()
        }

    }
   onCurrentIndexChanged:changeIndex(currentIndex)

    contentItem: Text {
        id: combo_text
        color: comboBoxTextColor
        text: isNormal === true ? currentText : comboBoxText
        anchors.left:  comboboxId.left
        anchors.leftMargin: Math.round(10 * Style.scaleHint)
        verticalAlignment: Text.AlignVCenter
        font{
            family: fontFamily
            pixelSize: fontSize
        }
    }

    delegate: ItemDelegate {
        width: minWidth
        height: minHeight
        contentItem: Rectangle
        {
            anchors.fill: parent
            color: hovered === true ? Style.titleBackgroundColor : "#ffffff"
            Text {
                anchors.fill: parent
                text: modelData
                color: hovered === true ? "#ffffff" : Style.blackFontColor
                font.family: fontFamily
                font.pixelSize: fontSize
//                elide: Text.ElideRight
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                leftPadding:  Math.round(10* Style.scaleHint)
            }
        }
    }

    onPressedChanged:
    {
        comboboxId.changeImageUp()
    }

    /**
       *@breif: On click change image
       **/
    function changeImageUp() {
        img.source = "qrc:/images/drop-up-arrow.svg"

    }

    /**
       *@breif: On click change image
       **/
    function changeImageDown() {
        img.source = "qrc:/images/drop-down-arrow_blue.svg"
    }

    /**
       *@breif: Change image
       **/
    function changeIndex(currentIndex)
    {
        comboboxId.changeImageDown()
    }
    indicator:  Image {
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
}
