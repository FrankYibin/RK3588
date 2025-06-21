/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/
pragma Singleton
import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtMultimedia 5.15
import Style 1.0
Camera {
    id: camera
    property alias imageCapture: camera.imageCapture
    signal isImageReady(var image)
    deviceId: "/dev/video1"
    imageProcessing.whiteBalanceMode: CameraImageProcessing.WhiteBalanceFlash

    exposure {
        exposureCompensation: -1.0
        exposureMode: Camera.ExposurePortrait
    }

    flash.mode: Camera.FlashRedEyeReduction

    imageCapture {
        onImageCaptured: {
            isImageReady(preview)  // Show the preview in an Image
        }
    }
}


