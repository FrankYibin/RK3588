/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 2.15
import Style 1.0
import AxisDefine 1.0
import Com.Branson.UIScreenEnum 1.0
Rectangle
{
    signal leftAxisChanged(var index)
    signal rightAxisChanged(var index)
    property color rectleftcolor: "#000000"
    property color rectrightcolor: "#000000"
    property int fontSize: Math.round(Style.style4 * Style.scaleHint)
    property int companyfontSize: Math.round(Style.style4  * Style.scaleHint)
    property string qmltextLeftAxisTitle: qsTr("Left Axis")
    property string qmltextRightAxisTitle: qsTr("Right Axis")
    property string qmltextAutoGraphRefresh: qsTr("Auto Graph Refresh")
    property string qmltextAutoScaleTimeAxis: qsTr("Auto Scale Time Axis")
    property string qmltextSetTimeScale: qsTr("Set Time Scale")
    property var qmlTextArray: [qmltextLeftAxisTitle, qmltextRightAxisTitle, qmltextAutoGraphRefresh, qmltextAutoScaleTimeAxis, qmltextSetTimeScale]
    id: rectright
    border.color: Style.activeFrameBorderColor
    border.width: Style.scaleHint === 1.0 ? 1 : 3
    color: Style.frameButtonBackgroundColor

    function updateLanguage()
    {
        qmlTextArray = languageConfig.getLanguageStringList(UIScreenEnum.ANALYTICS_RESULT_GRAPH_RIGHT_SETTING, qmlTextArray)
        qmltextLeftAxisTitle = qmlTextArray[textEnum.leftAxisTitleIdx]
        qmltextRightAxisTitle = qmlTextArray[textEnum.rightAxisTitleIdx]
        qmltextAutoGraphRefresh = qmlTextArray[textEnum.autoGraphRefreshIdx]
        qmltextAutoScaleTimeAxis = qmlTextArray[textEnum.autoScaleTimeAxisIdx]
        qmltextSetTimeScale = qmlTextArray[textEnum.setTimeScaleIdx]
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted: {
        updateLanguage()
    }

    QtObject {
        id: textEnum
        readonly property int leftAxisTitleIdx:         0
        readonly property int rightAxisTitleIdx:        1
        readonly property int autoGraphRefreshIdx:      2
        readonly property int autoScaleTimeAxisIdx:     3
        readonly property int setTimeScaleIdx:          4
    }

    Rectangle
    {
        id: leftAxisSetting
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: Math.round(100 * Style.scaleHint)
        color: "transparent"
        Column
        {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            spacing: Math.round(5 * Style.scaleHint)
            Text {
                id: leftAxisTitle
                text: qmltextLeftAxisTitle
                font.pixelSize: fontSize
                font.family: Style.regular.name
                color: Style.blackFontColor
            }
            BransonComboBox
            {
                minWidth: Math.round(160 * Style.scaleHint)
                model: AxisDefine.getAxisModel()
                onCurrentTextChanged:
                {
                    leftAxisChanged(currentIndex)
                }
            }
            Row
            {
                spacing: Math.round(10 * Style.scaleHint)
                Rectangle
                {
                    width: Math.round(15 * Style.scaleHint)
                    height: Math.round(15 * Style.scaleHint)
                    radius: width/2
                    color: rectleftcolor
                    anchors.verticalCenter: leftAxisValue.verticalCenter
                }
                Text {
                    id: leftAxisValue
                    text: qsTr("12%")
                    font.pixelSize: fontSize
                    font.family: Style.regular.name
                    color: Style.blueFontColor
                }
            }

        }
    }
    Rectangle
    {
        id: separator1
        anchors.top: leftAxisSetting.bottom
        anchors.left: parent.left
        width: parent.width
        height: Style.scaleHint === 1.0 ? 1 : 3
        color: Style.activeFrameBorderColor
    }

    Rectangle
    {
        id:rightAxisSetting
        anchors.top: separator1.bottom
        width: parent.width
        height: Math.round(100 * Style.scaleHint)
        color: "transparent"
        Column
        {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            spacing: Math.round(5 * Style.scaleHint)
            Text {
                id: rightAxisTitle
                text: qmltextRightAxisTitle
                font.pixelSize: fontSize
                font.family: Style.regular.name
                color: Style.blackFontColor
            }
            BransonComboBox
            {
                minWidth: Math.round(160 * Style.scaleHint)
                model: AxisDefine.getAxisModel()
                onCurrentTextChanged:
                {
                    rightAxisChanged(currentIndex)
                }
            }
            Row
            {
                spacing: Math.round(10 * Style.scaleHint)
                Rectangle
                {
                    width: Math.round(15 * Style.scaleHint)
                    height: Math.round(15 * Style.scaleHint)
                    radius: width/2
                    color: rectrightcolor
                    anchors.verticalCenter: rightAxisValue.verticalCenter
                }
                Text {
                    id: rightAxisValue
                    text: qsTr("12W")
                    font.pixelSize: fontSize
                    font.family: Style.regular.name
                    color: Style.blueFontColor
                }
            }
        }
    }
    Rectangle
    {
        id: separator2
        anchors.top: rightAxisSetting.bottom
        anchors.left: parent.left
        width: parent.width
        height: Style.scaleHint === 1.0 ? 1 : 3
        color: Style.activeFrameBorderColor
    }

    Rectangle
    {
        anchors.top: separator2.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width
        color: "transparent"
        Column
        {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            spacing: Math.round(5 * Style.scaleHint)
            Text {
                id: autoGraphRefeshTitle
                text: qmltextAutoGraphRefresh
                font.pixelSize: fontSize
                font.family: Style.regular.name
                color: Style.blackFontColor
            }
            BransonSwitch
            {
                id: autoGraphRefreshswitch
                anchors.left: autoGraphRefeshTitle.left
                anchors.leftMargin: Math.round(8 * Style.scaleHint)
                checked: true
            }
            Text {
                text: qmltextAutoScaleTimeAxis
                font.pixelSize: fontSize
                font.family: Style.regular.name
                color: Style.blackFontColor
            }
            BransonSwitch
            {
                anchors.left: autoGraphRefreshswitch.left
                checked: true
                onCheckedChanged:
                {
                    if(checked === false)
                    {
                        inputtext.visible=true
                        input.visible=true
                    }
                    else if(checked===true)
                    {
                        inputtext.visible=false
                        input.visible=false
                    }
                }

            }
            Text {
                id:inputtext
                text: qmltextSetTimeScale
                font.pixelSize: fontSize
                font.family: Style.regular.name
                visible: false
                color: Style.blackFontColor
            }
            Row
            {
                id:input
                visible: false
                spacing: Math.round(5 * Style.scaleHint)
                BransonTextField
                {
                    id: myinput
                    text: "1.00"
                    width: Math.round(80 * Style.scaleHint)
                    height: Math.round(30 * Style.scaleHint)
                    onlyForNumpad: true
                    onSignalClickedEvent: {
                        mainWindow.showPrimaryNumpad("Time Scale Setting", "s", 3, 0, 5, "0.123")
                    }
                }
                Text
                {
                    anchors.verticalCenter: myinput.verticalCenter
                    text: qsTr("s")
                    font.pixelSize: fontSize
                    font.family: Style.regular.name
                    color: Style.blueFontColor
                }
            }
        }
    }
}

