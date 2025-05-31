import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import HB.Modbus 1.0
import HB.Enums 1.0
import DepthGlobalDefine 1.0
Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_DEPTH_SETTING
    readonly property int textWidth: 100
    readonly property int componentWidth: 140
    readonly property int rowSpacing: 20
    readonly property int columnSpacing: 30
    readonly property int optionHeight: 30


    readonly property var depthOrientationModel: [qsTr("反"), qsTr("正")]
    readonly property var depthCalculateTypeModel: [qsTr("单编码器"), qsTr("双编码器")]
    readonly property var encorderOptionModel: [qsTr("编码器1"), qsTr("编码器2"),qsTr("编码器3"), qsTr("编码器1-2"), qsTr("编码器2-3"), qsTr("编码器1-3")]

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

    Item
    {
        id: parameterSetting
        anchors.centerIn: parent
        width: parent.width - Math.round(20 * Style.scaleHint)
        height: parent.height / 2 - Math.round(15 * Style.scaleHint)

        Grid
        {
            anchors.centerIn: parent
            columns: 2
            rows: 5
            rowSpacing: Math.round(50 * Style.scaleHint)
            columnSpacing: Math.round(50 * Style.scaleHint)

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidth + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleTargetLayerDepth
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("目的层深度") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textTargetLayerDepth
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^\d{1,5}(\.\d{1,2})?$/
                    }
                    // text: qsTr("192")
                    text: Depth.TargetLayerDepth
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        console.log("textTargetLayerDepth.text =", textTargetLayerDepth.text);
                         console.log("textTargetLayerDepth =", textTargetLayerDepth);
                        mainWindow.showPrimaryNumpad(qsTr("请输入目标层深度"), " ", 2, 0, 99999, textTargetLayerDepth.text, textTargetLayerDepth, function(val) {
                            Depth.TargetLayerDepth = val;
                            ModbusUtils.writeScaledValue(val,HQmlEnum.TARGET_DEPTH_H,100.0)

                        })

                    }
                }
                Text {
                    id: unitTargetLayerDepth
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: DepthGlobalDefine.distanceUnitModel[Depth.DistanceUnit]
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidth + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleDepthOrientation
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("深度方向") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBComboBox
                {
                    id:comboBoxDepthOrientation
                    model: depthOrientationModel
                    currentIndex:  Depth.DepthOrientation
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    // Component.onCompleted: {
                    //     comboBoxDepthOrientation.currentIndex = Depth.DepthOrientation
                    // }

                    onCurrentIndexChanged: {
                        ModbusClient.writeCoil(HQmlEnum.DEPTHORIENTATION,currentIndex)
                        Depth.DepthOrientation = currentIndex
                        console.log("DepthOrientation：" + currentIndex)
                    }
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidth + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleMeterDepth
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("表套深度") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textMeterDepth
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^\d{1,5}(\.\d{1,2})?$/
                    }
                    // text: qsTr("192")
                    text:Depth.MeterDepth
                    onlyForNumpad: true

                    onSignalClickedEvent: {
                        console.log("textMeterDepth.text =", textMeterDepth.text);
                         console.log("textMeterDepth =", textMeterDepth);
                        mainWindow.showPrimaryNumpad(qsTr("请输入表套深度"), " ", 3, 0, 99999, textMeterDepth.text,textMeterDepth,function(val) {
                            Depth.MeterDepth = val;
                            ModbusUtils.writeScaledValue(val,HQmlEnum.METER_DEPTH_H,100.0)
                        })

                    }
                }
                Text {
                    id: unitMeterDepth
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: DepthGlobalDefine.distanceUnitModel[Depth.DistanceUnit]
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }
            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidth + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleCurrentDepth
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("瞬时深度") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textCurrentDepth
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^\d{0,5}(\.\d{0,2})?$/
                    }
                    // text: qsTr("8080")
                    text: HBHome.Depth
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("请输入瞬时深度"), " ", 3, 0, 99999, textCurrentDepth.text, textCurrentDepth,function(val) {
                            HBHome.Depth = val;
                            ModbusUtils.writeScaledValue(val,HQmlEnum.HOLOD_DEPTH_H,100.0)
                        })
                    }
                }
                Text {
                    id: unitCurrentDepth
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: DepthGlobalDefine.distanceUnitModel[Depth.DistanceUnit]
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidth + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleEncorderOption
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("编码器源选择") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBComboBox
                {
                    id: comboBoxEncorderOption
                    model: encorderOptionModel
                    currentIndex: Depth.CodeOption
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    onCurrentIndexChanged: {
                        Depth.CodeOption = currentIndex
                        ModbusClient.writeRegister(HQmlEnum.DEPTHCALCULATETYPE, currentIndex)
                    }
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidth + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleVelocityUnit
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("速度单位") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBComboBox
                {
                    id:comboBoxVelocityUnit
                    model: DepthGlobalDefine.velocityUnitModel
                    currentIndex: Depth.VelocityUnit
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    onCurrentIndexChanged: {
                        Depth.VelocityUnit = currentIndex
                    }
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidth + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titlePulseCount
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("脉冲数") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textPulseCount
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^[1-9][0-9]{4}$/
                    }
                    text: HBHome.Pulse
                    onlyForNumpad: true

                    onSignalClickedEvent: { 
                        mainWindow.showPrimaryNumpad(qsTr("请输入脉冲数"), " ", 0, 1, 99999, textPulseCount.text, textPulseCount, function(val) {
                            ModbusClient.writeRegister(HQmlEnum.PULSE, parseInt(val))
                        })

                    }

                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidth + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleUpperVelocityLimit
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("极限速度") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textUpperVelocityLimit
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^\d{1,5}(\.\d{1,2})?$/
                    }
                    text: HBHome.MaxSpeed
                    onlyForNumpad: true

                    onSignalClickedEvent: {
                        console.log("textPulseCount.text =", textUpperVelocityLimit.text);
                         console.log("textPulseCount =", textUpperVelocityLimit);
                        mainWindow.showPrimaryNumpad(qsTr("请输入极限速度"), " ", 2, 0, 20000, textUpperVelocityLimit.text, textUpperVelocityLimit, function(val) {
                            HBHome.MaxSpeed = val;
                            ModbusUtils.writeScaledValue(val,HQmlEnum.MAX_SPEED_H,100.0)
                        })

                    }
                }
                Text {
                    id: unitUpperVelocityLimit
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: DepthGlobalDefine.velocityUnitModel[Depth.VelocityUnit]
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }

        }
    }

}


