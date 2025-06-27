import QtQuick 2.0
import QtGraphicalEffects 1.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import UserGlobalDefine 1.0
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
        id: loadingVisible
        anchors.top: parent.top
        anchors.topMargin: Math.round(10 * Style.scaleHint)
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


    Item{
        anchors.top: loadingVisible.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width:  Math.round(600 * Style.scaleHint)
        height: Math.round(300 * Style.scaleHint)
        HBFaceDetector
        {
            id: faceDetector
            anchors.fill: parent
            onImageIsReady:
            {
                var userID = UserModel.UserName;
                VideoCapture.deleteFaceRecord(userID)
                if(VideoCapture.generateFaceEigenValue(userID) === true)
                {
                    mainWindow.showDialogScreen(qsTr("人脸录入成功"), null)
                }
                else
                {
                    faceDetector.showPreview = false
                    loadingVisible.visible = false
                    mainWindow.showDialogScreen(qsTr("请重新人脸录入"), null)
                }
            }
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
                    // 指定保存路径到当前工作目录
                    faceDetector.captureFrame()
                    faceDetector.showPreview = true // 切换为显示图片
                    loadingVisible.visible = true
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


