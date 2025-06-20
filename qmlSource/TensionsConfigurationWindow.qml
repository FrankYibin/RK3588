﻿import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import HB.Modbus 1.0
import TensionsGlobalDefine 1.0
import HB.Database 1.0
import HB.Enums 1.0
Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_TENSIONS_SETTING
    readonly property int textWidth: 100
    readonly property int comboBoxWidth: 150
    readonly property int rowSpacing: 10
    readonly property int columnSpacing: 30
    readonly property int optionHeight: 30
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
                id: titleKvalue
                width: Math.round(textWidth * Style.scaleHint)
                height: parent.height
                text: qsTr("K值") + ":"
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor
            }
            HBTextField
            {
                id: textKvalue
                text: TensionSetting.KValue
                width: Math.round(150 * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                onlyForNumpad: true

                onSignalClickedEvent: {
                    mainWindow.showPrimaryNumpad(qsTr("请输入K值"), " ", 3, 0, 99999, textKvalue.text,textKvalue,function(val) {
                        TensionSetting.KValue = val;
                        ModbusClient.writeRegister(HQmlEnum.K_VALUE, val)
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
                id: titleTensionUnit
                width: Math.round(textWidth * Style.scaleHint)
                height: parent.height
                text: qsTr("张力单位") + ":"
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor

            }
            HBComboBox
            {
                id: comboBoxTensionUnits
                model: TensionsGlobalDefine.tensionUnitModel
                currentIndex: TensionSetting.TensionUnit
                width: Math.round(comboBoxWidth * Style.scaleHint)
                height: parent.height
                onCurrentIndexChanged: {
                    TensionSetting.TensionUnit = currentIndex
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
                id: titleTensionLimited
                width: Math.round(textWidth * Style.scaleHint)
                height: parent.height
                text: qsTr("极限张力") + ":"
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor
            }
            HBTextField
            {
                id: textTensionLimited
                text: TensionSetting.TensionLimited
                width: Math.round(150 * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                onlyForNumpad: true

                onSignalClickedEvent: {
                    mainWindow.showPrimaryNumpad(qsTr("请输入极限张力"), " ", 3, 0, 99999, textTensionLimited.text, textTensionLimited, function(val) {
                        TensionSetting.TensionLimited = val;
                        ModbusClient.writeRegister(HQmlEnum.TENSION_LIMITED_H, val)
                    })
                }
            }
            Text
            {
                id: unitTensionLimited
                text: TensionsGlobalDefine.tensionUnitModel[TensionSetting.TensionUnit] //qsTr("kg")
                anchors.verticalCenter: textTensionLimited.verticalCenter
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.whiteFontColor
            }
        }

        Row
        {
            width: parent.width
            height: Math.round(optionHeight * Style.scaleHint)
            spacing: Math.round(rowSpacing * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
            Text {
                id: titleTensionLimitedDelta
                width: Math.round(textWidth * Style.scaleHint)
                height: parent.height
                text: qsTr("极限张力增量") + ":"
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor
            }
            HBTextField
            {
                id: textTensionLimitedDelta
                text: TensionSetting.TensionLimitedDelta
                width: Math.round(150 * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                onlyForNumpad: true
                onSignalClickedEvent: {
                    mainWindow.showPrimaryNumpad(qsTr("请输入极限张力增量"), " ", 3, 0, 99999, textTensionLimitedDelta.text, textTensionLimitedDelta, function(val) {
                        TensionSetting.TensionLimitedDelta = val;
                        ModbusClient.writeRegister(HQmlEnum.TENSION_LIMITED_DELTA_H, val)
                    })
                }
            }
            Text
            {
                id: unitTensionLimitedDelta
                text: TensionsGlobalDefine.tensionUnitModel[TensionSetting.TensionUnit] + "/s" //qsTr("kg/s")
                anchors.verticalCenter: textTensionLimitedDelta.verticalCenter
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.whiteFontColor
            }
        }


    }
    // Connections {
    //     target: TensionSetting
    //     function onTensionUnitChanged() {
    //             HBDatabase.updateTensionUnit(TensionSetting.TensionUnit)
    //         }
    // }
}


