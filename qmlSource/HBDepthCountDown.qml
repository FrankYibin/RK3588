import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    id: depthCountDownPopUp
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

    function valueToAngel(value)
    {
        if(value < 0)
            value = 0
        if(value > 1200)
            value = 1200
        return ((240/ 1200) * value + 60)
    }

    Rectangle
    {
        id: background
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: parent.height
        color: "#3d7ab3"
        opacity: 1   // 0~1，0为全透明，1为不透明
    }

    HBPandel
    {
        id: pandelDepth
        anchors.left: parent.left
        anchors.leftMargin: Math.round(20 * Style.scaleHint)
        anchors.verticalCenter: parent.verticalCenter
        width: 300
        height: 300
        angle: valueToAngel(Number(textCurrentDepth.text))
    }

    Text {
        id: titleCurrentDepth
        width: Math.round(textWidthColumn1 * Style.scaleHint)
        height: Math.round(optionHeight * Style.scaleHint)
        text: qsTr("深度倒计") + ":"
        font.family: "宋体"
        font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
        verticalAlignment: Text.AlignVCenter
        color: Style.whiteFontColor
        anchors.horizontalCenter: textCurrentDepth.horizontalCenter
        anchors.bottom: textCurrentDepth.top
        anchors.bottomMargin: Math.round(10 * Style.scaleHint)
    }

    HBTextField
    {
        id: textCurrentDepth
        width: Math.round(140 * Style.scaleHint)
        height: Math.round(80 * Style.scaleHint)
        anchors.verticalCenter: pandelDepth.verticalCenter
        anchors.left: pandelDepth.right
        anchors.leftMargin: Math.round(20 * Style.scaleHint)
        fontSize: Math.round(Style.style8 * Style.scaleHint)
        maximumLength: 16
        validator: RegularExpressionValidator{
            regularExpression: /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/
        }
        // text: "8081"
        text:DepthMeter.CurrentDepth
        onlyForNumpad: true
        onSignalClickedEvent: {
            mainWindow.showPrimaryNumpad(qsTr("深度倒计"), " ", 3, 0, 99999, "0.123")
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
        anchors.verticalCenter: textCurrentDepth.verticalCenter
        anchors.left: textCurrentDepth.right
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
    }

    // 拖动区域
    MouseArea {
        id: dragArea
        anchors.fill: parent
        drag.target: depthCountDownPopUp
        drag.axis: Drag.XAndYAxis
    }

    HBPrimaryButton
    {
        id: btnClose
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(10 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(10 * Style.scaleHint)
        width: Math.round(100 * Style.scaleHint)
        height: Math.round(30 * Style.scaleHint)
        text: qsTr("返回")
        fontSize: Math.round(Style.style5 * Style.scaleHint)
        onClicked:
        {
           depthCountDownPopUp.visible = false
        }
    }
}


