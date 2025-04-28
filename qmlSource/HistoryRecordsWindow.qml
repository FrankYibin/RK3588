import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    readonly property int textWidth: 70
    readonly property int comboBoxWidth: 150
    readonly property int editTextWidth: 100
    readonly property int buttonWidth: 100
    readonly property int rowSpacing: 10
    readonly property int componentHeight: 30
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
        id: info
        title: qsTr("作业信息")
        anchors.top: parent.top
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
        width: parent.width - Math.round(10 * Style.scaleHint)
        height: parent.height / 3 - Math.round(40 * Style.scaleHint)
        backgroundColor: Style.backgroundLightColor
        Item {
            id: argumentLayout
            width: parent.width
            height: parent.height / 2
            anchors.left: parent.left
            anchors.top: parent.top
            Row
            {
                height: Math.round(componentHeight * Style.scaleHint)
                width: parent.width
                anchors.left: parent.left
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: Math.round(20 * Style.scaleHint)
                spacing: Math.round(30 * Style.scaleHint)

                Row{
                    spacing: Math.round(rowSpacing * Style.scaleHint)
                    height: parent.height
                    width: Math.round((textWidth + rowSpacing + editTextWidth) * Style.scaleHint)
                    Text {
                        id: titleFirstNumber
                        width: Math.round(textWidth * Style.scaleHint)
                        height: parent.height
                        text: qsTr("队别") + ":"
                        font.family: "宋体"
                        font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                        verticalAlignment: Text.AlignVCenter
                        color: Style.whiteFontColor
                    }
                    HBLineEdit {
                        id: textFirstNumber
                        width: Math.round(editTextWidth * Style.scaleHint)
                        height: parent.height
                        text: "01"
                    }
                }

                Row{
                    spacing: Math.round(rowSpacing * Style.scaleHint)
                    height: parent.height
                    width: Math.round((textWidth + rowSpacing + editTextWidth) * Style.scaleHint)
                    Text {
                        id: titleAreaNumber
                        width: Math.round(textWidth * Style.scaleHint)
                        height: parent.height
                        text: qsTr("区域") + ":"
                        font.family: "宋体"
                        font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                        verticalAlignment: Text.AlignVCenter
                        color: Style.whiteFontColor
                    }
                    HBLineEdit {
                        id: textAreaNumber
                        width: Math.round(editTextWidth * Style.scaleHint)
                        height: parent.height
                        text: "01"
                    }
                }

                Row{
                    spacing: Math.round(rowSpacing * Style.scaleHint)
                    height: parent.height
                    width: Math.round((textWidth + rowSpacing + editTextWidth) * Style.scaleHint)
                    Text {
                        id: titleWellNumber
                        width: Math.round(textWidth * Style.scaleHint)
                        height: parent.height
                        text: qsTr("井名") + ":"
                        font.family: "宋体"
                        font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                        verticalAlignment: Text.AlignVCenter
                        color: Style.whiteFontColor
                    }
                    HBLineEdit {
                        id: textWellNumber
                        width: Math.round(editTextWidth * Style.scaleHint)
                        height: parent.height
                        text: "01"
                    }
                }
            }

        }

        Item{
            id: timeScopeLayout
            width: parent.width
            height: parent.height / 2
            anchors.top: argumentLayout.bottom
            anchors.left: parent.left
            Row{
                width: parent.width
                height: Math.round(componentHeight * Style.scaleHint)
                spacing: Math.round(20 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                Row{
                    spacing: Math.round(rowSpacing * Style.scaleHint)
                    height: parent.height
                    width: Math.round((textWidth + rowSpacing + comboBoxWidth) * Style.scaleHint)
                    Text {
                        id: titleStartTimeStamp
                        width: Math.round(textWidth * Style.scaleHint)
                        height: parent.height
                        text: qsTr("开始时间") + ":"
                        font.family: "宋体"
                        font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                        verticalAlignment: Text.AlignVCenter
                        color: Style.whiteFontColor
                    }
                    HBComboBox
                    {
                        id:comboBoxStartTimeStamp
                        width: Math.round(comboBoxWidth * Style.scaleHint)
                        height: parent.height
                    }
                }

                Row{
                    spacing: Math.round(rowSpacing * Style.scaleHint)
                    height: parent.height
                    width: Math.round((textWidth + rowSpacing + comboBoxWidth) * Style.scaleHint)
                    Text {
                        id: titleFinishTimeStamp
                        width: Math.round(textWidth * Style.scaleHint)
                        height: parent.height
                        text: qsTr("结束时间") + ":"
                        font.family: "宋体"
                        font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                        verticalAlignment: Text.AlignVCenter
                        color: Style.whiteFontColor
                    }
                    HBComboBox
                    {
                        id:comboBoxFinishTimeStamp
                        width: Math.round(comboBoxWidth * Style.scaleHint)
                        height: parent.height
                    }
                }

                HBPrimaryButton
                {
                    id: buttonInquire
                    width: Math.round(buttonWidth * Style.scaleHint)
                    height: Math.round(componentHeight * Style.scaleHint)
                    text: qsTr("查询")
                    onClicked:
                    {
                        // controlLimitNumpad.visible = false
                    }
                }
            }
        }
    }
}


