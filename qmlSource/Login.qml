/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 Login Screen

 **********************************************************************************************************/
import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.15
import QtQuick.VirtualKeyboard.Settings 2.15
import Style 1.0
import QtQuick.Layouts 1.12
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.LoginIndexEnum 1.0
Rectangle{
    id:loginWindow
    property int fontPixelSize: Math.round(Style.style6 * Style.scaleHint)
    property alias textFildPassword: textFildPassword
    property alias imageLoginUiLock: imageLoginUiLock
    property alias rectangle: rectangle
    property alias textLoginUiTooltip: textLoginUiTooltip
    property alias bransonLoginKeyboard: bransonLoginKeyboard
    property alias backgroundLoginUi: backgroundLoginUi
    property string qmltextEnterPasscode:       qsTr("Enter passcode")
    property string qmltextLogin:               qsTr("Login")
    property string qmltextMultipleLoginFailed: qsTr("Too many failed login attempts. System will be locked for 15 minutes.")
    property string qmltextLoginFail:           qsTr("Invalid Passcode. Please re-enter and try again.")
    property string qmltextLoginSuccess:        qsTr("Login Successful")
    property string qmltextPasscodeEmpty:       qsTr("Please enter a passcode")
    property string qmlLoginErrorMessage:       qmltextLoginSuccess
    property var    qmlTextArray: [qmltextEnterPasscode, qmltextLogin,
        qmltextMultipleLoginFailed, qmltextLoginFail, qmltextLoginSuccess, qmltextPasscodeEmpty]
    property var loginErrorCode: 0
    /*Background picture of login interface*/
    visible: true

    function updateLanguage()
    {
        bransonLoginKeyboard.buttonLoginTextLogin = qmltextLogin
        qmlTextArray = languageConfig.getLanguageStringList(UIScreenEnum.LOGIN, qmlTextArray)
        qmltextEnterPasscode = qmlTextArray[textEnum.enterPasscodeIdx]
        qmltextLogin = qmlTextArray[textEnum.loginIdx]
        qmltextMultipleLoginFailed = qmlTextArray[textEnum.multipleLoginFailedIdx]
        qmltextLoginFail = qmlTextArray[textEnum.loginFailIdx]
        qmltextLoginSuccess = qmlTextArray[textEnum.loginSuccessIdx]
        qmltextPasscodeEmpty = qmlTextArray[textEnum.passcodeEmptyIdx]
        bransonLoginKeyboard.buttonLoginTextLogin = qmltextLogin
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted:
    {
        updateLanguage()
    }

    QtObject {
        id: textEnum
        readonly property int enterPasscodeIdx:         0
        readonly property int loginIdx:                 1
        readonly property int multipleLoginFailedIdx:   2
        readonly property int loginFailIdx:             3
        readonly property int loginSuccessIdx:          4
        readonly property int passcodeEmptyIdx:         5

    }

    BorderImage {
        id: backgroundLoginUi
        source: "qrc:/images/background.jpg"
        anchors.fill: parent
    }

    Rectangle{
        id: rectangle
        anchors.centerIn: parent
        width: Math.round(238 * Style.scaleHint)
        height: Math.round(440 * Style.scaleHint)
        color: "transparent"
        Image {
            id: imageLoginUiLock
            height: Math.round(20 * Style.scaleHint)
            width: Math.round(20 * Style.scaleHint)
            source: "qrc:/images/Password icon.svg"
            sourceSize.width:  imageLoginUiLock.width
            sourceSize.height: imageLoginUiLock.height
            anchors.verticalCenter: textLoginUiTooltip.verticalCenter
            anchors.left: parent.left

        }
        Text {
            id: textLoginUiTooltip
            height: Math.round(27 * Style.scaleHint)
            text: qmltextEnterPasscode
            font.pixelSize: fontPixelSize
            anchors.left: imageLoginUiLock.right
            anchors.leftMargin: Math.round(12 * Style.scaleHint)
            anchors.top: parent.top
            font.family: Style.light.name
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            color: Style.whiteFontColor
        }
        TextField{
            id: textFildPassword
            anchors.top: textLoginUiTooltip.bottom
            anchors.topMargin: Math.round(3 * Style.scaleHint)
            width: parent.width
            height: Math.round(35 * Style.scaleHint)
            echoMode: TextInput.Password
            font.pixelSize: fontPixelSize
            mouseSelectionMode: TextInput.SelectCharacters
            passwordCharacter: "*"
            validator: RegularExpressionValidator{ regularExpression: /[0-9]+/ }
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    textFildPassword.focus = true
                    Qt.inputMethod.hide()
                }
            }

            Image {
                id: imageErrorInfo
                height: Math.round(18 * Style.scaleHint)
                width: Math.round(18 * Style.scaleHint)
                source: "qrc:/images/Exclaim-Circle-Red30.svg"
                sourceSize.width:  imageErrorInfo.width
                sourceSize.height: imageErrorInfo.height
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: Math.round(8 * Style.scaleHint)
                visible: loginErrorCode === 0 ? false : true
            }

            background: Rectangle{
                anchors.fill: parent
                border.width: 2
                border.color: Style.activeFrameBorderColor
            }
        }
        Text {
            id: textErrorMessage
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.rightMargin: Math.round(37 * Style.scaleHint)
            anchors.top: textFildPassword.bottom
            anchors.topMargin: Math.round(4 * Style.scaleHint)
            height: Math.round(44 * Style.scaleHint)
            text: qmlLoginErrorMessage
            font.family: Style.light.name
            color: Style.whiteFontColor
            font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
            visible: loginErrorCode === 0 ? false : true
            wrapMode: Text.WordWrap
        }

        BransonLoginKeyboard{
            id: bransonLoginKeyboard
            anchors.top: textErrorMessage.bottom
            anchors.topMargin: Math.round(10 * Style.scaleHint)
            anchors.left: parent.left
        }
        //Process data sent by the keyboard
        function slotDealKeyBoardData(data)
        {
            textFildPassword.focus=true
            Qt.inputMethod.hide()
            if(data === BransonNumpadDefine.EnumKeyboard.Clear)
            {
                textFildPassword.clear()
            }
            else if(data === BransonNumpadDefine.EnumKeyboard.Delete)
            {
                textFildPassword.remove(textFildPassword.cursorPosition-1,textFildPassword.cursorPosition)
            }
            else if(data === BransonNumpadDefine.EnumKeyboard.Login)
            {
                if(debug === true)
                {
                    mainWindow.loginProcess()
                }
                else
                {
                    if(textFildPassword.text === "")
                    {
                        qmlLoginErrorMessage = qmltextPasscodeEmpty
                        loginErrorCode = LoginIndexEnum.EMPTY_PASSCODE
                        return
                    }
                    loginErrorCode = login.loginValidate(textFildPassword.text)
                    switch(loginErrorCode)
                    {
                        case LoginIndexEnum.LOGIN_FAIL:
                            qmlLoginErrorMessage = qmltextLoginFail
                            break;
                        case LoginIndexEnum.MULTIPLE_FAILED_LOGIN:
                            qmlLoginErrorMessage = qmltextMultipleLoginFailed
                            break;
                        case LoginIndexEnum.SUCCESS:
                            mainWindow.loginProcess()
                            break;
                    }
                    textFildPassword.text = ""
                }
            }
            else{
                textFildPassword.insert(textFildPassword.cursorPosition, data)
            }
        }
        Component.onCompleted: {
            bransonLoginKeyboard.signalButtonNum.connect(slotDealKeyBoardData)
            bransonLoginKeyboard.signalButtonFunc.connect(slotDealKeyBoardData)
        }
    }
}
