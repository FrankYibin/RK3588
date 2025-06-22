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
    // property alias imageCapture: camera.imageCapture
    signal imageIsReady();
    // Camera
    // {
    //     id: camera
    //     deviceId: "/dev/video1"
    //     imageProcessing.whiteBalanceMode: CameraImageProcessing.WhiteBalanceFlash

    //     exposure {
    //         exposureCompensation: -1.0
    //         exposureMode: Camera.ExposurePortrait
    //     }

    //     flash.mode: Camera.FlashRedEyeReduction

    //     imageCapture {
    //         onImageCaptured: {
    //             photoPreview.source = preview  // Show the preview in an Image
    //         }
    //         onImageSaved: {
    //             console.debug("333333333333333333333333")
    //             imageIsReady()
    //         }
    //     }
    //     Component.onCompleted: {
    //         console.debug("Device: ", camera.deviceId)
    //         console.debug("DisplayName: ", camera.displayName)
    //     }
    // }

    function captureFrame()
    {
        // 使用 VideoOutput.grabToImage() 捕获当前帧
        videoOutput.grabToImage(function(result) {
            if (result) {
                // 保存图片到本地
                var savePath = VideoCapture.getImageDirectory() + "/tmpImage.jpg";// 保存到当前目录
                result.saveToFile(savePath);
                photoPreview.source = ""
                photoPreview.source = result.url;
                console.log("图片已保存到:", savePath);
                imageIsReady();
            } else {
                console.error("截屏失败，未能获取当前帧");
            }
        });
    }

    MediaPlayer {
        id: mediaPlayer
        autoPlay: true
        source: "gst-pipeline: v4l2src device=/dev/video1 ! image/jpeg,width=1920,height=1080,framerate=30/1 ! jpegdec ! videoconvert ! qtvideosink"
        onError: {
            console.error("MediaPlayer error:", errorString)
        }
    }

    VideoOutput {
        id: videoOutput
        // source: camera
        source: mediaPlayer
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        focus : visible // to receive focus and capture key events when visible
        visible: !showPreview // 只在未显示图片时显示摄像头
    }

    Image {
        id: photoPreview
        anchors.fill: parent
        visible: showPreview // 只在需要显示图片时显示图片
        fillMode: Image.Stretch
    }
}


