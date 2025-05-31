import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import HB.Modbus 1.0
import HB.Database 1.0
import HB.Enums 1.0
import ProfileGlobalDefine 1.0
Item{
    // Component.onCompleted:
    // {
    //     console.log(Qt.fontFamilies())
    // }
    id: profileLayout
    readonly property int comboBoxWidth: 100

    readonly property var harnessTypeModel: [5.6, 11.8]
    readonly property var tensionUnitModel: [10 , 20, 30]

    HBBackground{
        id: background
        anchors.fill: parent
        // z: -1
    }

    Row
    {
        id: profile
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: Math.round(100 * Style.scaleHint)
        anchors.topMargin: Math.round(50 * Style.scaleHint)
        anchors.rightMargin: Math.round(100 * Style.scaleHint)
        anchors.bottomMargin: Math.round(50 * Style.scaleHint)
        spacing: Math.round(10 * Style.scaleHint)
        Column
        {
            id: leftInfo
            width: Math.round(350 * Style.scaleHint)
            height: Math.round(430 * Style.scaleHint)
            spacing: Math.round(35 * Style.scaleHint)
            Row
            {
                id: infoWellNumber
                width: parent.width
                height: Math.round(30 * Style.scaleHint)
                spacing: Math.round(10 * Style.scaleHint)
                Text
                {
                    id: titleWellNumber
                    width: Math.round(120 * Style.scaleHint)
                    text: qsTr("井号：")
                    font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                }

                HBLineEdit {
                    id: textWellNumber
                    width: Math.round(100 * Style.scaleHint)
                    height: Math.round(25 * Style.scaleHint)
                    text: WellParameter.WellNumber
                    onAccepted: {
                        WellParameter.WellNumber = text;
                    }
                }
            }

            Row
            {
                id: infoAreaBlock
                width: parent.width
                height: Math.round(30 * Style.scaleHint)
                spacing: Math.round(10 * Style.scaleHint)
                Text
                {
                    id: titleAreaBlock
                    width: Math.round(120 * Style.scaleHint)
                    text: qsTr("区块：")
                    font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                }

                HBLineEdit {
                    id: textAreaBlock
                    width: Math.round(100 * Style.scaleHint)
                    height: Math.round(25 * Style.scaleHint)
                    //                    text: qsTr("--")
                    text: WellParameter.AreaBlock
                    onAccepted: {
                        WellParameter.AreaBlock = text;
                    }
                }
            }

            Row
            {
                id: infoWellType
                width: parent.width
                height: Math.round(30 * Style.scaleHint)
                spacing: Math.round(10 * Style.scaleHint)
                Text
                {
                    id: titleWellType
                    width: Math.round(120 * Style.scaleHint)
                    text: qsTr("井斜：")
                    font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                }

                HBComboBox
                {
                    id: comboWellType
                    model: ProfileGlobalDefine.wellTypeModel
                    currentIndex: WellParameter.WellType
                    width: Math.round(comboBoxWidth * Style.scaleHint)
                    height: parent.height
                    fontFamily: "宋体"
                    onCurrentIndexChanged: {
                        WellParameter.WellType = currentIndex
                        ModbusClient.writeRegister(HQmlEnum.OIL_WELL_TYPE, currentIndex)
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
                    id: titleWellDepth
                    width: Math.round(120 * Style.scaleHint)
                    text: qsTr("井深：")
                    font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textWellDepth
                    text: WellParameter.WellDepth
                    width: Math.round(100 * Style.scaleHint)
                    height: Math.round(25 * Style.scaleHint)
                    onlyForNumpad: true

                    onSignalClickedEvent: {
                        console.log("textWellDepth.text =", textWellDepth.text);
                         console.log("textWellDepth =", textWellDepth);
                        mainWindow.showPrimaryNumpad(qsTr("请输入井深值"), " ", 3, 0, 999999, textWellDepth.text,textWellDepth,function(val) {
                            WellParameter.WellDepth = val;
                            ModbusUtils.writeScaledValue(val, 69,100.0)
                        })
                    }

                }
                Text
                {
                    id: unitWellDepth
                    text: qsTr("m")
                    font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.whiteFontColor
                }
            }

            Row
            {
                id: infoHarnessWeight
                width: parent.width
                height: Math.round(30 * Style.scaleHint)
                spacing: Math.round(10 * Style.scaleHint)
                Text
                {
                    id: titleHarnessWeight
                    width: Math.round(120 * Style.scaleHint)
                    text: qsTr("电缆自重：")
                    font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textHarnessWeight
                    text: WellParameter.HarnessWeight
                    width: Math.round(100 * Style.scaleHint)
                    height: Math.round(25 * Style.scaleHint)
                    onlyForNumpad: true

                    onSignalClickedEvent: {
                        console.log("textHarnessWeight.text =", textHarnessWeight.text);
                         console.log("textHarnessWeight =", textHarnessWeight);
                        mainWindow.showPrimaryNumpad(qsTr("请输入电缆自重值"), " ", 3, 0, 99999, textHarnessWeight.text,textHarnessWeight,function(val) {
                            //TODO need to unit exchange
                            WellParameter.HarnessWeight = val;
                            ModbusClient.writeRegister(HQmlEnum.CABLE_UINT, [parseInt(val)])
                        })
                    }
                }
                Text
                {
                    id: unitHarnessWeight
                    text: qsTr("kg")
                    font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.whiteFontColor
                }
            }

            Row
            {
                id: infoSensorWeight
                width: parent.width
                height: Math.round(30 * Style.scaleHint)
                spacing: Math.round(10 * Style.scaleHint)
                Text
                {
                    id: titleSensorWeight
                    width: Math.round(120 * Style.scaleHint)
                    text: qsTr("仪器串重量：")
                    font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textSensorWeight
                    //                    text: qsTr("300.00")
                    text: WellParameter.SensorWeight
                    width: Math.round(100 * Style.scaleHint)
                    height: Math.round(25 * Style.scaleHint)
                    onlyForNumpad: true

                    onSignalClickedEvent: {
                        console.log("textHarnessWeight.text =", textSensorWeight.text);
                         console.log("textHarnessWeight =", textSensorWeight);
                        mainWindow.showPrimaryNumpad(qsTr("请输入仪器串重量值"), " ", 3, 0, 99999, textSensorWeight.text,textSensorWeight,function(val) {
                            WellParameter.SensorWeight = val;
                            ModbusClient.writeRegister(HQmlEnum.SENSOR_WEIGHT, [parseInt(val)])
                        })
                    }

                }
                Text
                {
                    id: unitSensorWeight
                    text: qsTr("kg")
                    font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.whiteFontColor
                }
            }

        }

        Column
        {
            id: rightInfo
            width: Math.round(350 * Style.scaleHint)
            height: Math.round(430 * Style.scaleHint)
            spacing: Math.round(35 * Style.scaleHint)
            Row
            {
                id: infoHarnessType
                width: parent.width
                height: Math.round(30 * Style.scaleHint)
                spacing: Math.round(10 * Style.scaleHint)
                Text
                {
                    id: titleHarnessType
                    width: Math.round(120 * Style.scaleHint)
                    text: qsTr("电缆规格：")
                    font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                }

                //                HBTextField
                //                {
                //                    id: textHarnessType
                //                    text: qsTr("5.6")
                //                    width: Math.round(100 * Style.scaleHint)
                //                    height: Math.round(25 * Style.scaleHint)
                //                    onlyForNumpad: true
                //                    onSignalClickedEvent: {
                //                        mainWindow.showPrimaryNumpad("请输入电缆规格", " ", 3, 0, 5, "0.123")
                //                    }
                //                }
                HBComboBox
                {
                    id: comboHarnessType
                    model: harnessTypeModel
                    currentIndex: WellParameter.HarnessType
                    width: Math.round(comboBoxWidth * Style.scaleHint)
                    height: parent.height
                    fontFamily: "宋体"
                    onCurrentIndexChanged: {
                        ModbusClient.writeRegister(HQmlEnum.CABLE_TYPE, [currentIndex])
                        WellParameter.HarnessType = currentIndex
                        console.log("HarnessType value： ", [currentIndex])
                    }
                }
            }

            Row
            {
                id: infoHarnessForce
                width: parent.width
                height: Math.round(30 * Style.scaleHint)
                spacing: Math.round(10 * Style.scaleHint)
                Text
                {
                    id: titleHarnessForce
                    width: Math.round(120 * Style.scaleHint)
                    text: qsTr("电缆拉断力：")
                    font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                }

                HBTextField
                {
                    id: textHarnessForce
                    text: WellParameter.HarnessForce
                    width: Math.round(100 * Style.scaleHint)
                    height: Math.round(25 * Style.scaleHint)
                    onlyForNumpad: true

                    onSignalClickedEvent: {
                        console.log("textHarnessForce.text =", textHarnessForce.text);
                         console.log("textHarnessForce =", textHarnessForce);
                        mainWindow.showPrimaryNumpad(qsTr("请输入电缆拉断力"), " ", 3, 0, 99999, textHarnessForce.text,textHarnessForce,function(val) {
                            //TODO Need to unit exchange.
                            WellParameter.HarnessForce = val;
                            ModbusClient.writeRegister(HQmlEnum.HARNESS_FORCE, [parseInt(val)])
                        })
                    }
                }

                Text
                {
                    id: unitHarnessForce
                    text: qsTr("kg")
                    font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.whiteFontColor
                }
            }

            Row
            {
                id: infoTensionUnit
                width: parent.width
                height: Math.round(30 * Style.scaleHint)
                spacing: Math.round(10 * Style.scaleHint)
                Text
                {
                    id: titleTensionUnit
                    width: Math.round(120 * Style.scaleHint)
                    text: qsTr("拉力磅吨位：")
                    font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                }

                HBTextField
                {
                    id: textTensionUnit
                    text: WellParameter.TensionUnit
                    width: Math.round(100 * Style.scaleHint)
                    height: Math.round(25 * Style.scaleHint)
                    onlyForNumpad: true

                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("请输入拉力磅吨位"), " ", 3, 0, 99999, textTensionUnit.text,textTensionUnit,function(val) {
                            //TODO Need to unit exchange.
                            WellParameter.textTensionUnit = val;
                            ModbusClient.writeRegister(HQmlEnum.TENSION_BAR_TONNAGE, [parseInt(val)])
                        })
                    }
                }
                Text
                {
                    id: unitTensionUnit
                    text: qsTr("t")
                    font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.whiteFontColor
                }
            }

            Row
            {
                id: infoWorkType
                width: parent.width
                height: Math.round(30 * Style.scaleHint)
                spacing: Math.round(10 * Style.scaleHint)
                Text
                {
                    id: titleWorkType
                    width: Math.round(120 * Style.scaleHint)
                    text: qsTr("作业类型：")
                    font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                }

                HBComboBox
                {
                    id: comboWorkType
                    model: ProfileGlobalDefine.workTypeModel
                    currentIndex: WellParameter.WorkType
                    width: Math.round(comboBoxWidth * Style.scaleHint)
                    height: parent.height
                    fontFamily: "宋体"
                    onCurrentIndexChanged: {
                        ModbusClient.writeRegister(HQmlEnum.WOKE_TYPE, [currentIndex])
                        WellParameter.WorkType = currentIndex
                        console.log("init WorkType: ", currentIndex)
                    }
                }
            }

            Row
            {
                id: infoUserName
                width: parent.width
                height: Math.round(30 * Style.scaleHint)
                spacing: Math.round(10 * Style.scaleHint)
                Text
                {
                    id: titleUserName
                    width: Math.round(120 * Style.scaleHint)
                    text: qsTr("操作员姓名：")
                    font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                }
                HBLineEdit {
                    id: textUserName
                    width: Math.round(100 * Style.scaleHint)
                    height: Math.round(25 * Style.scaleHint)
                    //                    text: qsTr("王强")
                    text:WellParameter.UserName
                    font.family: "宋体"

                    onFocusChanged: {
                        if (!focus) {
                            WellParameter.UserName = text;
                        }
                    }
                }
            }

            Row
            {
                id: infoUserLevel
                width: parent.width
                height: Math.round(30 * Style.scaleHint)
                spacing: Math.round(10 * Style.scaleHint)
                Text
                {
                    id: titleUserLevel
                    width: Math.round(120 * Style.scaleHint)
                    text: qsTr("操作员工种：")
                    font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                }
                HBLineEdit {
                    id: textUserLevel
                    width: Math.round(100 * Style.scaleHint)
                    height: Math.round(25 * Style.scaleHint)
                    //                    text: qsTr("操作员")
                    text: WellParameter.OperatorType
                    font.family: "宋体"

                    onFocusChanged: {
                        if (!focus) {
                            WellParameter.OperatorType = text;
                        }
                    }
                }
            }

        }

    }


    Row
    {
        id: buttons
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(20 * Style.scaleHint)
        width: Math.round(350 * Style.scaleHint)
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: Math.round(100 * Style.scaleHint)

        HBPrimaryButton
        {
            id: buttonImport
            width: Math.round(125 * Style.scaleHint)
            height: Math.round(40 * Style.scaleHint)
            text: qsTr("导入")
            onClicked:
            {
                // controlLimitNumpad.visible = false
            }
        }

        HBPrimaryButton
        {
            id: buttonSave
            width: Math.round(125 * Style.scaleHint)
            height: Math.round(40 * Style.scaleHint)
            text: qsTr("保存")
            onClicked:
            {
                // controlLimitNumpad.visible = false
                HBDatabase.updateWellParameterFromInstance()
                //                  console.log("是否成功更新数据库：", ok)
                profileLayout.visible = false
                mainWindow.menuParentOptionSelect(UIScreenEnum.HB_DASHBOARD)
            }
        }
    }

}
