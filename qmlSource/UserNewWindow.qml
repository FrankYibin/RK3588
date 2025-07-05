import QtQuick 2.0
import QtGraphicalEffects 1.15
import Style 1.0
import QtQuick.Controls 2.15
import Com.Branson.UIScreenEnum 1.0
import UserGlobalDefine 1.0
import HB.Database 1.0
Item{
    id: newUser
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_USER_MANAGEMENT
    readonly property int comboBoxWidth:        150
    readonly property int componentWidth:       150
    readonly property int componentHeight:      30
    readonly property int titleWidth:           100
    readonly property int rowSpacing:           10
    readonly property int columnSpacing:        20
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
    Component.onCompleted:
    {
        Qt.inputMethod.visibleChanged.connect(function(){
            if(!Qt.inputMethod.visible)
            {
                newUserSetting.anchors.top = iconUser.bottom
                iconUser.visible = true
            }
        })
    }

    Image
    {
        id: iconUser
        anchors.horizontalCenter: parent.horizontalCenter
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
    Column{
        id: newUserSetting
        spacing: Math.round(columnSpacing * Style.scaleHint)
        anchors.top: iconUser.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: Math.round((titleWidth + componentWidth + rowSpacing) * Style.scaleHint)
        height: Math.round((componentWidth * 4 + columnSpacing * 3) * Style.scaleHint)
        Row{
            id: userName
            spacing: Math.round(rowSpacing * Style.scaleHint)
            width: Math.round((titleWidth + componentWidth + rowSpacing) * Style.scaleHint)
            height: Math.round(componentHeight * Style.scaleHint)
            Item{
                height: parent.height
                width: Math.round(titleWidth * Style.scaleHint)
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
                height: Math.round(componentHeight * Style.scaleHint)
                text: UserModel.UserName
                onActiveFocusChanged:
                {
                    if(activeFocus)
                    {
                        newUserSetting.anchors.top = newUser.top
                        iconUser.visible = false
                        mainWindow.showFullKeyboard(textuserName)
                    }
                }
                enabled: (UserModel.getOperateType() === 0) ? true : false
            }
        }

        Row{
            id: nickName
            spacing: Math.round(rowSpacing * Style.scaleHint)
            width: Math.round((titleWidth + componentWidth + rowSpacing) * Style.scaleHint)
            height: Math.round(componentHeight * Style.scaleHint)

            Item{
                height: parent.height
                width: Math.round(titleWidth * Style.scaleHint)
                Text{
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    color: Style.whiteFontColor
                    font.family: "宋体"
                    text: "工种："
                    font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                }
            }
            HBLineEdit {
                id: textNickName
                width: Math.round(componentWidth * Style.scaleHint)
                height: Math.round(componentHeight * Style.scaleHint)
                text: UserModel.NickName
                onActiveFocusChanged:
                {
                    if(activeFocus)
                    {
                        newUserSetting.anchors.top = newUser.top
                        iconUser.visible = false
                        mainWindow.showFullKeyboard(textNickName)
                    }
                }
                enabled: (UserModel.getOperateType() === 0) ? true : false
            }
        }

        Row{
            id: groupName
            spacing: Math.round(rowSpacing * Style.scaleHint)
            width: Math.round((titleWidth + componentWidth + rowSpacing) * Style.scaleHint)
            height: Math.round(componentHeight * Style.scaleHint)

            Item{
                height: parent.height
                width: Math.round(titleWidth * Style.scaleHint)
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
                model: UserGlobalDefine.userGroupNameModel
                currentIndex: UserModel.GroupIndex
                width: Math.round(comboBoxWidth * Style.scaleHint)
                height: parent.height
                fontFamily: "宋体"
                onCurrentIndexChanged: {

                }
                enabled: (UserModel.getOperateType() === 0) ? true : false
            }
        }

        Row{
            id: userPassword
            spacing: Math.round(rowSpacing * Style.scaleHint)
            width: Math.round((titleWidth + componentWidth + rowSpacing) * Style.scaleHint)
            height: Math.round(componentHeight * Style.scaleHint)

            Item{
                height: parent.height
                width: Math.round(titleWidth * Style.scaleHint)
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
                height: Math.round(componentHeight * Style.scaleHint)
                text: UserModel.Password
                echoMode: TextInput.Password
                onActiveFocusChanged:
                {
                    if(activeFocus)
                    {
                        newUserSetting.anchors.top = newUser.top
                        iconUser.visible = false
                        mainWindow.showFullKeyboard(textPassWord)
                    }
                }
                enabled: (UserModel.getOperateType() === 0) ? true : false
            }
        }
    }


    HBPrimaryButton
    {
        id: buttonExit
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(20 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(20 * Style.scaleHint)
        width: Math.round(100 * Style.scaleHint)
        height: Math.round(40 * Style.scaleHint)
        text: qsTr("保存")
        onClicked:
        {
            // controlLimitNumpad.visible = false
            var username = textuserName.text
            var password = textPassWord.text
            var groupindex = comboHarnessType.currentIndex
            var nickname = textNickName.text

            if (username === "" || password === "") {
                console.log("用户名和密码不能为空")
                mainWindow.showDialogScreen(qsTr("用户名和密码不能为空"), Dialog.Ok, null)
                return
            }

            var success = false
            if(UserModel.RowIndex == -1)
            {
                console.log("添加成功")
                success = UserModel.addNewUser(username, password, groupindex, nickname)
                let logText = `${username}用户添加成功！`;
                HBDatabase.insertOperationLog(logText);
            }
            else
            {
                console.log("更新成功")
                success = UserModel.updateUser(UserModel.RowIndex, username, password, groupindex, nickname)
            }
            if (success)
            {
                currentScreenIndexChanged(UserGlobalDefine.userManagement)
            }
            else
            {
                console.log("添加失败")
                mainWindow.showDialogScreen(qsTr("用户名已存在"), Dialog.Ok, null)
            }
        }
    }
}


