import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import HB.Database 1.0
Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_DEPTH_SETTING
    readonly property int textWidthColumn1: 100
    readonly property int textWidthColumn2: 130
    readonly property int textWidthColumn3: 80
    readonly property int textWidthUnit: 20
    readonly property int componentWidth: 100
    readonly property int rowSpacing: 5
    readonly property int columnSpacing: 10
    readonly property int optionHeight: 30
    readonly property int switchHeight: 25
    readonly property int switchWidth: 80

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
        id: parameterUpperSetting
        title: qsTr("井口段")
        anchors.top: parent.top
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
        width: parent.width / 2 - Math.round(10 * Style.scaleHint)
        height: parent.height / 2 - Math.round(15 * Style.scaleHint)
        backgroundColor: Style.backgroundLightColor

        Column
        {
            anchors.left: parent.left
            anchors.leftMargin: (20 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            spacing: Math.round(10 * Style.scaleHint)

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn1 + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleDepthPreset
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("距井口距离") + ":"
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
                    // text: qsTr("192")
                    text: DepthSafe.DepthPreset
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("请输入井口距离值"), " ", 3, 0, 99999, textDepthPreset.text,textDepthPreset,function(val){
                            DepthSafe.DepthPreset = val;
                        })
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

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn1 + textWidthUnit+ componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleVelocityLimit
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("稳速") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textVelocityLimit
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    // text: qsTr("8081")
                    text:DepthSafe.VelocityLimit
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("请输入井口段限速值"), " ", 3, 0, 99999, textVelocityLimit.text,textVelocityLimit,function(val){
                            DepthSafe.VelocityLimit = val;})
                    }
                }
                Text {
                    id: unitVelocityLimit
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: "m/min"
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
                Item{
                    id: titleWarning
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("报警") + ":"
                        font.family: "宋体"
                        font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                        // verticalAlignment: Text.AlignVCenter
                        color: Style.whiteFontColor
                    }
                }

                BransonSwitch{
                    id: switchWarning
                    anchors.verticalCenter: titleWarning.verticalCenter
                    rectWidth: Math.round((switchWidth) * Style.scaleHint)
                    rectHeight: Math.round(switchHeight * Style.scaleHint)
                    maxWidth: Math.round(optionHeight * Style.scaleHint)
                    maxHeight: maxWidth
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn1 + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Item{
                    id: titleBrake
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("停车") + ":"
                        font.family: "宋体"
                        font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                        color: Style.whiteFontColor
                    }
                }

                BransonSwitch{
                    id: switchBrake
                    anchors.verticalCenter: titleBrake.verticalCenter
                    rectWidth: Math.round((switchWidth) * Style.scaleHint)
                    rectHeight: Math.round(switchHeight * Style.scaleHint)
                    maxWidth: Math.round(optionHeight * Style.scaleHint)
                    maxHeight: maxWidth
                }


            }

            // HBPrimaryButton
            // {
            //     id: buttonConfirm
            //     width: Math.round(105 * Style.scaleHint)
            //     height: Math.round(optionHeight * Style.scaleHint)
            //     text: qsTr("确定")
            //     onClicked:
            //     {
            //         // controlLimitNumpad.visible = false
            //         HBDatabase.updateDepthSafeFromInstance()
            //     }
            // }
        }

    }

    HBGroupBox
    {
        id: parameterLowerSetting
        title: qsTr("井底段")
        anchors.top: parent.top
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(5 * Style.scaleHint)
        width: parent.width / 2 - Math.round(10 * Style.scaleHint)
        height: parent.height / 2 - Math.round(15 * Style.scaleHint)
        backgroundColor: Style.backgroundLightColor

        Column
        {
            anchors.left: parent.left
            anchors.leftMargin: (20 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            spacing: Math.round(10 * Style.scaleHint)

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn1 + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleDepthLowerPreset
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("距井口距离") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textDepthLowerPreset
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    // text: qsTr("192")
                    text: DepthSafe.DepthPreset
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("请输入井口距离值"), " ", 3, 0, 99999, textDepthPreset.text,textDepthPreset,function(val){
                            DepthSafe.DepthPreset = val;
                        })
                    }
                }
                Text {
                    id: unitDepthLowerPreset
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
                width: Math.round((textWidthColumn1 + textWidthUnit+ componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleVelocityLowerLimit
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("稳速") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textVelocityLowerLimit
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    // text: qsTr("8081")
                    text:DepthSafe.VelocityLimit
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("请输入井口段限速值"), " ", 3, 0, 99999, textVelocityLimit.text,textVelocityLimit,function(val){
                            DepthSafe.VelocityLimit = val;})
                    }
                }
                Text {
                    id: unitVelocityLowerLimit
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: "m/min"
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
                Item{
                    id: titleLowerWarning
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("报警") + ":"
                        font.family: "宋体"
                        font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                        // verticalAlignment: Text.AlignVCenter
                        color: Style.whiteFontColor
                    }
                }

                BransonSwitch{
                    id: switchLowerWarning
                    anchors.verticalCenter: titleLowerWarning.verticalCenter
                    rectWidth: Math.round((switchWidth) * Style.scaleHint)
                    rectHeight: Math.round(switchHeight * Style.scaleHint)
                    maxWidth: Math.round(optionHeight * Style.scaleHint)
                    maxHeight: maxWidth
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn1 + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Item{
                    id: titleLowerBrake
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("停车") + ":"
                        font.family: "宋体"
                        font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                        color: Style.whiteFontColor
                    }
                }

                BransonSwitch{
                    id: switchLowerBrake
                    anchors.verticalCenter: titleLowerBrake.verticalCenter
                    rectWidth: Math.round((switchWidth) * Style.scaleHint)
                    rectHeight: Math.round(switchHeight * Style.scaleHint)
                    maxWidth: Math.round(optionHeight * Style.scaleHint)
                    maxHeight: maxWidth
                }
            }

            // HBPrimaryButton
            // {
            //     id: buttonConfirm
            //     width: Math.round(105 * Style.scaleHint)
            //     height: Math.round(optionHeight * Style.scaleHint)
            //     text: qsTr("确定")
            //     onClicked:
            //     {
            //         // controlLimitNumpad.visible = false
            //         HBDatabase.updateDepthSafeFromInstance()
            //     }
            // }
        }

    }

    HBGroupBox
    {
        id: parameterView
        title: qsTr("大斜度井段")
        anchors.top: parameterUpperSetting.bottom
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
        width: parent.width / 2 - Math.round(10 * Style.scaleHint)
        height: parent.height / 2 - Math.round(15 * Style.scaleHint)
        backgroundColor: Style.backgroundMiddleColor

        Column
        {
            anchors.left: parent.left
            anchors.leftMargin: (20 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            spacing: Math.round(10 * Style.scaleHint)

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn1 + componentWidth + textWidthUnit + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleTotalDepth
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("斜度") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textTotalDepth
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    // text: qsTr("192")
                    text:DepthSafe.TotalDepth
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("请输入总深度值"), " ", 3, 0, 99999, textTotalDepth.text,textTotalDepth,function(val){
                            DepthSafe.TotalDepth = val;})
                    }
                }
                Text {
                    id: unitTotalDepth
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
                width: Math.round((textWidthColumn1 + textWidthUnit+ componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleDepthVelocityLimit
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("稳速") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textDepthVelocityLimit
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    // text: qsTr("8081")
                    text: DepthSafe.DepthVelocityLimit
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("稳速"), " ", 3, 0, 99999, textDepthVelocityLimit.text,textDepthVelocityLimit,function(val){
                            DepthSafe.DepthVelocityLimit = val;})
                    }
                }
                Text {
                    id: unitDepthVelocityLimit
                    width: Math.round(textWidthUnit * Style.scaleHint)
                    height: parent.height
                    text: "m/min"
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn1 + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Item
                {
                    id: titleDepthWarning
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("报警") + ":"
                        font.family: "宋体"
                        font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                        verticalAlignment: Text.AlignVCenter
                        color: Style.whiteFontColor
                    }
                }
                BransonSwitch{
                    id: switchDepthWarning
                    anchors.verticalCenter: titleDepthWarning.verticalCenter
                    rectWidth: Math.round((switchWidth) * Style.scaleHint)
                    rectHeight: Math.round(switchHeight * Style.scaleHint)
                    maxWidth: Math.round(optionHeight * Style.scaleHint)
                    maxHeight: maxWidth
                }
            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn1 + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Item
                {
                    id: titleDepthBrake
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("停车") + ":"
                        font.family: "宋体"
                        font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                        verticalAlignment: Text.AlignVCenter
                        color: Style.whiteFontColor
                    }
                }
                BransonSwitch{
                    id: switchDepthBrake
                    anchors.verticalCenter: titleDepthBrake.verticalCenter
                    rectWidth: Math.round((switchWidth) * Style.scaleHint)
                    rectHeight: Math.round(switchHeight * Style.scaleHint)
                    maxWidth: Math.round(optionHeight * Style.scaleHint)
                    maxHeight: maxWidth
                }
            }
        }

    }


    HBGroupBox
    {
        id: parameterComplicatedSetting
        title: qsTr("复杂井段")
        anchors.top: parameterUpperSetting.bottom
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(5 * Style.scaleHint)
        width: parent.width / 2 - Math.round(10 * Style.scaleHint)
        height: parent.height / 2 - Math.round(15 * Style.scaleHint)
        backgroundColor: Style.backgroundLightColor
    }
}


