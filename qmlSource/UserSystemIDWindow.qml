import QtQuick 2.0
import QtGraphicalEffects 1.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import UserGlobalDefine 1.0
import FaceDetector 1.0
Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_USER_MANAGEMENT
    signal currentScreenIndexChanged(var index)
    Rectangle
    {
        id: background
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: parent.height
        gradient: Gradient {
        GradientStop { position: 0.0; color: Style.backgroundLightColor }
        GradientStop { position: 1.0; color: Style.backgroundDeepColor }
        }
    }


    Item{
        anchors.top: parent.top
        anchors.topMargin: Math.round(20 * Style.scaleHint)
        anchors.horizontalCenter: parent.horizontalCenter
        width:  Math.round(200 * Style.scaleHint)
        height: Math.round(200 * Style.scaleHint)
        // Image
        // {
        //     id: iconUser
        //     anchors.left: parent.left
        //     anchors.top: parent.top
        //     width: Math.round(175 * Style.scaleHint)
        //     height: Math.round(200 * Style.scaleHint)
        //     source: "qrc:/images/userManagement.png"
        //     fillMode: Image.PreserveAspectFit
        //     smooth: true
        //     sourceSize.width: width
        //     sourceSize.height: height
        //     visible: !enableFaceRecord
        // }

        FaceDetector
        {
            id: faceDetector
            anchors.fill: parent
        }

    }
    Row{
        id: buttonGroup
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: Math.round(20 * Style.scaleHint)
        height: Math.round(30 * Style.scaleHint)
        width: Math.round((100 * 2 + 20) * Style.scaleHint)
        spacing: Math.round(20 * Style.scaleHint)
        HBPrimaryButton
        {
            width: Math.round(100 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            text: qsTr("人脸录入")
            onClicked:
            {
                if(faceDetector.showPreview == false)
                {
                    faceDetector.imageCapture.capture()
                    // signalButtonFunc(BransonNumpadDefine.EnumKeyboard.Login)
                    faceDetector.showPreview = true // 切换为显示图片
                    // loadingVisible.visible = true
                }
                else
                {
                    faceDetector.showPreview = false
                    // loadingVisible.visible = false
                }
            }
        }

        HBPrimaryButton
        {
            id: buttonExit

            width: Math.round(100 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            text: qsTr("保存")
            onClicked:
            {
                currentScreenIndexChanged(UserGlobalDefine.userManagement)
            }
        }
    }

}


