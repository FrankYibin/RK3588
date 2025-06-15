import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_HISTORY_DATA
    readonly property int textWidth: 50
    readonly property int componentWidth: 160
    readonly property int rowSpacing: 50
    readonly property int columnSpacing: 30
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
        id: local
        title: qsTr("地面仪")
        anchors.top: parent.top
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(10 * Style.scaleHint)
        width: parent.width - Math.round(20 * Style.scaleHint)
        height: parent.height / 2 - Math.round(15 * Style.scaleHint)
        backgroundColor: Style.backgroundLightColor

        Grid
        {
            anchors.centerIn: parent
            columns: 2
            rows: 3
            rowSpacing: Math.round(20 * Style.scaleHint)
            columnSpacing: Math.round(50 * Style.scaleHint)

//            Row{
//                height: Math.round(optionHeight * Style.scaleHint)
//                width: Math.round((textWidth + componentWidth + rowSpacing) * Style.scaleHint)
//                spacing: rowSpacing
//                Text {
//                    id: titleLocalProtocol
//                    width: Math.round(textWidth * Style.scaleHint)
//                    height: parent.height
//                    text: qsTr("协议") + ":"
//                    font.family: "宋体"
//                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
//                    verticalAlignment: Text.AlignVCenter
//                    color: Style.whiteFontColor
//                }
//                HBComboBox
//                {
//                    id: comboBoxLocalProtocol
//                    width: Math.round(componentWidth * Style.scaleHint)
//                    height: parent.height
//                }
//            }

//            Row{
//                height: Math.round(optionHeight * Style.scaleHint)
//                width: Math.round((textWidth + componentWidth + rowSpacing) * Style.scaleHint)
//                spacing: rowSpacing
//                Text {
//                    id: titleLocalRemoteIP
//                    width: Math.round(textWidth * Style.scaleHint)
//                    height: parent.height
//                    text: qsTr("远程IP") + ":"
//                    font.family: "宋体"
//                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
//                    verticalAlignment: Text.AlignVCenter
//                    color: Style.whiteFontColor
//                }
//                HBTextField
//                {
//                    id: textLocalRemoteIP
//                    width: Math.round(componentWidth * Style.scaleHint)
//                    height: parent.height
//                    maximumLength: 16
//                    validator: RegularExpressionValidator{
//                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
//                    }
//                    text: qsTr("192.168.111.101")
//                    fontSize: Math.round(Style.style4 * Style.scaleHint)
//                    onlyForNumpad: true
//                    onSignalClickedEvent: {
//                        mainWindow.showPrimaryNumpad(qsTr("远程IP"), "IPV4", 3, 0, 255, "0.123")
//                    }
//                }
//            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidth + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleLocalIP
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("本地IP") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textLocalIP
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    text: qsTr("192.168.111.101")
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("本地IP"), "IPV4", 3, 0, 255, "0.123")
                    }
                }
            }

//            Row{
//                height: Math.round(optionHeight * Style.scaleHint)
//                width: Math.round((textWidth + componentWidth + rowSpacing) * Style.scaleHint)
//                spacing: rowSpacing
//                Text {
//                    id: titleLocalRemotePort
//                    width: Math.round(textWidth * Style.scaleHint)
//                    height: parent.height
//                    text: qsTr("远程端口") + ":"
//                    font.family: "宋体"
//                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
//                    verticalAlignment: Text.AlignVCenter
//                    color: Style.whiteFontColor
//                }
//                HBTextField
//                {
//                    id: textLocalRemotePort
//                    width: Math.round(componentWidth * Style.scaleHint)
//                    height: parent.height
//                    maximumLength: 16
//                    validator: RegularExpressionValidator{
//                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
//                    }
//                    text: qsTr("8081")
//                    onlyForNumpad: true
//                    onSignalClickedEvent: {
//                        mainWindow.showPrimaryNumpad(qsTr("远程端口"), " ", 3, 1, 99999, "0.123")
//                    }
//                }
//            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidth + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleLocalPort
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("本地端口") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textLocalPort
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    text: qsTr("8080")
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("本地端口"), " ", 3, 0, 99999, "0.123")
                    }
                }
            }

//            Row{
//                height: Math.round(optionHeight * Style.scaleHint)
//                width: Math.round((textWidth + componentWidth + rowSpacing) * Style.scaleHint)
//                spacing: rowSpacing
//                HBPrimaryButton
//                {
//                    id: buttonLocalConnect
//                    width: Math.round(105 * Style.scaleHint)
//                    height: parent.height
//                    text: qsTr("连接")
//                    onClicked:
//                    {
//                        // controlLimitNumpad.visible = false
//                    }
//                }

