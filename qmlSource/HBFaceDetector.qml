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
Item {
    height: 100
    width: 100
    property bool showPreview: false // false = 显示摄像头，true=显示图片
    property alias imageCapture: camera.imageCapture
    signal imageIsReady();
    Camera
    {
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
            onImageSaved: {
                imageIsReady()
            }
        }
        Component.onCompleted: {
            console.debug("Device: ", camera.deviceId)
            console.debug("DisplayName: ", camera.displayName)
        }
    }


    VideoOutput {
        source: camera
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        focus : visible // to receive focus and capture key events when visible
        visible: !showPreview // 只在未显示图片时显示摄像头
    }

    Image {
        id: photoPreview
        anchors.fill: parent
        visible: showPreview // 只在需要显示图片时显示图片
    }
}


