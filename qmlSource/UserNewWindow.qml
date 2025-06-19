import QtQuick 2.0
import QtGraphicalEffects 1.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_USER_MANAGEMENT
    readonly property var userGroupNameModel:["超级用户", "操作员", "普通用户", "访客"]
    readonly property int comboBoxWidthLeft:    120
    readonly property int comboBoxWidthRight:   120
    readonly property int componentWidth:       120

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
            visible: true
        }

        HBFaceDetector
        {
            id: faceDetector
            anchors.left: iconUser.left
            anchors.top: parent.top
            width: iconUser.width
            height: iconUser.height
            visible: false
        }

        Column{
            id: newUserSetting
            spacing: Math.round(10 * Style.scaleHint)
            anchors.horizontalCenter: iconUser.horizontalCenter
            anchors.top: iconUser.bottom
            width: Math.round(200 * Style.scaleHint)
            height: Math.round(70 * Style.scaleHint)
            Row{
                id: userName
                spacing: Math.round(5 * Style.scaleHint)
                width: Math.round(200 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)

                Item{
                    height: parent.height
                    width: Math.round(100 * Style.scaleHint)
                    Text{
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        color: Style.whiteFontColor
                        font.family: "宋体"
                        text: "用户名："
                        font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                    }

                }
                HBLineEdit {
                    id: textuserName
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: Math.round(25 * Style.scaleHint)
                    text: ""
                    onAccepted: {

                        //TODO need to send number using modbus
                    }
                }
            }


            Row{
                id: nickName
                spacing: Math.round(5 * Style.scaleHint)
                width: Math.round(200 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)

                Item{
                    height: parent.height
                    width: Math.round(100 * Style.scaleHint)
                    Text{
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        color: Style.whiteFontColor
                        font.family: "宋体"
                        text: "昵称："
                        font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                    }
                }
                HBLineEdit {
                    id: textNickName
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: Math.round(25 * Style.scaleHint)
                    text: ""
                    onAccepted: {

                        //TODO need to send number using modbus
                    }
                }
            }

            Row{
                id: groupName
                spacing: Math.round(5 * Style.scaleHint)
                width: Math.round(200 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)

                Item{
                    height: parent.height
                    width: Math.round(100 * Style.scaleHint)
                    Text{
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        color: Style.whiteFontColor
                        font.family: "宋体"
                        text: "用户等级："
                        font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                    }
                }
                HBComboBox
                {
                    id: comboHarnessType
                    model: userGroupNameModel
                    currentIndex:2
                    width: Math.round(comboBoxWidthRight * Style.scaleHint)
                    height: parent.height
                    fontFamily: Style.regular.name
                    onCurrentIndexChanged: {

                    }
                }

            }

            Row{
                id: userPassword
                spacing: Math.round(5 * Style.scaleHint)
                width: Math.round(200 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)

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
                HBLineEdit {
                    id: textPassWord
                    width: Math.round(componentWidth * Style.scaleHint)
                    height: Math.round(25 * Style.scaleHint)
                    text: ""
                    onAccepted: {

                        //TODO need to send number using modbus
                    }
                }
            }
        }
        Row{
            id: buttonGroup
            anchors.bottom: parent.bottom
            anchors.bottomMargin:  Math.round(-90 * Style.scaleHint)
            // height: Math.round(40 * Style.scaleHint)
            // width: Math.round((150 * 2 + 20) * Style.scaleHint)
            HBPrimaryButton
            {
                id: buttonExit
                width: Math.round(150 * Style.scaleHint)
                height: Math.round(40 * Style.scaleHint)
                text: qsTr("保存")
                onClicked:
                {
                    // controlLimitNumpad.visible = false
                    const username = textuserName.text
                    const password = textPassWord.text
                    const groupname = comboHarnessType.currentText
                    const nickname = textNickName.text

                    if (username === "" || password === "") {
                        console.log("用户名和密码不能为空")
                        return
                    }

                    if (success) {
                        console.log("添加成功")
                        //
                    } else {
                        console.log("添加失败")
                    }
                }
            }
        }
    }
}


