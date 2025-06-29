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
    /*Background picture of login interface*/
    visible: true

    QtObject {
        id: textEnum
        readonly property int enterPasscodeIdx:         0
        readonly property int loginIdx:                 1
        readonly property int multipleLoginFailedIdx:   2
        readonly property int loginFailIdx:             3
        readonly property int loginSuccessIdx:          4
        readonly property int passcodeEmptyIdx:         5

    }

    //Process data sent by the keyboard
    // function slotDealKeyBoardData(data)
    // {
    //     textFildPassword.focus=true
    //     Qt.inputMethod.hide()
    //     if(data === BransonNumpadDefine.EnumKeyboard.Clear)
    //     {
    //         textFildPassword.clear()
    //     }
    //     else if(data === BransonNumpadDefine.EnumKeyboard.Delete)
    //     {
    //         textFildPassword.remove(textFildPassword.cursorPosition-1,textFildPassword.cursorPosition)
    //     }
    //     else if(data === BransonNumpadDefine.EnumKeyboard.Login)
    //     {
    //         if(debug === true)
    //         {
    //             mainWindow.loginProcess()
    //         }
    //         else if(debug === false)
    //             mainWindow.loginProcess()
    //         else
    //         {
    //             if(textFildPassword.text === "")
    //             {
    //                 qmlLoginErrorMessage = qmltextPasscodeEmpty
    //                 loginErrorCode = LoginIndexEnum.EMPTY_PASSCODE
    //                 return
    //             }
    //             loginErrorCode = login.loginValidate(textFildPassword.text)
    //             switch(loginErrorCode)
    //             {
    //                 case LoginIndexEnum.LOGIN_FAIL:
    //                     qmlLoginErrorMessage = qmltextLoginFail
    //                     break;
    //                 case LoginIndexEnum.MULTIPLE_FAILED_LOGIN:
    //                     qmlLoginErrorMessage = qmltextMultipleLoginFailed
    //                     break;
    //                 case LoginIndexEnum.SUCCESS:
    //                     mainWindow.loginProcess()
    //                     break;
    //             }
    //             textFildPassword.text = ""
    //         }
    //     }
    //     else if(data === BransonNumpadDefine.EnumKeyboard.FaceLogin)
    //     {
    //         mainWindow.showFaceLogin()
    //     }
    //     else
    //     {
    //         textFildPassword.insert(textFildPassword.cursorPosition, data)
    //     }
    // }

    BorderImage {
        id: backgroundLoginUi
        source: "qrc:/images/background.jpg"
        anchors.fill: parent
    }

    LoginTextField{
        id: userInput
        width: 300
        height: Math.round(30 * Style.scaleHint)
        anchors.top: parent.top//logo.bottom
        anchors.topMargin: 115
        anchors.horizontalCenter: parent.horizontalCenter
        source: "qrc:/images/login_user.png"
        font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
        placeholderText: qsTr("用户名")
        text: "管理员"
        font.family: "宋体"
    }

    LoginTextField{
        id: passwordInput
        width: userInput.width
        height: userInput.height
        anchors.top: userInput.bottom
        anchors.topMargin: 21
        anchors.horizontalCenter: parent.horizontalCenter
        source: "qrc:/images/login_password.png"
        echoMode: TextInput.Password
        font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
        placeholderText: qsTr("密码")
        text: "Default"
    }

    Row{
        spacing: Math.round(10 * Style.scaleHint)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: passwordInput.bottom
        anchors.topMargin: Math.round(20 * Style.scaleHint)

        HBPrimaryButton {
            id: faceBtn
            width: Math.round(100 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            text: qsTr("人脸登录")
            onClicked:
            {
                mainWindow.showFaceLogin()
            }
        }

        HBPrimaryButton {
            id: loginBtn
            width: Math.round(100 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            text: qsTr("密码登录")
            onClicked:
            {
                // if(debug === true)
                //     mainWindow.loginProcess()
                // else if(debug === false)
                //     mainWindow.loginProcess()
                if(userInput.text === "")
                {
                    mainWindow.showDialogScreen(qsTr("用户名不能为空"), Dialog.Ok, null)
                }
                else if(passwordInput.text === "")
                {
                    mainWindow.showDialogScreen(qsTr("密码不能为空"), Dialog.Ok, null)
                }
                else if(UserModel.validateUser(userInput.text, passwordInput.text) === true)
                    mainWindow.loginProcess()
                else
                {
                    mainWindow.showDialogScreen(qsTr("此用户不存在或密码错误"), Dialog.Ok, null)
                }
            }
        }
    }
}
