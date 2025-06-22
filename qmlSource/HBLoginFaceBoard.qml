/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/
import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtMultimedia 5.15
import Style 1.0
Rectangle {
    property int minWidthNumpad: Math.round(50 * Style.scaleHint)
    property int minHeightNumpad: Math.round(290 * Style.scaleHint)
    property int gridRowColumnSpaceing: Math.round(12 * Style.scaleHint)
    property int loginColumnSpaceing: Math.round(22 * Style.scaleHint)
    readonly property string buttonLoginColor: "#6699CC"
    readonly property string buttonLoginTextColor: "#ffffff"
    property int buttonLoginSize: Math.round(50* Style.scaleHint)

    readonly property string buttonLogin:             "#000000"
    property string buttonLoginTextLogin:             qsTr("人脸登录")

    property int buttonLoginFontSize: Math.round(Style.style5  * Style.scaleHint)
    signal signalButtonFunc(int funcBtn)

    Item{
        id: loadingVisible
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: Math.round(30 * Style.scaleHint)
        visible: false
        clip: true
        AnimatedImage{
            anchors.centerIn: parent
            source: "qrc:/images/loading.gif"
            playing: loadingVisible.visible
        }
    }

    Item {
        id: faceArea
        anchors.top: loadingVisible.bottom
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.horizontalCenter: parent.horizontalCenter
        height: 4 * buttonLoginSize + 3 * gridRowColumnSpaceing
        width: 4 * buttonLoginSize + 3 * gridRowColumnSpaceing

        HBFaceDetector{
            id: faceDetector
            anchors.fill: parent
            height: parent.height
            width: parent.width
            onImageIsReady:
            {
                if(VideoCapture.detectFaceImage() === true)
                {
                    mainWindow.loginProcess()
                }
                else
                {
                    faceDetector.showPreview = false
                    loadingVisible.visible = false
                    mainWindow.showDialogScreen(qsTr("请重新人脸登录"), null)
                }
            }
        }
    }

    BransonDigitalKeyboard
    {
        id: buttonLogin
        text: buttonLoginTextLogin
        textColor: buttonLoginTextColor
        anchors.left: faceArea.left
        anchors.top: faceArea.bottom
        anchors.topMargin: loginColumnSpaceing
        implicitWidth: buttonLoginSize * 4 + gridRowColumnSpaceing * 3
        implicitHeight: buttonLoginSize
        buttonColor: buttonLoginColor
        fontSize: buttonLoginFontSize
        fontFamily: "宋体"
        onClicked:  {
            if(faceDetector.showPreview == false)
            {
                // 指定保存路径到当前工作目录
                faceDetector.captureFrame()
                signalButtonFunc(BransonNumpadDefine.EnumKeyboard.Login)
                faceDetector.showPreview = true // 切换为显示图片
                loadingVisible.visible = true
            }
        }
    }

    Item{
        anchors.top: buttonLogin.bottom
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        anchors.left: buttonLogin.left
        height: Math.round(30 * Style.scaleHint)
        width: buttonLogin.width
        Text{
            id: faceLogin
            text: qsTr("密码登录")
            anchors.centerIn: parent
            font.family: "宋体"
            font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
            font.underline: true
            color: Style.whiteFontColor
            verticalAlignment: Text.AlignVCenter
        }
        MouseArea{
            anchors.fill: parent
            onClicked: signalButtonFunc(BransonNumpadDefine.EnumKeyboard.PasswordLogin)
        }
    }




}


