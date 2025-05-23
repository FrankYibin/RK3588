﻿/**********************************************************************************************************

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
Item {
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

    Rectangle {
        id: faceArea
        height: 4 * buttonLoginSize + 3 * gridRowColumnSpaceing
        width: 4 * buttonLoginSize + 3 * gridRowColumnSpaceing
        Component.onCompleted: {
            console.debug("Device: ", camera.deviceId)
            console.debug("DisplayName: ", camera.displayName)
        }

        Camera {
            id: camera
            deviceId: "/dev/video1"
            imageProcessing.whiteBalanceMode: CameraImageProcessing.WhiteBalanceFlash

            exposure {
                exposureCompensation: -1.0
                exposureMode: Camera.ExposurePortrait
            }

            flash.mode: Camera.FlashRedEyeReduction

            imageCapture {
                onImageCaptured: {
                     photoPreview.source = preview  // Show the preview in an Image
                }
            }
        }

//        VideoOutput {
//            source: camera
//            anchors.top: faceArea.top
//            anchors.bottom: faceArea.bottom
//            anchors.left: faceArea.left
//            anchors.right: faceArea.right
//            fillMode: Image.PreserveAspectFit
//            focus : visible // to receive focus and capture key events when visible
//        }

        Image {
            id: photoPreview
            anchors.fill: parent
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
        onClicked:  signalButtonFunc(BransonNumpadDefine.EnumKeyboard.Login)
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


