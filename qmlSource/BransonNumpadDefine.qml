﻿/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/
pragma Singleton //we indicate that this QML Type is a singleton
import QtQuick 2.12
import Com.Branson.UIScreenEnum 1.0
Item {
    id: numpadDefine
    readonly property int stepTimeIdx:         0
    readonly property int stepEnergyIdx:       1
    readonly property int stepPeakPowerIdx:    2
    readonly property int stepAbsoluteIdx:     3
    readonly property int stepCollapseIdx:     4
    readonly property int stepExtSignalIdx:    5

    property string qmltextCancel:          qsTr("CANCEL")
    property string qmltextDone:            qsTr("DONE")
    property string qmltextMinimun:         qsTr("Min")
    property string qmltextMaximum:         qsTr("Max")
    property string qmltextStepping:        qsTr("STEPPING")
    property string qmltextStep:            qsTr("Step")
    property string qmltextStepValue:       qsTr("Step Value")
    property string qmltextStepTime:        qsTr("Step@Time")
    property string qmltextStepEnergy:      qsTr("Step@Energy")
    property string qmltextStepPeakPower:   qsTr("Step@Pk Power")
    property string qmltextStepAbsolute:    qsTr("Step@Absolute")
    property string qmltextStepCollapse:    qsTr("Step@Collapse")
    property string qmltextStepExtSignal:   qsTr("Step@Ext. Signal")
    property string qmltextInvalidValueMsg: qsTr("Invalid value is entered, Reverted to old value")
    property var stepTypeModel: [qmltextStepTime, qmltextStepEnergy, qmltextStepPeakPower,
        qmltextStepAbsolute, qmltextStepCollapse, qmltextStepExtSignal]

    property var qmlTextArray: [qmltextCancel, qmltextDone, qmltextMinimun,
        qmltextMaximum, qmltextStepping, qmltextStep, qmltextStepValue,
        qmltextStepTime, qmltextStepEnergy, qmltextStepPeakPower, qmltextStepAbsolute,
        qmltextStepCollapse, qmltextStepExtSignal, qmltextInvalidValueMsg]

    function updateLanguage()
    {
        qmlTextArray = languageConfig.getLanguageStringList(UIScreenEnum.NUMPAD, qmlTextArray)
        qmltextCancel =             qmlTextArray[textEnum.cancelIdx]
        qmltextDone =               qmlTextArray[textEnum.doneIdx]
        qmltextMinimun =            qmlTextArray[textEnum.minimumIdx]
        qmltextMaximum =            qmlTextArray[textEnum.maximumIdx]
        qmltextStepping =           qmlTextArray[textEnum.steppingIdx]
        qmltextStep =               qmlTextArray[textEnum.stepIdx]
        qmltextStepValue =          qmlTextArray[textEnum.stepValueIdx]
        qmltextStepTime =           qmlTextArray[textEnum.stepTimeIdx]
        qmltextStepEnergy =         qmlTextArray[textEnum.stepEnergyIdx]
        qmltextStepPeakPower =      qmlTextArray[textEnum.stepPeakPowerIdx]
        qmltextStepAbsolute =       qmlTextArray[textEnum.stepAbsoluteIdx]
        qmltextStepCollapse =       qmlTextArray[textEnum.stepCollapseIdx]
        qmltextStepExtSignal =      qmlTextArray[textEnum.stepExtSignalIdx]
        qmltextInvalidValueMsg =    qmlTextArray[textEnum.invalidValueMsgIdx]
    }

    Component.onCompleted:
    {
        updateLanguage()
    }

    enum EnumKeyboard{
        Delete,
        Clear,
        Login,
        FaceLogin,
        PasswordLogin
    }

    QtObject {
        id: textEnum
        readonly property int cancelIdx:            0
        readonly property int doneIdx:              1
        readonly property int minimumIdx:           2
        readonly property int maximumIdx:           3
        readonly property int steppingIdx:          4
        readonly property int stepIdx:              5
        readonly property int stepValueIdx:         6
        readonly property int stepTimeIdx:          7
        readonly property int stepEnergyIdx:        8
        readonly property int stepPeakPowerIdx:     9
        readonly property int stepAbsoluteIdx:      10
        readonly property int stepCollapseIdx:      11
        readonly property int stepExtSignalIdx:     12
        readonly property int invalidValueMsgIdx:   13

    }


    function handleWithDigitalKeyInput(data, text_input, suffix)
    {
        Qt.inputMethod.hide()
        if(data === BransonNumpadDefine.EnumKeyboard.Clear)
            text_input.remove(0, text_input.cursorPosition)
        else if(data === BransonNumpadDefine.EnumKeyboard.Delete)
        {
            if(text_input.isSelectedAll === true)
                text_input.remove(0, text_input.cursorPosition)
            else
                text_input.remove(text_input.cursorPosition - 1, text_input.cursorPosition)
        }
        else
        {
            var strInputText = text_input.text
            if(text_input.isSelectedAll === true)
                strInputText = data
            else
                strInputText += data
            if(BransonNumpadDefine.isValidData(strInputText, suffix) === true)
            {
                text_input.text = strInputText
            }
        }
        text_input.isSelectedAll = false
    }

    function decimalsNumber(decimals_num, text_input)
    {
        var contrast = text_input.text
        /*Number of decimal points*/
        var num = contrast.split('.').length - 1
        if(num === 1)
            var position = contrast.indexOf(".");

        if(decimals_num === 0)
        {
            text_input.maximumLength = 8
            if(num >= 1)
            {
                /*Limit when the number of decimal points is greater than 1*/
                text_input.remove(text_input.cursorPosition - 1, text_input.cursorPosition)
            }
        }
        else
        {
            /*Limit total length*/
            if(position + 1 + decimals_num <= 8)
            {
                /*The number of digits before the decimal point
                  plus the number of digits after the decimal point is
                  the total length of the restriction*/
                text_input.maximumLength = position + 1 + decimals_num
            }
            else
                text_input.maximumLength = 8
        }
        return text_input.text
    }

    function numberToString(decimals_num, realValue)
    {
        var strValue = realValue.toFixed(decimals_num)
        return strValue
    }

    function isValidData(strInputText, strUnit)
    {
        var validator = /^\d{0,6}?$/
        var bResult = false
        if(strUnit.toUpperCase() === "S")
        {
            validator = /^\d{0,6}(\.\d{0,3})?$/
        }
        else if(strUnit.toUpperCase() === "%")
        {
            validator = /^\d{0,3}?$/
        }
        else if(strUnit.toUpperCase() === "W")
        {
            validator = /^\d{0,4}?$/
        }
        else if(strUnit.toUpperCase() === "MM" || strUnit.toUpperCase() === "MM/S2" || strUnit.toUpperCase() === "MM/S")
        {
            validator = /^\d{0,3}(\.\d{0,2})?$/
        }
        else if(strUnit.toUpperCase() === "IN" || strUnit.toUpperCase() === "IN/S2" || strUnit.toUpperCase() === "IN/S")
        {
            validator = /^\d{0,2}(\.\d{0,4})?$/
        }
        else if(strUnit.toUpperCase() === "IPV4" || strUnit.toUpperCase() === "IPV6")
        {
            return true
        }
        else
        {
            validator = /^\d{0,7}(\.\d{0,2})?$/
        }

        if (validator.test(strInputText))
        {
            bResult = true
        }
        else
        {
            bResult = false
        }
        return bResult
    }

}