//                HBPrimaryButton
//                {
//                    id: buttonLocalDisconnect
//                    width: Math.round(105 * Style.scaleHint)
//                    height: parent.height
//                    text: qsTr("断开")
//                    onClicked:
//                    {
//                        // controlLimitNumpad.visible = false
//                    }
//                }
//            }
        }
    }

    HBGroupBox
    {
        id: cloud
        title: qsTr("云平台")
        anchors.top: local.bottom
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(10 * Style.scaleHint)
        width: parent.width - Math.round(20 * Style.scaleHint)
        height: parent.height / 2 - Math.round(15 * Style.scaleHint)
        backgroundColor: Style.backgroundMiddleColor

        Grid
        {
            anchors.centerIn: parent
            columns: 2
            rows: 3
            rowSpacing: Math.round(20 * Style.scaleHint)
            columnSpacing: Math.round(50 * Style.scaleHint)

//            Row{
//                height: Math.round(optionHeight * Style.scaleHint)
//                width: Math.round((textWidth + componentWidth + rowSpacing) * Style.scaleHint)
//                spacing: rowSpacing
//                Text {
//                    id: titleCloudProtocol
//                    width: Math.round(textWidth * Style.scaleHint)
//                    height: parent.height
//                    text: qsTr("协议") + ":"
//                    font.family: "宋体"
//                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
//                    verticalAlignment: Text.AlignVCenter
//                    color: Style.whiteFontColor
//                }
//                HBComboBox
//                {
//                    id: comboBoxCloudProtocol
//                    width: Math.round(componentWidth * Style.scaleHint)
//                    height: parent.height
//                }
//            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidth + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleCloudRemoteIP
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("远程IP") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textCloudRemoteIP
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    text: qsTr("192.168.111.101")
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("远程IP"), "IPV4", 3, 0, 255, "0.123")
                    }
                }
            }

//            Row{
//                height: Math.round(optionHeight * Style.scaleHint)
//                width: Math.round((textWidth + componentWidth + rowSpacing) * Style.scaleHint)
//                spacing: rowSpacing
//                Text {
//                    id: titleCloudLocalIP
//                    width: Math.round(textWidth * Style.scaleHint)
//                    height: parent.height
//                    text: qsTr("本地IP") + ":"
//                    font.family: "宋体"
//                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
//                    verticalAlignment: Text.AlignVCenter
//                    color: Style.whiteFontColor
//                }
//                HBTextField
//                {
//                    id: textCloudLocalIP
//                    width: Math.round(componentWidth * Style.scaleHint)
//                    height: parent.height
//                    maximumLength: 16
//                    validator: RegularExpressionValidator{
//                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
//                    }
//                    text: qsTr("192.168.111.101")
//                    onlyForNumpad: true
//                    onSignalClickedEvent: {
//                        mainWindow.showPrimaryNumpad(qsTr("本地IP"), "IPV4", 3, 0, 255, "0.123")
//                    }
//                }
//            }

            Row{
                height: Math.round(optionHeight * Style.scaleHint)
                width: Math.round((textWidth + componentWidth + rowSpacing) * Style.scaleHint)
                spacing: rowSpacing
                Text {
                    id: titleCloudRemotePort
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("远程端口") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBTextField
                {
                    id: textCloudRemotePort
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: parent.height
                    maximumLength: 16
                    validator: RegularExpressionValidator{
                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
                    }
                    text: qsTr("8081")
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad(qsTr("远程端口"), " ", 3, 0, 99999, "0.123")
                    }
                }
            }

//            Row{
//                height: Math.round(optionHeight * Style.scaleHint)
//                width: Math.round((textWidth + componentWidth + rowSpacing) * Style.scaleHint)
//                spacing: rowSpacing
//                Text {
//                    id: titleCloudLocalPort
//                    width: Math.round(textWidth * Style.scaleHint)
//                    height: parent.height
//                    text: qsTr("本地端口") + ":"
//                    font.family: "宋体"
//                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
//                    verticalAlignment: Text.AlignVCenter
//                    color: Style.whiteFontColor
//                }
//                HBTextField
//                {
//                    id: textCloudLocalPort
//                    width: Math.round(componentWidth * Style.scaleHint)
//                    height: parent.height
//                    maximumLength: 16
//                    validator: RegularExpressionValidator{
//                        regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
//                    }
//                    text: qsTr("8080")
//                    onlyForNumpad: true
//                    onSignalClickedEvent: {
//                        mainWindow.showPrimaryNumpad(qsTr("本地端口"), " ", 3, 0, 99999, "0.123")
//                    }
//                }
//            }

//            Row{
//                height: Math.round(optionHeight * Style.scaleHint)
//                width: Math.round((textWidth + componentWidth + rowSpacing) * Style.scaleHint)
//                spacing: rowSpacing
//                HBPrimaryButton
//                {
//                    id: buttonCloudConnect
//                    width: Math.round(105 * Style.scaleHint)
//                    height: parent.height
//                    text: qsTr("连接")
//                    onClicked:
//                    {
//                        // controlLimitNumpad.visible = false
//                    }
//                }

//                HBPrimaryButton
//                {
//                    id: buttonCloudDisconnect
//                    width: Math.round(105 * Style.scaleHint)
//                    height: parent.height
//                    text: qsTr("断开")
//                    onClicked:
//                    {
//                        // controlLimitNumpad.visible = false
//                    }
//                }
//            }
        }
    }


}


