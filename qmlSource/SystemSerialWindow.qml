﻿import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_HISTORY_DATA
    readonly property int textWidth: 50
    readonly property int comboBoxWidth: 150
    readonly property int rowSpacing: 100
    readonly property int columnSpacing: 30
    readonly property int optionHeight: 30

    readonly property var comboBoxBaudratemodel: ["2400", "9600", "19200","38400","57600","115200"] //9600
    readonly property var comboBoxDataBitsmodel: ["6", "7", "8"] //8
    readonly property var comboBoxStandardmodel: ["None", "Odd", "Even"] //Even
    readonly property var comboBoxStopBitsmodel: ["1", "1.5", "2"] //1

    Rectangle
    {
        id: background
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: parent.height
        gradient: Gradient {
            GradientStop { position: 0.0; color: Style.backgroundLightColor }
            GradientStop { position: 1.0; color: Style.backgroundDeepColor }
        }
    }

    Column
    {
        anchors.centerIn: parent
        width: Math.round((textWidth + comboBoxWidth + rowSpacing) * Style.scaleHint)
        height: Math.round((optionHeight * 4 + columnSpacing * 3) * Style.scaleHint)
        spacing: Math.round(columnSpacing * Style.scaleHint)
        Row
        {
            width: parent.width
            height: Math.round(optionHeight * Style.scaleHint)
            spacing: Math.round(rowSpacing * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
            Text {
                id: titleBaudrate
                width: Math.round(textWidth * Style.scaleHint)
                height: parent.height
                text: qsTr("波特率") + ":"
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor
            }

            HBComboBox
            {
                id: comboBoxBaudrate
                model: comboBoxBaudratemodel
                currentIndex: comboBoxBaudratemodel.indexOf(Configuration.BaudRate)
                width: Math.round(comboBoxWidth * Style.scaleHint)
                height: parent.height
                fontFamily: "宋体"
                onCurrentIndexChanged: {
                    Configuration.setBaudRate(comboBoxBaudratemodel[currentIndex])
                }
            }
        }

        Row
        {
            width: parent.width
            height: Math.round(optionHeight * Style.scaleHint)
            spacing: Math.round(rowSpacing * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
            Text {
                id: titleDataBits
                width: Math.round(textWidth * Style.scaleHint)
                height: parent.height
                text: qsTr("数据位") + ":"
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor
            }

            HBComboBox
            {
                id: comboBoxDataBits
                model: comboBoxDataBitsmodel
                currentIndex: comboBoxDataBitsmodel.indexOf(Configuration.DataBits)
                width: Math.round(comboBoxWidth * Style.scaleHint)
                height: parent.height
                fontFamily: "宋体"
                onCurrentIndexChanged: {
                    Configuration.setDataBits(comboBoxDataBitsmodel[currentIndex])
                }
            }
        }

        Row
        {
            width: parent.width
            height: Math.round(optionHeight * Style.scaleHint)
            spacing: Math.round(rowSpacing * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
            Text {
                id: titleStandard
                width: Math.round(textWidth * Style.scaleHint)
                height: parent.height
                text: qsTr("奇偶校验位") + ":"
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor
            }

            HBComboBox
            {
                id: comboBoxStandard
                model: comboBoxStandardmodel
                currentIndex: comboBoxStandardmodel.indexOf(Configuration.Parity)
                width: Math.round(comboBoxWidth * Style.scaleHint)
                height: parent.height
                fontFamily: "宋体"
                onCurrentIndexChanged: {
                    Configuration.setParity(comboBoxStandardmodel[currentIndex])
                }
            }
        }
        Row
        {
            width: parent.width
            height: Math.round(optionHeight * Style.scaleHint)
            spacing: Math.round(rowSpacing * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
            Text {
                id: titleStopBits
                width: Math.round(textWidth * Style.scaleHint)
                height: parent.height
                text: qsTr("停止位") + ":"
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor
            }

            HBComboBox
            {
                id: comboBoxStopBits
                model: comboBoxStopBitsmodel
                currentIndex: comboBoxStopBitsmodel.indexOf(Configuration.StopBits)
                width: Math.round(comboBoxWidth * Style.scaleHint)
                height: parent.height
                fontFamily: "宋体"
                onCurrentIndexChanged: {
                    Configuration.setStopBits(comboBoxStopBitsmodel[currentIndex])
                }
            }
        }
    }

}


