import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_HISTORY_DATA
    readonly property int buttonWidth: 100
    readonly property int componentHeight: 30
    Component.onCompleted:
    {
        languageModel.resetModel()
    }

    ListModel
    {
        id: languageModel
        function resetModel()
        {
            languageModel.clear()
            languageModel.append({"itemIndex": 0, "itemName": qsTr("中文")})
            languageModel.append({"itemIndex": 1, "itemName": qsTr("English")})
        }
    }

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
        id: timeSetting
        title: qsTr("时间设置")
        anchors.top: parent.top
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
        width: parent.width - Math.round(10 * Style.scaleHint)
        height: parent.height / 4 * 3 - Math.round(5 * Style.scaleHint)
        backgroundColor: Style.backgroundLightColor

        HBDateTimeSetting
        {
            id: dateTimeSetting
            anchors.left: parent.left
            anchors.leftMargin: Math.round(50 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            visible: true
        }
        HBPrimaryButton
        {
            id: buttonExport
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(10 * Style.scaleHint)
            anchors.right: parent.right
            anchors.rightMargin: Math.round(10 * Style.scaleHint)
            width: Math.round(buttonWidth * Style.scaleHint)
            height: Math.round(componentHeight * Style.scaleHint)
            text: qsTr("确认")
            onClicked:
            {
                var strDateTime = dateTimeSetting.getDateTimeString()
                console.debug("Time Setting： ", strDateTime)
                DateTime.setSystemDateTime(strDateTime)
            }
        }

    }

    HBGroupBox
    {
        id: languageSetting
        title: qsTr("语言设置")
        anchors.top: timeSetting.bottom
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(5 * Style.scaleHint)
        width: parent.width - Math.round(10 * Style.scaleHint)
        backgroundColor: Style.backgroundLightColor

        Row {
            anchors.centerIn: parent
            spacing: Math.round(36 * Style.scaleHint)
            ExclusiveGroup {id: languageOptionGroup}
            Repeater {
                model: languageModel
                delegate: BransonRadioButton
                {
                    id: customerRadioButtionDelegate
                    height: Math.round(componentHeight * Style.scaleHint)
                    width: Math.round(buttonWidth * Style.scaleHint)
                    labelText:  model.itemName
                    exclusiveGroup: languageOptionGroup
                    checked: (index == 0) ? true : false
                    onClicked:
                    {
                        console.debug("current Language: ", model.itemIndex)
                    }
                }
            }
        }
    }


}


