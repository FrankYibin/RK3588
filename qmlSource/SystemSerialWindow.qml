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
    readonly property int comboBoxWidth: 150
    readonly property int rowSpacing: 100
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

    Column
    {
        anchors.centerIn: parent
        width: Math.round((textWidth + comboBoxWidth + rowSpacing) * Style.scaleHint)
        height: Math.round((optionHeight * 4 + columnSpacing * 3) * Style.scaleHint)
        spacing: Math.round(columnSpacing * Style.scaleHint)
        Row
        {
            width: parent.width
            height: Math.round(optionHeight * Style.scaleHint)
            spacing: Math.round(rowSpacing * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
            Text {
                id: titlePort
                width: Math.round(textWidth * Style.scaleHint)
                height: parent.height
                text: qsTr("端口") + ":"
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor
            }
            HBComboBox
            {
                id:comboBoxPort
                width: Math.round(comboBoxWidth * Style.scaleHint)
                height: parent.height
            }
        }

        Row
        {
            width: parent.width
            height: Math.round(optionHeight * Style.scaleHint)
            spacing: Math.round(rowSpacing * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
            Text {
                id: titleBaudrate
                width: Math.round(textWidth * Style.scaleHint)
                height: parent.height
                text: qsTr("波特率") + ":"
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor
            }
            HBComboBox
            {
                id: comboBoxBaudrate
                width: Math.round(comboBoxWidth * Style.scaleHint)
                height: parent.height
            }
        }

        Row
        {
            width: parent.width
            height: Math.round(optionHeight * Style.scaleHint)
            spacing: Math.round(rowSpacing * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
            Text {
                id: titleDataBits
                width: Math.round(textWidth * Style.scaleHint)
                height: parent.height
                text: qsTr("数据位") + ":"
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor
            }
            HBComboBox
            {
                id: comboBoxDataBits
                width: Math.round(comboBoxWidth * Style.scaleHint)
                height: parent.height
            }
        }

        Row
        {
            width: parent.width
            height: Math.round(optionHeight * Style.scaleHint)
            spacing: Math.round(rowSpacing * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
            Text {
                id: titleStandard
                width: Math.round(textWidth * Style.scaleHint)
                height: parent.height
                text: qsTr("标准") + ":"
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor
            }
            HBComboBox
            {
                id: comboBoxStandard
                width: Math.round(comboBoxWidth * Style.scaleHint)
                height: parent.height
            }
        }
    }

    HBPrimaryButton
    {
        id: buttonConnect
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(20 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(20 * Style.scaleHint)
        width: Math.round(125 * Style.scaleHint)
        height: Math.round(40 * Style.scaleHint)
        text: qsTr("连接")
        onClicked:
        {
            console.debug("Serial Connecting")
        }
    }

}


