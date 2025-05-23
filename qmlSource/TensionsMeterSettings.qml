﻿import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    id: newTensionMeter
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_TENSIONS_SETTING
    readonly property int textWidth: 50
    readonly property int comboBoxWidth: 150
    readonly property int rowSpacing: 100
    readonly property int columnSpacing: 30
    readonly property int optionHeight: 30
    readonly property var tensionsTypeModel: [qsTr("数字无线"), qsTr("数字有线"), qsTr("模拟有线")]
    readonly property var sensorRangeModel: ["10T", "15T", "20T", "30T"]
    readonly property var analogRangeModel: [qsTr("无"), "0-30mV", "0-1.5V", "0-5V"]
    signal signalSaveTensometer()
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
        id: tensionsSettings
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
                id: titleTensionsNumber
                width: Math.round(textWidth * Style.scaleHint)
                height: parent.height
                text: qsTr("张力计编号") + ":"
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor
            }
            HBTextField
            {
                id: txtTensionsNumber
                // text: qsTr("2412001")
                text:Tensiometer.TensionsNumber
                width: Math.round(100 * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                onlyForNumpad: true
                onSignalClickedEvent: {
                    console.log("txtTensionsNumber.text =", txtTensionsNumber.text);
                     console.log("txtTensionsNumber =", txtTensionsNumber);
                    mainWindow.showPrimaryNumpad("请输入张力计编号", "s", 3, 0, 5, txtTensionsNumber.text,txtTensionsNumber,function(val) {
                        Tensiometer.TensionsNumber = val;
                        ModbusClient.writeRegister(39,[parseInt(val)])
                    })
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
                id: titleTensionsType
                width: Math.round(textWidth * Style.scaleHint)
                height: parent.height
                text: qsTr("张力计类型") + ":"
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor
            }
            HBComboBox
            {
                id: comboTensionsType
                model: tensionsTypeModel
                currentIndex: Tensiometer.TensiometerType
                width: Math.round(comboBoxWidth * Style.scaleHint)
                height: parent.height
                fontFamily: "宋体"
                onCurrentIndexChanged: {
                    ModbusClient.writeRegister(37, [currentIndex])
                    Tensiometer.TensiometerType = currentIndex
                    console.log("init Tensiometer:" + currentIndex)
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
                id: titleSensorRange
                width: Math.round(textWidth * Style.scaleHint)
                height: parent.height
                text: qsTr("张力计量程") + ":"
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor
            }
            HBComboBox
            {
                id: comboSensorRange
                model: sensorRangeModel
                currentIndex:Tensiometer.TensiometerRange
                width: Math.round(comboBoxWidth * Style.scaleHint)
                height: parent.height
                onCurrentIndexChanged: {
                    // ModbusClient.writeRegister(37, [currentIndex])
                    // ModbusUtils.writeScaledValue()
                    Tensiometer.TensiometerRange = currentIndex
                    console.log("init TensiometerRange:" + currentIndex)
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
                id: titleAnalogRange
                width: Math.round(textWidth * Style.scaleHint)
                height: parent.height
                text: qsTr("张力计输出信号") + ":"
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor
            }
            HBComboBox
            {
                id: comboAnalogRange
                model: analogRangeModel
                currentIndex: Tensiometer.TensiometerSignal
                width: Math.round(comboBoxWidth * Style.scaleHint)
                height: parent

                onCurrentIndexChanged: {
                    // ModbusClient.writeRegister(37, [currentIndex])
                    // ModbusUtils.writeScaledValue()
                    Tensiometer.TensiometerRange = currentIndex
                    console.log("init TensiometerSignal:" + currentIndex)
                }
            }
        }
    }


    Item{
        anchors.top: tensionsSettings.bottom
        anchors.bottom: parent.bottom
        anchors.left: tensionsSettings.left
        anchors.right: tensionsSettings.right

        HBPrimaryButton
        {
            id: newSensor
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            width: Math.round(100 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            text: qsTr("保存")
            fontSize: Math.round(Style.style5 * Style.scaleHint)
            onClicked:
            {
                signalSaveTensometer()
            }
        }
    }

}


