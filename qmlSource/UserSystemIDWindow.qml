import QtQuick 2.0
import QtGraphicalEffects 1.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_USER_MANAGEMENT
    property bool enableFaceRecord: false

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
        anchors.horizontalCenter: parent.horizontalCenter
        width: Math.round(175 * Style.scaleHint)
        height: iconUser.height + Math.round((20 + 20) * Style.scaleHint) + newUserSetting.height
        Image
        {
            id: iconUser
            anchors.left: parent.left
            anchors.top: parent.top
            width: Math.round(175 * Style.scaleHint)
            height: Math.round(200 * Style.scaleHint)
            source: "qrc:/images/userManagement.png"
            fillMode: Image.PreserveAspectFit
            smooth: true
            sourceSize.width: width
            sourceSize.height: height
            visible: !enableFaceRecord
        }

        HBFaceDetector
        {
            id: faceDetector
            anchors.left: iconUser.left
            anchors.top: parent.top
            width: iconUser.width
            height: iconUser.height
            visible: enableFaceRecord
        }

    }
    Row{
        id: buttonGroup
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: Math.round(10 * Style.scaleHint)
        height: Math.round(40 * Style.scaleHint)
        width: Math.round((150 * 2 + 20) * Style.scaleHint)
        spacing: Math.round(20 * Style.scaleHint)
        HBPrimaryButton
        {
            width: Math.round(150 * Style.scaleHint)
            height: Math.round(40 * Style.scaleHint)
            text: (enableFaceRecord === false)? qsTr("开启人脸录入") : qsTr("关闭人脸录入")
            onClicked:
            {
                if(enableFaceRecord === false)
                    enableFaceRecord = true
                else
                    enableFaceRecord = false
            }
        }

        HBPrimaryButton
        {
            id: buttonExit

            width: Math.round(150 * Style.scaleHint)
            height: Math.round(40 * Style.scaleHint)
            text: qsTr("保存")
            onClicked:
            {

            }
        }
    }

}


