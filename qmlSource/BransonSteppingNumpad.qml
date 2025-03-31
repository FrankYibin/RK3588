/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import QtQuick.Controls 1.4
import QtQml.Models 2.15
import Style 1.0
Item {
    id: steppingNumpad
    property int minWidth: Math.round(400 * Style.scaleHint)
    property int maxHeight: Math.round(411 * Style.scaleHint)
    property int headermaxHeight: Math.round(30 * Style.scaleHint)
    property string headerColor: Style.headerBackgroundColor
    property string headertext: "WELD AMPLITUDE"
    property string headertextColor: "#FFFFFF"
    property int fontSize: Math.round(Style.style2 * Style.scaleHint)
    property int count: 1
    property var obj: []
    property string suffix:  "%"
    property string stepSuffix: "%"
    property int decimals: 2
    property int stepDecimals: 2
    property int currentStepIndex: 0
    property real minimumValue: 10
    property real maximumValue: 100
    property alias value: input.text
    readonly property int maxSteps: 4
    property int focusedItem: focusedItemEnum.mainFocusedIdx

    /*Remove components dynamically*/
    function removeDynamicSteps()
    {
        /*Dynamically delete components*/
        if(count - 1 > 0)
        {
            obj[count - 1].destroy()
            if(count === stepValueModel.count)
            {
                stepValueModel.remove(count - 1)
            }
            count--
            obj[count - 1].checked = true
            onSignalClickAction(count - 1)
        }
        else
            stepValueModel.resetModel()
    }

    /*Add components dynamically*/
    function createDynamicSteps()
    {
        var component = Qt.createComponent("BransonDynamicStepButton.qml")
        if (component.status === Component.Ready)
        {
            if(count > maxSteps)
                return
            obj[count] = component.createObject(stepsColumn, {
                                                    "exclusiveGroup": stepButtonsGroup,
                                                    "width": Math.round(40 * Style.scaleHint),
                                                    "height": Math.round(40 * Style.scaleHint),
                                                    "stepIndex": count })
            obj[count].signalClickAction.connect(onSignalClickAction)
            stepValueModel.appendNewDefaultStep()
            onSignalClickAction(count)
            count++
        }

    }

    function slotDigitalKeyPressed(data)
    {
        if(focusedItem === focusedItemEnum.mainFocusedIdx)
            BransonNumpadDefine.handleWithDigitalKeyInput(data, input, suffix)
        else if(focusedItem === focusedItemEnum.ampStepFocusedIdx)
            BransonNumpadDefine.handleWithDigitalKeyInput(data, stepValueInput, stepSuffix)
        else
            BransonNumpadDefine.handleWithDigitalKeyInput(data, input, suffix)
    }

    function onSignalClickAction(index)
    {
        currentStepIndex = index - 1
        stepSuffix = stepValueModel.get(currentStepIndex).StepUnit
        stepDecimals = stepValueModel.get(currentStepIndex).Decimals
        stepValueInput.text = stepValueModel.get(currentStepIndex).StepValue
        input.text = stepValueModel.get(currentStepIndex).AmplitudeValue
        stepTitle.currentIndex = stepValueModel.get(currentStepIndex).TitleIndex

    }

    ListModel {
        id: stepValueModel
        function resetModel()
        {
            stepValueModel.clear()
        }

        function appendNewDefaultStep()
        {
            stepValueModel.append({"TitleIndex": BransonNumpadDefine.stepTimeIdx,
                                   "StepValue": "0.001",
                                   "StepUnit": "S",
                                   "Decimals": 3,
                                   "AmplitudeValue": steppingNumpad.value})
        }

        function updateStepValueModel()
        {
            count = 1
            for(var i = 0; i < stepValueModel.count; i++)
            {
                if(count > maxSteps)
                    return
                obj[count] = component.createObject(stepsColumn, {
                                                        "exclusiveGroup": stepButtonsGroup,
                                                        "width": Math.round(40 * Style.scaleHint),
                                                        "height": Math.round(40 * Style.scaleHint),
                                                        "stepIndex": count })
                count++
            }
        }

    }

    Component.onCompleted: {
        bransonprimary.signalButtonNum.connect(slotDigitalKeyPressed)
        bransonprimary.signalButtonFunc.connect(slotDigitalKeyPressed)
        stepValueModel.resetModel()
    }

    ExclusiveGroup {
        id: stepButtonsGroup
    }

    QtObject {
        id: focusedItemEnum
        readonly property int mainFocusedIdx:       0
        readonly property int ampStepFocusedIdx:    1
        readonly property int forceStepFocusedIdx:  2
    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: Style.dialogBackgroundColor
        opacity: 0.75
        MouseArea {
            anchors.fill: parent
        }
    }
    Rectangle
    {
        id:root
        width: minWidth
        height: maxHeight
        anchors.centerIn: parent
        color: "#FFFFFF"
        Rectangle
        {
            id: numpadHeader
            width: parent.width
            implicitHeight: headermaxHeight
            color: headerColor
            Text {
                id: headername
                anchors.left: numpadHeader.left
                anchors.top: numpadHeader.top
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                text: headertext
                color: headertextColor
                font{
                    family: Style.regular.name
                    pixelSize: fontSize
                }
            }
            Rectangle
            {
                id: rectimage
                implicitWidth: Math.round(24 * Style.scaleHint)
                implicitHeight: Math.round(24 * Style.scaleHint)
                anchors.right: numpadHeader.right
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                anchors.top: numpadHeader.top
                anchors.topMargin:Math.round(5 * Style.scaleHint)
                color: "transparent"
                Image {
                    id: headerClose
                    anchors.fill: parent
                    source: "qrc:/images/crossMark.svg"
                    sourceSize.width: headerClose.width
                    sourceSize.height: headerClose.height
                    smooth: true
                }
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        steppingNumpad.visible = false
                    }
                }
            }
        }

        Rectangle
        {
            id: mykeyboard
            anchors.top: numpadHeader.bottom
            anchors.left: numpadHeader.left
            width: Math.round(200 * Style.scaleHint)
            anchors.bottom: root.bottom
            Rectangle
            {
                id: rect
                width: parent.width
                anchors.top: switchbtn.top
                anchors.left: parent.left
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.topMargin: Math.round(50 * Style.scaleHint)
                anchors.bottom: parent.bottom
                visible: false
                Rectangle
                {
                    id:leftbtn
                    width: Math.round(40 * Style.scaleHint)
                    height: parent.height
                    Column {
                        id: stepsColumn
                        anchors.top: parent.top
                        anchors.topMargin: Math.round(40 * Style.scaleHint)
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        width: parent.width
                    }
                    Rectangle {
                        id: deleteObjectBtn
                        anchors.top: parent.top
                        anchors.left: parent.left
                        width: Math.round(40 * Style.scaleHint)
                        height: Math.round(40 * Style.scaleHint)
                        color: BransonStyle.backgroundColor
                        border.width: BransonStyle.scaleHint === 1.0 ? 1 : 2
                        border.color: BransonStyle.activeFrameBorderColor
                        Text {
                            id: dec
                            anchors.centerIn: parent
                            text: "-"
                            font.bold: true
                            font.family: BransonStyle.regular.name
                            font.pixelSize: BransonStyle.style4
                            color: "#000000"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                removeDynamicSteps()
                            }
                        }
                    }
                    Rectangle {
                        id: createObjectBtn
                        anchors.left: parent.left
                        width: Math.round(40 * Style.scaleHint)
                        height: Math.round(40 * Style.scaleHint)
                        color: BransonStyle.backgroundColor
                        border.width: 1
                        border.color: BransonStyle.activeFrameBorderColor
                        y: count === 1 ? count * Math.round(40 * Style.scaleHint + 2) : count * Math.round(40 * Style.scaleHint)
                        Text {
                            id: inc
                            anchors.centerIn: parent
                            text: "+"
                            font.bold: true
                            font.family: BransonStyle.regular.name
                            font.pixelSize: BransonStyle.style4
                            color: "#000000"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if(createObjectBtn.y + 40 <= leftbtn.height)
                                {
                                    createDynamicSteps()
                                }
                            }
                        }
                    }
                }

                Rectangle
                {
                    id: input_left
                    width:  Math.round(200 * Style.scaleHint)
                    height:   Math.round(95 * Style.scaleHint)
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(50 * Style.scaleHint)
                    anchors.top: parent.top
                    Column
                    {
                        id:columnid
                        anchors.fill: input_left
                        spacing: Math.round(5 * Style.scaleHint)
                        Text {
                            id: stepname
                            text: BransonNumpadDefine.qmltextStep + "@" //qsTr("Step@")
                            font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
                            font.family: Style.regular.name
                            color: BransonStyle.blueFontColor
                        }
                        BransonComboBox
                        {
                            id: stepTitle
                            width: Math.round(170 * Style.scaleHint)
                            model: BransonNumpadDefine.stepTypeModel
                            enabled: (currentStepIndex > 0) ? true : false
                            comboBoxTextColor: BransonStyle.blueFontColor
                            onActivated: {
                                if(currentStepIndex < 1)
                                    return
                                if(currentStepIndex < stepValueModel.count)
                                {
                                    stepValueModel.setProperty(currentStepIndex, "TitleIndex", currentIndex)
                                    switch(currentIndex)
                                    {
                                    case BransonNumpadDefine.stepTimeIdx:
                                        stepSuffix = "S"
                                        stepDecimals = 3
                                        break;
                                    case BransonNumpadDefine.stepEnergyIdx:
                                        stepSuffix = "J"
                                        stepDecimals = 0
                                        break;
                                    case BransonNumpadDefine.stepPeakPowerIdx:
                                        stepSuffix = "W"
                                        stepDecimals = 0
                                        break;
                                    case BransonNumpadDefine.stepAbsoluteIdx:
                                        stepSuffix = "mm"
                                        stepDecimals = 2
                                        break;
                                    case BransonNumpadDefine.stepCollapseIdx:
                                        stepSuffix = "mm"
                                        stepDecimals = 2
                                        break;
                                    case BransonNumpadDefine.stepExtSignalIdx:
                                        stepSuffix = ""
                                        stepDecimals = 0
                                        break;
                                    default:
                                        stepSuffix = "S"
                                        stepDecimals = 0
                                        currentIndex = 0
                                        break;
                                    }
                                    stepValueModel.setProperty(currentStepIndex, "StepUnit", stepSuffix)
                                    stepValueModel.setProperty(currentStepIndex, "Decimals", stepDecimals)
                                }
                            }
                        }
                        Text {
                            id: valuename
                            text: BransonNumpadDefine.qmltextStepValue //qsTr("Step Value")
                            font.pixelSize: Math.round(Style.style2  * Style.scaleHint)
                            font.family: Style.regular.name
                            color: BransonStyle.blueFontColor
                        }
                        BransonTextField {
                            id: stepValueInput
                            onlyForNumpad: true
                            width: Math.round(170 * Style.scaleHint)
                            height: Math.round(40 * Style.scaleHint)
                            enabled: (currentStepIndex > 0) ? true : false
                            onTextChanged:
                            {
                                BransonNumpadDefine.decimalsNumber(stepDecimals, stepValueInput)
                                if(currentStepIndex < 1)
                                    return
                                if(currentStepIndex < stepValueModel.count)
                                {
                                    stepValueModel.setProperty(currentStepIndex, "StepValue", stepValueInput.text)
                                }
                            }
                            onSignalClickedEvent: {
                                focusedItem = focusedItemEnum.ampStepFocusedIdx
                            }
                        }
                    }
                }
            }
            Text {
                id: switchname
                text: BransonNumpadDefine.qmltextStepping  //qsTr("STEPPING")
                color: BransonStyle.blackFontColor
                font.pixelSize: Math.round(Style.style2  * Style.scaleHint)
                font.family: Style.regular.name
                anchors.top: parent.top
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(140 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter

            }
            BransonSwitch
            {
                id:switchbtn
                anchors.bottom: switchname.bottom
                anchors.left: switchname.right
                anchors.leftMargin:  Math.round(15 * Style.scaleHint)
                onCheckedChanged:
                {
                    if(checked === false)
                    {
                        /*Hide the content on the left and move the coordinates to the left*/
                        rect.visible = false
                        root.width = Math.round(400 * Style.scaleHint)
                        mainkeyboard.anchors.leftMargin = Math.round(58 * Style.scaleHint)
                        switchname.anchors.left = parent.left
                        switchname.anchors.leftMargin = Math.round(140 * Style.scaleHint)
                        btnCancel.anchors.leftMargin = Math.round(60 * Style.scaleHint)
                        btnDone.anchors.leftMargin = Math.round(20 * Style.scaleHint)

                    }
                    else
                    {
                        /*Display the content on the left and move the coordinates to the right*/
                        rect.visible = true
                        root.width = Math.round(600 * Style.scaleHint)
                        mainkeyboard.anchors.leftMargin = Math.round(380 * Style.scaleHint)
                        switchname.anchors.left = parent.left
                        switchname.anchors.leftMargin = Math.round(20 * Style.scaleHint)
                        btnCancel.anchors.leftMargin = Math.round(270 * Style.scaleHint)
                        btnDone.anchors.leftMargin = Math.round(20 * Style.scaleHint)
                    }
                }
            }

            Rectangle
            {
                id: mainkeyboard
                anchors.top: switchbtn.bottom
                anchors.topMargin: Math.round(-15 * Style.scaleHint)
                anchors.left: switchname.left
                anchors.leftMargin: Math.round(58 * Style.scaleHint)
                BransonTextField
                {
                    id: input
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(22 * Style.scaleHint)
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: Math.round(260 * Style.scaleHint)
                    height: Math.round(30 * Style.scaleHint)
                    onlyForNumpad: true
                    focus: true
                    onTextChanged:
                    {
                        BransonNumpadDefine.decimalsNumber(decimals, input)
                        if(currentStepIndex < 1)
                            return
                        if(currentStepIndex < stepValueModel.count)
                        {
                            stepValueModel.setProperty(currentStepIndex, "AmplitudeValue", input.text)
                        }
                    }
                    onSignalClickedEvent: {
                        focusedItem = focusedItemEnum.mainFocusedIdx
                    }
                }

                Text {
                    id: txtUnit
                    text: suffix
                    anchors.right: input.right
                    anchors.rightMargin: Math.round(5 * Style.scaleHint)
                    anchors.top: input.top
                    anchors.topMargin: Math.round(4 * Style.scaleHint)
                    color: BransonStyle.blackFontColor
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: Style.regular.name
                }
                Label {
                    id: labelMin
                    text: BransonNumpadDefine.qmltextMinimun + ":"
                    anchors.top: input.bottom
                    anchors.left: input.left
                    anchors.topMargin: Math.round(2 * Style.scaleHint)
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: BransonStyle.blueFontColor
                }
                Text {
                    id: txtMin
                    text: minimumValue
                    anchors.top: labelMin.top
                    anchors.left: labelMin.right
                    anchors.leftMargin:  Math.round(5 * Style.scaleHint)
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: BransonStyle.blueFontColor

                }
                Label {
                    id: labelMax
                    text: BransonNumpadDefine.qmltextMaximum + ":" //qsTr("Max:")
                    anchors.top: txtMax.top
                    anchors.right: txtMax.left
                    anchors.rightMargin: Math.round(5 * Style.scaleHint)
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: BransonStyle.blueFontColor
                }
                Text {
                    id: txtMax
                    text: maximumValue
                    anchors.top: input.bottom
                    anchors.topMargin: Math.round(2 * Style.scaleHint)
                    anchors.right: input.right
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: BransonStyle.blueFontColor

                }
                BransonNumKeyboard
                {
                    id:bransonprimary
                    anchors.top:input.bottom
                    anchors.left: input.left
                    anchors.leftMargin: Math.round(132 * Style.scaleHint)
                }
            }
        }

        BransonPrimaryButton
        {
            id: btnCancel
            implicitWidth: Math.round(124 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style2  * Style.scaleHint)
            anchors.bottom: root.bottom
            anchors.bottomMargin: Math.round(15 * Style.scaleHint)
            anchors.left: root.left
            anchors.leftMargin: Math.round(60 * Style.scaleHint)
            text: BransonNumpadDefine.qmltextCancel
            font.family: Style.regular.name
            buttonColor: BransonStyle.backgroundColor
            textColor: "#000000"
            onClicked:
            {
                steppingNumpad.visible = false
            }
        }
        BransonPrimaryButton
        {
            id: btnDone
            implicitWidth: Math.round(124 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style2  * Style.scaleHint)
            anchors.top: btnCancel.top
            anchors.left: btnCancel.right
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            text: BransonNumpadDefine.qmltextDone
            font.family: Style.regular.name
            onClicked:
            {
                //var validatedValue = recipe.ValidateParamRange(paramIndex, input.text)
                // recipe.updateParam(paramIndex, validateValue)
                steppingNumpad.visible = false
            }
        }

    }

}
