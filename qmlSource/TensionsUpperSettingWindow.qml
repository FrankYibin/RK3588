﻿import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import HB.Modbus 1.0
import HB.Database 1.0
import HB.Enums 1.0
import ProfileGlobalDefine 1.0
import DepthGlobalDefine 1.0
import TensionsGlobalDefine 1.0

Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_TENSIONS_SETTING
    readonly property int textWidthColumn1: 90
    readonly property int textWidthColumn2: 120
    readonly property int textWidthColumn3: 80
    readonly property int textWidthUnit: 20
    readonly property int componentWidth: 85
    readonly property int comboxWidth: 60 + 20 + 10 + 20
    readonly property int rowSpacing: 10
    readonly property int columnSpacing: 12
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

    HBGroupBox
    {
        id: parameterSetting
        title: qsTr("参数设置")
        anchors.top: parent.top
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
        width: parent.width - Math.round(10 * Style.scaleHint)
        height: parent.height / 2 - Math.round(15 * Style.scaleHint)
        backgroundColor: Style.backgroundLightColor

        Grid
        {
            anchors.centerIn: parent
            columns: 3
            rows: 3
            rowSpacing: Math.round(20 * Style.scaleHint)
            columnSpacing: Math.round(5 * Style.scaleHint)

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn1 + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleWellType
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("油气井类型") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBComboBox
                {
                    id: comboWellType
                    model: ProfileGlobalDefine.wellTypeModel
                    currentIndex: TensionSafety.WellType
                    width: Math.round(comboxWidth * Style.scaleHint)
                    height: parent.height
                    fontFamily: "宋体"
                    fontSize: Math.round(Style.style3 * Style.scaleHint)
                    onCurrentIndexChanged: {
                        // TensionSafety.WellType = currentIndex
                        ModbusClient.writeRegister(HQmlEnum.WELL_TYPE, currentIndex)
                    }
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn2 + componentWidth + textWidthUnit + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleHarnessWeightPerEachKilometers
                    width: Math.round(textWidthColumn2 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("电缆每千米重量") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textCableWeight
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    text: TensionSafety.WeightEachKilometerCable
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("请输入电缆每千米重量值"), " ", 3, 0, 99999, textCableWeight.text,textCableWeight,function(val) {
                            //TODO need to do unit exchange
                            TensionSafety.WeightEachKilometerCable = val;
                            ModbusClient.writeRegister(HQmlEnum.WEIGHT_EACH_KILOMETER_CABLE, val)
                        })
                    }
                }
                Text {
                    id: unitHarnessWeightPerEachKilometers
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: qsTr("kg")
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn3 + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleWorkType
                    width: Math.round(textWidthColumn3 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("作业类型") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBComboBox
                {
                    id: comboWorkType
                    model: ProfileGlobalDefine.workTypeModel
                    currentIndex: TensionSafety.WorkType
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontFamily: "宋体"
                    fontSize: Math.round(Style.style3 * Style.scaleHint)
                    onCurrentIndexChanged: {
                        // TensionSafety.WorkType = currentIndex
                        ModbusClient.writeRegister(HQmlEnum.WOKE_TYPE, currentIndex)
                    }
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn1 + textWidthUnit+ componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleSensorWeight
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("仪器串重量") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textSensorWeightValue
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    text: TensionSafety.WeightInstrumentString
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("请输入仪器串重量值"), " ", 3, 0, 99999, textSensorWeightValue.text,textSensorWeightValue,function(val) {
                            TensionSafety.WeightInstrumentString = val;
                            ModbusClient.writeRegister(HQmlEnum.WEIGHT_INSTRUMENT_STRING, val)
                            var logText = `仪器串重量值被修改为：${val}`;
                            HBDatabase.insertOperationLog(logText);
                        })
                    }
                }
                Text {
                    id: unitSensorWeight
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: qsTr("kg")
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn2 + componentWidth + textWidthUnit + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleHarnessPullingStrength
                    width: Math.round(textWidthColumn2 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("电缆拉断力") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textHarnessPullingStrength
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    text: TensionSafety.BreakingForceCable
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("请输入电缆拉断力值"), " ", 3, 0, 99999, textHarnessPullingStrength.text,textHarnessPullingStrength,function(val) {
                            TensionSafety.BreakingForceCable = val;
                            ModbusClient.writeRegister(HQmlEnum.BREAKING_FORCE_CABLE, val)
                            var logText = `电缆拉断力值被修改为：${val}`;
                            HBDatabase.insertOperationLog(logText);
                        })
                    }
                }
                Text {
                    id: unitHarnessPullingStrength
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: qsTr("kg")
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn3 + componentWidth + textWidthUnit + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleWeaknessPullingStrength
                    width: Math.round(textWidthColumn3 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("弱点拉断力") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textWeaknessPullingStrength
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    text: TensionSafety.BreakingForceWeakness
                    onlyForNumpad: true

                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("请输入弱点拉断力值"), " ", 3, 0, 99999, textWeaknessPullingStrength.text,textWeaknessPullingStrength,function(val) {
                            TensionSafety.BreakingForceWeakness = val;
                            ModbusClient.writeRegister(HQmlEnum.BREAKING_FORCE_WEAKNESS, val)
                            var logText = `弱点拉断力值被修改为：${val}`;
                            HBDatabase.insertOperationLog(logText);
                        })
                    }
                }
                Text {
                    id: unitWeaknessPullingStrength
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: qsTr("kg")
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn1 + componentWidth + textWidthUnit + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleUltimateTension
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("极限张力") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textUltimateTension
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    // text: qsTr("8080")
                    text: TensionSafety.TensionLimited
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("请输入极限张力值"), " ", 3, 0, 99999, textUltimateTension.text,textUltimateTension,function(val) {
                            TensionSafety.TensionLimited = val;
                            ModbusClient.writeRegister(HQmlEnum.TENSION_LIMITED_H, val)
                        })
                    }
                }
                Text {
                    id: unitUltimateTension
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: TensionsGlobalDefine.tensionUnitModel[TensionSetting.TensionUnit]
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn2 + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleSafetyTensionFactor
                    width: Math.round(textWidthColumn2 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("安全张力系数") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textSafetyTensionFactor
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    text: TensionSafety.TensionSafetyCoefficient
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("请输入极限张力值"), " ", 3, 0, 99999, textSafetyTensionFactor.text,textSafetyTensionFactor,function(val) {
                            TensionSafety.TensionSafetyCoefficient = val;
                            ModbusClient.writeRegister(HQmlEnum.TENSION_SAFETY_COEFFICIENT, val)
                        })
                    }
                }
            }
        }
    }

    HBGroupBox
    {
        id: parameterView
        title: qsTr("参数预览")
        anchors.top: parameterSetting.bottom
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
        width: parent.width - Math.round(10 * Style.scaleHint)
        height: parent.height / 2 - Math.round(15 * Style.scaleHint)
        backgroundColor: Style.backgroundMiddleColor

        Grid
        {
            anchors.centerIn: parent
            columns: 3
            rows: 3
            rowSpacing: Math.round(20 * Style.scaleHint)
            columnSpacing: Math.round(5 * Style.scaleHint)

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn1 + componentWidth + textWidthUnit + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleCurrentSafetyTension
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("当前安全张力") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textCurrentSafetyTension
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    readOnly: true
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    text: TensionSafety.TensionCurrentSafety
                }
                Text {
                    id: unitCurrentSafetyTension
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: TensionsGlobalDefine.tensionUnitModel[TensionSetting.TensionUnit]
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn2 + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleCableTensionTrend
                    width: Math.round(textWidthColumn2 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("缆头张力变化趋势") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textCableTensionTrend
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    readOnly: true
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    text: TensionsGlobalDefine.tensionCableHeadTrendModel[TensionSafety.TensionCableHeadTrend]
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn3 + componentWidth + textWidthUnit + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleCurrentDepth1
                    width: Math.round(textWidthColumn3 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("编码器1深度") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textCurrentDepth1
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    readOnly: true
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    text: TensionSafety.DepthEncoder1
                }
                Text {
                    id: unitCurrentDepth1
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: DepthGlobalDefine.distanceUnitModel[Depth.DistanceUnit]
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn1 + componentWidth + textWidthUnit + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleMaxSafetyTension
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("最大安全张力") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textMaxSafetyTension
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    readOnly: true
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    text: TensionSafety.TensionLimitedSafety
                }
                Text {
                    id: unitMaxSafetyTension
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: TensionsGlobalDefine.tensionUnitModel[TensionSetting.TensionUnit]
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn2 + componentWidth + textWidthUnit + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleSafetyStopTime
                    width: Math.round(textWidthColumn2 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("安全停车时间") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textSafetyStopTime
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    readOnly: true
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    text: TensionSafety.TimeSafetyStop
                }
                Text {
                    id: unitSafetyStopTime
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: "s"
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn3 + componentWidth + textWidthUnit + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleCurrentDepth2
                    width: Math.round(textWidthColumn3 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("编码器2深度") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textCurrentDepth2
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    readOnly: true
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    text: TensionSafety.DepthEncoder2
                }
                Text {
                    id: unitCurrentDepth2
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: DepthGlobalDefine.distanceUnitModel[Depth.DistanceUnit]
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn1 + componentWidth + textWidthUnit + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleCurrentHarnessTension
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("当前缆头张力") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textCurrentHarnessTension
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    readOnly: true
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    text: TensionSafety.TensionCableHead
                }
                Text {
                    id: unitCurrentHarnessTension
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: TensionsGlobalDefine.tensionUnitModel[TensionSetting.TensionUnit]
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn2 + componentWidth + textWidthUnit + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleDepthTolerance
                    width: Math.round(textWidthColumn2 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("深度误差") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textDepthTolerance
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    readOnly: true
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    text:TensionSafety.DepthTolerance
                }
                Text {
                    id: unitDepthTolerance
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: DepthGlobalDefine.distanceUnitModel[Depth.DistanceUnit]
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn3 + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleCurrentDepth3
                    width: Math.round(textWidthColumn3 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("编码器3深度") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textCurrentDepth3
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    readOnly: true
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    text:TensionSafety.DepthEncoder3
                }
                Text {
                    id: unitCurrentDepth3
                    width: Math.round(textWidthColumn3 * Style.scaleHint)
                    height: parent.height
                    text: DepthGlobalDefine.distanceUnitModel[Depth.DistanceUnit]
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }
        }
    }
}


