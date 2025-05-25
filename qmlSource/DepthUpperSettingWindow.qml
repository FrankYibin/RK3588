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
        title: qsTr("井口段")
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
            columns: 2
            rows: 3
            rowSpacing: Math.round(20 * Style.scaleHint)
            columnSpacing: Math.round(80 * Style.scaleHint)

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn1 + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleDepthPreset
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("深度预置") + ":"
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
                        mainWindow.showPrimaryNumpad(qsTr("请输入深度预置值"), " ", 3, 0, 99999, textDepthPreset.text,textDepthPreset,function(val){
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
                width: Math.round((textWidthColumn1 + componentWidth + textWidthUnit + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleWarning
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("报警") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textWarning
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    // text: qsTr("192")
                    text: DepthSafe.WellWarnig
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("请输入报警值"), " ", 3, 0, 99999, textWarning.text,textWarning,function(val){
                            DepthSafe.WellWarnig = val;
                        })
                    }
                }
                Text {
                    id: unitWarning
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
                width: Math.round((textWidthColumn1 + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleBrake
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("刹车") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textBrake
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    // text: qsTr("192")
                    text:DepthSafe.Brake
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("请输入刹车值"), " ", 3, 0, 99999, textBrake.text,textBrake,function(val){
                            DepthSafe.Brake = val;
                        })
                    }
                }
                Text {
                    id: unitBrake
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
                    text: qsTr("井口段限速") + ":"
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

            HBPrimaryButton
            {
                id: buttonConfirm
                width: Math.round(105 * Style.scaleHint)
                height: Math.round(optionHeight * Style.scaleHint)
                text: qsTr("确定")
                onClicked:
                {
                    // controlLimitNumpad.visible = false
                    HBDatabase.updateDepthSafeFromInstance()
                }
            }
        }

    }

    HBGroupBox
    {
        id: parameterView
        title: qsTr("总深度")
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
            columns: 2
            rows: 3
            rowSpacing: Math.round(40 * Style.scaleHint)
            columnSpacing: Math.round(80 * Style.scaleHint)

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidthColumn1 + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleDepthWarning
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("报警") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textDepthWarning
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    // text: qsTr("192")
                    text:DepthSafe.DepthWarning
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("请输入报警值"), " ", 3, 0, 99999, textDepthWarning.text,textDepthWarning,function(val){
                            DepthSafe.DepthWarning = val;
                        })
                    }
                }
                Text {
                    id: unitDepthWarning
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
                    id: titleTotalDepth
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("总深度") + ":"
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
                width: Math.round((textWidthColumn1 + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleDepthBrake
                    width: Math.round(textWidthColumn1 * Style.scaleHint)
                    height: parent.height
                    text: qsTr("刹车") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textDepthBrake
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    fontSize: Math.round(Style.style4 * Style.scaleHint)
                    // maximumLength: 16
                    // validator: RegularExpressionValidator{
                    //     regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    // }
                    maximumLength: 5
                    validator: IntValidator {
                        bottom: 0
                        top: 9999
                    }
                    // text: qsTr("192")
                    text:DepthSafe.DepthBrake
                    onlyForNumpad: true

                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("请输入总深度值"), " ", 3, 0, 99999, textDepthBrake.text,textDepthBrake,function(val){
                            DepthSafe.DepthBrake = val;})
                    }

                }
                Text {
                    id: unitDepthBrake
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
                    text: qsTr("井底段限速") + ":"
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
                        mainWindow.showPrimaryNumpad(qsTr("请输井底段限速值"), " ", 3, 0, 99999, textDepthVelocityLimit.text,textDepthVelocityLimit,function(val){
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
        }

    }
}


