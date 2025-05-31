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
    readonly property int textWidthColumn1: 100
    readonly property int textWidthColumn2: 130
    readonly property int textWidthColumn3: 80
    readonly property int textWidthUnit: 100
    readonly property int componentWidth: 100
    readonly property int actualTextWidth: 150
    readonly property int buttonWidth: 100
    readonly property int rowSpacing: 10
    readonly property int columnSpacing: 10
    readonly property int optionHeight: 30
    readonly property int actualHeight: 100
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
        id: preset
        anchors.top: parent.top
        anchors.topMargin: Math.round(parent.height/4)
        width: parent.width
        height: Math.round(optionHeight * Style.scaleHint)
        Row{
            height: Math.round(optionHeight * Style.scaleHint)
            width: Math.round((textWidthColumn1 + textWidthUnit+ componentWidth + buttonWidth + 2 * rowSpacing) * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin: Math.round(100 * Style.scaleHint)
            anchors.top: parent.top
            spacing: rowSpacing
            Text {
                id: titleDepthPreset
                width: Math.round(textWidthColumn1 * Style.scaleHint)
                height: parent.height
                text: qsTr("深度倒计设置") + ":"
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor
            }
            HBTextField
            {
                id: textSDepthPreset
                width: Math.round(componentWidth * Style.scaleHint)
                height: parent.height
                fontSize: Math.round(Style.style4 * Style.scaleHint)
                maximumLength: 16
                validator: RegularExpressionValidator{
                    regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                }
                // text: qsTr("8081")
                text:AutoTestSpeed.DepthCountDown
                onlyForNumpad: true
                onSignalClickedEvent: {
                    mainWindow.showPrimaryNumpad(qsTr("请输入深度倒计值"), " ", 3, 0, 99999, textSDepthPreset.text,textSDepthPreset,function(val) {
                        //TODO Need to Unit exchange function
                        AutoTestSpeed.DepthCountDown = val;
                        ModbusClient.writeRegister(HQmlEnum.DEPTH_COUNTDOWN,[parseInt(val)])
                    })
                }
            }
            Text {
                id: unitDepthPreset
                width: Math.round(textWidthUnit * Style.scaleHint)
                height: parent.height
                text: DepthGlobalDefine.distanceUnitModel[Depth.DistanceUnit]
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor
            }

            HBPrimaryButton
            {
                id: buttonConfirm
                width: Math.round(buttonWidth * Style.scaleHint)
                height: Math.round(optionHeight * Style.scaleHint)
                text: qsTr("确定")
                onClicked:
                {
                    mainWindow.showDepthCountDown()
                }
            }
        }

    }

    Item {
        id: actual
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: parent.width
        height: parent.height / 2
        Row{
            height: Math.round(actualHeight * Style.scaleHint)
            width: Math.round((textWidthColumn1 + textWidthUnit+ actualTextWidth + rowSpacing) * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin: Math.round(100 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            spacing: rowSpacing
            Text {
                id: titleCurrentDepth
                width: Math.round(textWidthColumn1 * Style.scaleHint)
                height: Math.round(optionHeight * Style.scaleHint)
                text: qsTr("深度倒计") + ":"
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor
                anchors.verticalCenter: parent.verticalCenter
            }
            HBTextField
            {
                id: textCurrentDepth
                width: Math.round((actualTextWidth) * Style.scaleHint)
                height: parent.height
                fontSize: Math.round(Style.style8 * Style.scaleHint)
                maximumLength: 16
                validator: RegularExpressionValidator{
                    regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                }
                // text: "8081"
                text: HBHome.Depth
                onlyForNumpad: true
                onSignalClickedEvent: {
                    mainWindow.showPrimaryNumpad("请输入深度倒计值", " ", 3, 0, 99999, "0.123")
                }
            }
            Text {
                id: unitCurrentDepth
                width: Math.round(textWidthUnit * Style.scaleHint)
                height: parent.height
                text: DepthGlobalDefine.distanceUnitModel[Depth.DistanceUnit]
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor
            }
        }
    }

    Item {
        id: pandel
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(60 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(40 * Style.scaleHint)
        width: parent.width / 3
        height: parent.height / 3

        function valueToAngel(value)
        {
            if(value < 0)
                value = 0
            if(value > 1200)
                value = 1200
            return ((240/ 1200) * value + 60)
        }

        HBPandel
        {
            id: pandelDepth
            anchors.centerIn: parent
            width: 400
            height: 400
            angle: pandel.valueToAngel(Number(textCurrentDepth.text))
        }
    }
}


