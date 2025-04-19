import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_DEPTH_SETTING
    readonly property int textWidthColumn1: 100
    readonly property int textWidthColumn2: 130
    readonly property int textWidthColumn3: 80
    readonly property int textWidthUnit: 20
    readonly property int componentWidth: 100
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

    Item
    {
        id: preset
        width: parent.width / 2
        height: parent.height / 2
        Column
        {
            anchors.centerIn: parent
            spacing: Math.round(20 * Style.scaleHint)

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn1 + textWidthUnit+ componentWidth + rowSpacing) * Style.scaleHint)
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
                    id: textDepthPreset
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    text: qsTr("8081")
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad("Time Scale Setting", "s", 3, 0, 5, "0.123")
                    }
                }
                Text {
                    id: unitDepthPreset
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: "m"
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }

            HBPrimaryButton
            {
                id: buttonConfirm
                width: Math.round(105 * Style.scaleHint)
                height: Math.round(optionHeight * Style.scaleHint)
                text: qsTr("确定")
                onClicked:
                {
                    // controlLimitNumpad.visible = false
                }
            }

        }
    }

    Item {
        id: actual
        anchors.left: preset.left
        anchors.top: preset.bottom
        width: parent.width / 2
        height: parent.height / 2
        // Rectangle {
        //     anchors.centerIn: parent
            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn1 + textWidthUnit+ componentWidth + rowSpacing) * Style.scaleHint)
                anchors.centerIn: parent
                spacing: rowSpacing
                Text {
                    id: titleCurrentDepth
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("深度倒计") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
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
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    text: "8081"
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad("Time Scale Setting", "s", 3, 0, 5, "0.123")
                    }
                }
                Text {
                    id: unitCurrentDepth
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: "m"
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }
        // }
    }

    Item {
        id: pandel
        anchors.top: preset.top
        anchors.left: preset.right
        width: parent.width / 2
        height: parent.height

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


