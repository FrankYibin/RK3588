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
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_VELOCITY
    Component.onCompleted: {
        modelDirectionMode.resetModel()
        AutoTestSpeed.VelocityStatus = 1;
        AutoTestSpeed.VelocitySetting = "200.00"
    }

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

    ListModel {
        id: modelDirectionMode
        function resetModel()
        {
            modelDirectionMode.clear()
            modelDirectionMode.append({"OptionName":    "上提",
                                      "OptionIndex":    0,
                                      })
            modelDirectionMode.append({"OptionName":    "下放",
                                      "OptionIndex":    1,
                                      })
        }
    }

    Item
    {
        id: controlSetting
        width: parent.width / 3 * 2
        height: parent.height / 3 * 2
        anchors.centerIn: parent
        Column
        {
            width: parent.width
            height: parent.height
            spacing: Math.round(50 * Style.scaleHint)
            Row {
                width: parent.width / 3 * 2
                height: Math.round(30 * Style.scaleHint)
                spacing: Math.round(25 * Style.scaleHint)
                ExclusiveGroup {id: directionControlGroup}
                Text
                {
                    height: parent.height
                    width: Math.round(100 * Style.scaleHint)
                    color: Style.whiteFontColor
                    text: "控速方向:"
                    wrapMode: Text.WordWrap
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                }
                Repeater {
                    model: modelDirectionMode
                    delegate: HBRadioButton
                    {
                        id: controlRadioButton
                        height: Math.round(30 * Style.scaleHint)
                        width: parent.width/2
                        labelText:  model.OptionName
                        circleSize: height
                        exclusiveGroup: directionControlGroup
                        checked: {
                            switch(AutoTestSpeed.VelocityStatus)
                            {
                            case 0:
                                return false;
                            case 1:
                                if(index === 0)
                                    return true;
                                else
                                    return false;
                            case 2:
                                if(index === 1)
                                    return false;
                                else
                                    return true;
                            }
                        }
                        onClicked:
                        {
                            // nCurrentLanguageIndex = model.itemIndex
                            console.debug("index: ", index)

                            if(index === 0)
                                AutoTestSpeed.VelocityStatus = 1
                            else if (index === 1)
                                AutoTestSpeed.VelocityStatus = 2
                            else
                                AutoTestSpeed.VelocitySetting = 3
                        }
                    }
                }
            }

            Row
            {
                id: infoWellDepth
                width: parent.width
                height: Math.round(30 * Style.scaleHint)
                spacing: Math.round(10 * Style.scaleHint)
                Text
                {
                    id: titleVelocitySetting
                    width: Math.round(120 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("请输入控速值：")
                    font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                    verticalAlignment: Text.AlignVCenter
                }
                HBTextField
                {
                    id: textVelocitySetting
                    // text: qsTr("255.00")
                    //开机获取
                    text: AutoTestSpeed.VelocitySetting
                    width: Math.round(200 * Style.scaleHint)
                    height: Math.round(25 * Style.scaleHint)
                    onlyForNumpad: true
                    //输入写入
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("请输入控速值"), " ", 2, 0, 99999, textVelocitySetting.text, textVelocitySetting, function(val) {
                            AutoTestSpeed.VelocitySetting = val;
                        })
                    }
                }
                Text
                {
                    id: unitVelocity
                    text: DepthGlobalDefine.velocityUnitModel[Depth.VelocityUnit]
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.whiteFontColor
                    verticalAlignment: Text.AlignBottom
                }
            }


            Text {
                height: Math.round(30 * Style.scaleHint)
                color: Style.redFontColor
                text: "注： 请将控速手柄恢复至零位，并将滚筒速度降低至零。"
                wrapMode: Text.WordWrap
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
            }
        }
    }


    Row
    {
        id: buttons
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(100 * Style.scaleHint)
        width: Math.round(350 * Style.scaleHint)
        anchors.left: controlSetting.left
        anchors.leftMargin: Math.round(20 * Style.scaleHint)
        spacing: Math.round(100 * Style.scaleHint)

        HBPrimaryButton
        {
            id: buttonImport
            width: Math.round(125 * Style.scaleHint)
            height: Math.round(40 * Style.scaleHint)
            text: qsTr("启动")
            buttonColor: (AutoTestSpeed.EnableVelocityControl === 0) ? Style. hbButtonBackgroundColor : Style.hbButtonCVBackgroundColor
            onClicked:
            {
                var status = AutoTestSpeed.VelocityStatus
                ModbusClient.writeRegister(HQmlEnum.VELOCITY_STATUS, status)
                ModbusClient.writeRegister(HQmlEnum.VELOCITY_SETTING_H, AutoTestSpeed.VelocitySetting)
            }
        }

        HBPrimaryButton
        {
            id: buttonSave
            width: Math.round(125 * Style.scaleHint)
            height: Math.round(40 * Style.scaleHint)
            text: qsTr("停止")
            onClicked:
            {
                ModbusClient.writeRegister(HQmlEnum.VELOCITY_STATUS, 0)
            }
        }
    }



}


