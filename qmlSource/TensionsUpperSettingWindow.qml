﻿import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import HB.Modbus 1.0
import HB.Database 1.0
Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_TENSIONS_SETTING
    readonly property int textWidthColumn1: 100
    readonly property int textWidthColumn2: 130
    readonly property int textWidthColumn3: 80
    readonly property int textWidthUnit: 20
    readonly property int componentWidth: 60
    readonly property int rowSpacing: 10
    readonly property int columnSpacing: 10
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
            columnSpacing: Math.round(30 * Style.scaleHint)

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
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textWellType
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    // text: qsTr("192")
                    text:TensionSafe.WellType
                    onlyForNumpad: true

                    onSignalClickedEvent: {
                        console.log("textWellType.text =", textWellType.text);
                        console.log("textWellType =", textWellType);
                        mainWindow.showPrimaryNumpad("请输入油气井类型", "s", 3, 0, 5, textWellType.text,textWellType,function(val) {
                            TensionSafe.WellType = val;
                        })
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
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
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
                    // text: qsTr("192")
                    text: WellParameter.HarnessWeight
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        console.log("textCableWeight.text =", textCableWeight.text);
                        console.log("textCableWeight =", textCableWeight);
                        mainWindow.showPrimaryNumpad("请输入电缆每千米重量值", "s", 3, 0, 5, textCableWeight.text,textCableWeight,function(val) {
                            WellParameter.HarnessWeight = val;
                            ModbusClient.writeRegister(75,[parseInt(val)])
                        })
                    }
                }
                Text {
                    id: unitHarnessWeightPerEachKilometers
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: "kg"
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
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textWorkType
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    // text: qsTr("192")
                    text: WellParameter.WorkType
                    onlyForNumpad: true
                    // onSignalClickedEvent: {
                    //     console.log("textCableWeight.text =", textCableWeight.text);
                    //     console.log("textCableWeight =", textCableWeight);
                    //     mainWindow.showPrimaryNumpad("请输入作业类型", "s", 3, 0, 5, textCableWeight.text,textCableWeight,function(val) {
                    //         WellParameter.HarnessWeight = val;
                    //         ModbusClient.writeRegister(75,[parseInt(val)])
                    //     })
                    // }
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
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
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
                    // text: qsTr("8081")
                    text: WellParameter.SensorWeight
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        console.log("textSensorWeightValue.text =", textSensorWeightValue.text);
                         console.log("textSensorWeightValue =", textSensorWeight);
                        mainWindow.showPrimaryNumpad("请输入仪器串重量值", "s", 3, 0, 5, textSensorWeightValue.text,textSensorWeightValue,function(val) {
                            WellParameter.SensorWeight = val;
                            ModbusClient.writeRegister(76, [parseInt(val)])
                        })
                    }
                }
                Text {
                    id: unitSensorWeight
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: "kg"
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
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
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
                    // text: qsTr("8080")
                    text: WellParameter.HarnessForce
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        console.log("textHarnessPullingStrength.text =", textHarnessPullingStrength.text);
                         console.log("textHarnessPullingStrength =", textHarnessPullingStrength);
                        mainWindow.showPrimaryNumpad("请输入电缆拉断力值", "s", 3, 0, 5, textHarnessPullingStrength.text,textHarnessPullingStrength,function(val) {
                            WellParameter.HarnessForce = val;
                            ModbusClient.writeRegister(73,[parseInt(val)])
                        })
                    }
                }
                Text {
                    id: unitHarnessPullingStrength
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: "kg"
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
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
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
                    // text: qsTr("8080")
                    text: TensionSafe.WeakForce
                    onlyForNumpad: true

                    onSignalClickedEvent: {
                        console.log("textWeaknessPullingStrength.text =", textWeaknessPullingStrength.text);
                         console.log("textWeaknessPullingStrength =", textWeaknessPullingStrength);
                        mainWindow.showPrimaryNumpad("请输入弱点拉断力值", "s", 3, 0, 5, textWeaknessPullingStrength.text,textWeaknessPullingStrength,function(val) {
                            TensionSafe.WeakForce = val;
                            ModbusClient.writeRegister(74,[parseInt(val)])
                        })
                    }
                }
                Text {
                    id: unitWeaknessPullingStrength
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: "kg"
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
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
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
                    text: HBHome.MaxTension
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        console.log("textUltimateTension.text =", textUltimateTension.text);
                         console.log("textUltimateTension =", textUltimateTension);
                        mainWindow.showPrimaryNumpad("请输入极限张力值", "s", 3, 0, 5, textUltimateTension.text,textUltimateTension,function(val) {
                            HBHome.MaxTension = val;
                            ModbusUtils.writeScaledValue(val,47,100.0);
                        })
                    }
                }
                Text {
                    id: unitUltimateTension
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: "kg"
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
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
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
                    // text: qsTr("8080")
                    text: TensionSafe.TensionSafeFactor
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        console.log("textSafetyTensionFactor.text =", textSafetyTensionFactor.text);
                         console.log("textSafetyTensionFactor =", textSafetyTensionFactor);
                        mainWindow.showPrimaryNumpad("请输入极限张力值", "s", 3, 0, 5, textSafetyTensionFactor.text,textSafetyTensionFactor,function(val) {
                            TensionSafe.TensionSafe = val;
                            ModbusUtils.writeScaledValue(77,[parseInt(val)]);
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
            columnSpacing: Math.round(30 * Style.scaleHint)

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
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
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
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    // text: qsTr("192")
                    text: TensionSafe.CurrentTensionSafe
                    onlyForNumpad: true

                    // onSignalClickedEvent: {
                    //     console.log("textCurrentSafetyTension.text =", textCurrentSafetyTension.text);
                    //      console.log("textCurrentSafetyTension =", textCurrentSafetyTension);
                    //     mainWindow.showPrimaryNumpad("请输入极限张力值", "s", 3, 0, 5, textCurrentSafetyTension.text,textCurrentSafetyTension,function(val) {
                    //         TensionSafe.TensionSafe = val;
                    //         ModbusUtils.writeScaledValue(77,[parseInt(val)]);
                    //     })
                    // }
                }
                Text {
                    id: unitCurrentSafetyTension
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: "kg"
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
                    id: titleHarnessTensionTrend
                    width: Math.round(textWidthColumn2 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("缆头张力变化趋势") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textHarnessTensionTrend
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    // text: qsTr("192")
                    text: TensionSafe.CableTensionTrend
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad("Time Scale Setting", "s", 3, 0, 5, "0.123")
                    }
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
                    text: qsTr("当前深度1") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
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
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    // text: qsTr("192")
                    text: TensionSafe.CurrentDepth1
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad("Time Scale Setting", "s", 3, 0, 5, "0.123")
                    }
                }
                Text {
                    id: unitCurrentDepth1
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: "m"
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
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
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
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    // text: qsTr("8081")
                    text: TensionSafe.MAXTensionSafe
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad("Time Scale Setting", "s", 3, 0, 5, "0.123")
                    }
                }
                Text {
                    id: unitMaxSafetyTension
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: "kg"
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
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
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
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    // text: qsTr("8080")
                    text: TensionSafe.Ptime
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad("Time Scale Setting", "s", 3, 0, 5, "0.123")
                    }
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
                    text: qsTr("当前深度2") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
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
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    // text: qsTr("8080")
                    text: TensionSafe.CurrentDepth2
                    onlyForNumpad: true
                    // onSignalClickedEvent: {
                    //     mainWindow.showPrimaryNumpad("Time Scale Setting", "s", 3, 0, 5, "0.123")
                    // }
                }
                Text {
                    id: unitCurrentDepth2
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: "m"
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
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
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
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    // text: qsTr("8080")
                    text: HBHome.HarnessTension
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad("Time Scale Setting", "s", 3, 0, 5, "0.123")
                    }
                }
                Text {
                    id: unitCurrentHarnessTension
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: "kg"
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
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
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
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    // text: qsTr("8080")
                    text:TensionSafe.DepthLoss
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad("Time Scale Setting", "s", 3, 0, 5, "0.123")
                    }
                }
                Text {
                    id: unitDepthTolerance
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: "m"
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
                    text: qsTr("当前深度3") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
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
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    // text: qsTr("8080")
                    text:TensionSafe.CurrentDepth3
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad("Time Scale Setting", "s", 3, 0, 5, "0.123")
                    }
                }
                Text {
                    id: unitCurrentDepth3
                    width: Math.round(textWidthColumn3 * Style.scaleHint)
                    height: parent.height
                    text: "m"
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }
        }
    }
}


