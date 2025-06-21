import QtQuick 2.0
import QtGraphicalEffects 1.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import UserGlobalDefine 1.0
Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_USER_MANAGEMENT

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
        anchors.centerIn: parent
        width: Math.round(175 * Style.scaleHint)
        height: Math.round((200 + 20 +  40 * 2 + 30)* Style.scaleHint)
        Image
        {
            id: iconUser
            width: Math.round(175 * Style.scaleHint)
            height: Math.round(200 * Style.scaleHint)
            source: "qrc:/images/userManagement.png"
            fillMode: Image.PreserveAspectFit
            smooth: true
            sourceSize.width: width
            sourceSize.height: height
        }
        Row{
            id: currentUser
            spacing: Math.round(100 * Style.scaleHint)
            anchors.horizontalCenter: iconUser.horizontalCenter
            anchors.top: iconUser.bottom
            anchors.topMargin: Math.round(20 * Style.scaleHint)
            width: Math.round(200 * Style.scaleHint)
            height: Math.round(20 * Style.scaleHint)
            Text{
                height: parent.height
                width: Math.round(50 * Style.scaleHint)
                color: Style.whiteFontColor
                font.family: "宋体"
                text: "当前用户："
                font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
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


        HBPrimaryButton
        {
            id: buttonExit
            anchors.top: currentUser.bottom
            anchors.topMargin: Math.round(20 * Style.scaleHint)
            anchors.horizontalCenter: currentUser.horizontalCenter
            width: Math.round(150 * Style.scaleHint)
            height: Math.round(40 * Style.scaleHint)
            text: qsTr("退出登录")
            onClicked:
            {
                // controlLimitNumpad.visible = false
            }
        }

    }


}


