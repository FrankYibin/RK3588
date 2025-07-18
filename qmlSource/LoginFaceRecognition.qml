﻿/**********************************************************************************************************

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
    // property alias textFildPassword: textFildPassword
    property alias rectangle: rectangle
    property string qmltextEnterPasscode:       qsTr("Face Recognition")
    property string qmltextLogin:               qsTr("Login")
    property string qmltextMultipleLoginFailed: qsTr("Too many failed login attempts. System will be locked for 15 minutes.")
    property string qmltextLoginFail:           qsTr("Invalid Passcode. Please re-enter and try again.")
    property string qmltextLoginSuccess:        qsTr("Login Successful")
    property string qmltextPasscodeEmpty:       qsTr("Please enter a passcode")
    property string qmltextWelcomeMessage:      qsTr("请正对靠近摄像头，请勿遮挡")
    property string qmlLoginErrorMessage:       qmltextLoginSuccess
    property var    qmlTextArray: [qmltextEnterPasscode, qmltextLogin,
        qmltextMultipleLoginFailed, qmltextLoginFail, qmltextLoginSuccess, qmltextPasscodeEmpty]
    property int loginErrorCode: 0
    /*Background picture of login interface*/
    visible: true

    // function updateLanguage()
    // {
    //     qmlTextArray = languageConfig.getLanguageStringList(UIScreenEnum.LOGIN, qmlTextArray)
    //     qmltextEnterPasscode = qmlTextArray[textEnum.enterPasscodeIdx]
    //     qmltextLogin = qmlTextArray[textEnum.loginIdx]
    //     qmltextMultipleLoginFailed = qmlTextArray[textEnum.multipleLoginFailedIdx]
    //     qmltextLoginFail = qmlTextArray[textEnum.loginFailIdx]
    //     qmltextLoginSuccess = qmlTextArray[textEnum.loginSuccessIdx]
    //     qmltextPasscodeEmpty = qmlTextArray[textEnum.passcodeEmptyIdx]
    // }

    // Connections {
    //     target: mainWindow
    //     function onSignalCurrentLanguageChanged()
    //     {
    //         updateLanguage()
    //     }
    // }

    Component.onCompleted:
    {
        // updateLanguage()
        qmlLoginErrorMessage = qmltextWelcomeMessage
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

    Item{
        id: rectangle
        anchors.centerIn: parent
        width: Math.round(250 * Style.scaleHint)
        height: parent.height
        Item {
            id: textErrorMessage
            anchors.left: parent.left
            anchors.right: parent.right
            // anchors.rightMargin: Math.round(37 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(20 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            Text {
                anchors.centerIn: parent
                text: qmlLoginErrorMessage
                font.family: "宋体"
                color: Style.whiteFontColor
                font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                // visible: loginErrorCode === 0 ? false : true
                wrapMode: Text.WordWrap
            }
        }
	
        HBLoginFaceBoard {
            id: faceArea
            anchors.top: textErrorMessage.bottom
            anchors.topMargin: Math.round(10 * Style.scaleHint)
            anchors.left: parent.left
            width: parent.width

        }

        //Process data sent by the keyboard
        function slotDealKeyBoardData(data)
        {
            Qt.inputMethod.hide()
            switch(data)
            {
            case BransonNumpadDefine.EnumKeyboard.PasswordLogin:
                mainWindow.showPasswordLogin()
                break;
            case BransonNumpadDefine.EnumKeyboard.Login:

                break;
            }

        }

        Component.onCompleted: {
            faceArea.signalButtonFunc.connect(slotDealKeyBoardData)
        }
    }
}
