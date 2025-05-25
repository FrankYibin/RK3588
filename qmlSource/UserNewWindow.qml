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

    Item
    {
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


        Column{
            id: newUserSetting
            spacing: Math.round(10 * Style.scaleHint)
            anchors.horizontalCenter: iconUser.horizontalCenter
            anchors.top: iconUser.bottom
            anchors.topMargin: Math.round(20 * Style.scaleHint)
            width: Math.round(200 * Style.scaleHint)
            height: Math.round(70 * Style.scaleHint)

            Row{
                id: userName
                spacing: Math.round(5 * Style.scaleHint)
                width: Math.round(200 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                Image{
                    anchors.verticalCenter: parent.verticalCenter
                    width: Math.round(20 * Style.scaleHint)
                    height: Math.round(20 * Style.scaleHint)
                    source: "qrc:/images/userIcon.png"
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                    sourceSize.width: width
                    sourceSize.height: height
                }
                Item{
                    height: parent.height
                    width: Math.round(100 * Style.scaleHint)
                    Text{
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        color: Style.whiteFontColor
                        font.family: "宋体"
                        text: "用户："
                        font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                    }
                }

                Text{
                    height: parent.height
                    width: Math.round(50 * Style.scaleHint)
                    color: Style.whiteFontColor
                    font.family: "宋体"
                    text: "何文斌"
                    font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                }
            }

            Row{
                id: userPassword
                spacing: Math.round(5 * Style.scaleHint)
                width: Math.round(200 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)

                Image{
                    width: Math.round(20 * Style.scaleHint)
                    height: Math.round(20 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/images/password.png"
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                    sourceSize.width: width
                    sourceSize.height: height
                }

                Item{
                    height: parent.height
                    width: Math.round(100 * Style.scaleHint)
                    Text{
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        color: Style.whiteFontColor
                        font.family: "宋体"
                        text: "密码："
                        font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                    }
                }

                Text{
                    height: parent.height
                    width: Math.round(50 * Style.scaleHint)
                    color: Style.whiteFontColor
                    font.family: "宋体"
                    text: "何文斌"
                    font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                }
            }
        }

        Row{
            id: buttonGroup
            anchors.top: newUserSetting.bottom
            anchors.topMargin: Math.round(40 * Style.scaleHint)
            anchors.horizontalCenter: newUserSetting.horizontalCenter
            spacing: Math.round(20 * Style.scaleHint)
            height: Math.round(40 * Style.scaleHint)
            width: Math.round((150 * 2 + 20) * Style.scaleHint)
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
                    // controlLimitNumpad.visible = false
                }
            }
        }

    }


}


