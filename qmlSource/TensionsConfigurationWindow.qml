import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import HB.Modbus 1.0
Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_TENSIONS_SETTING
    readonly property int textWidth: 50
    readonly property int comboBoxWidth: 150
    readonly property int rowSpacing: 100
    readonly property int columnSpacing: 30
    readonly property int optionHeight: 30
    readonly property var tensionModel: [qsTr("LB"),qsTr("KG"),qsTr("KN")]
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
        height: Math.round((optionHeight * 2 + columnSpacing * 1) * Style.scaleHint)
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
            // HBComboBox
            // {
            //     id:comboBoxPort
            //     width: Math.round(comboBoxWidth * Style.scaleHint)
            //     height: parent.height
            // }
            HBTextField
            {
                id: textKvalue
                //                    text: qsTr("4000.00")
                text: HBHome.KValue
                width: Math.round(150 * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                onlyForNumpad: true

                onSignalClickedEvent: {
                    console.log("textKvalue.text =", textKvalue.text);
                     console.log("textKvalue =", textKvalue);
                    mainWindow.showPrimaryNumpad(qsTr("请输入K值"), " ", 3, 0, 99999, textKvalue.text,textKvalue,function(val) {
                        HBHome.KValue = val;
                        ModbusClient.writeRegister(36,[parseInt(val)])
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
                model:tensionModel
                // currentIndex: Tensiometer.TensionUnits
                width: Math.round(comboBoxWidth * Style.scaleHint)
                height: parent.height
                Component.onCompleted: {
                      comboBoxTensionUnits.currentIndex = Tensiometer.TensionUnits
                  }

                onCurrentIndexChanged: {
                    Tensiometer.TensionUnits = currentIndex
                    console.log("TensionUnit" + currentIndex)
                }
            }

        }
    }

}


