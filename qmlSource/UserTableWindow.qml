import QtQuick 2.0
import QtGraphicalEffects 1.15
import Style 1.0
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
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
    Component.onCompleted:
    {
        UserModel.loadFromDatabase()
    }

    HBTableView {
        id: userManagerTable
        property int selectedRow: -1
        anchors.left: parent.left
        anchors.leftMargin: Math.round(10 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(10 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(50 * Style.scaleHint)
        headerHeight: Math.round(40 * Style.scaleHint)
        rowHeight: Math.round(35 * Style.scaleHint)
        fontSize: Math.round(Style.style2 * Style.scaleHint)
        model: UserModel
        isMouseMoving: false
        rowDelegate: Rectangle{
            height: userManagerTable.rowHeight
            color: (styleData.row === userManagerTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor

        }
        TableViewColumn {
            role: "Index";              title: qsTr("");                width: 30;
            delegate: Rectangle {
                height: userManagerTable.rowHeight
                width: styleData.columnWidth
                color: (styleData.row === userManagerTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                border.color: Style.hbFrameBorderColor
                Text {
                    anchors.centerIn: parent
                    color: Style.whiteFontColor
                    text: styleData.row + 1
                    font.family: Style.regular.name
                    font.pixelSize: userManagerTable.fontSize
                }
            }
        }
        TableViewColumn {
            role: "UserName";         title: qsTr("用户名");        width: 150
            delegate: Rectangle {
                height: userManagerTable.rowHeight
                width: styleData.columnWidth
                color: (styleData.row === userManagerTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                border.color: Style.hbFrameBorderColor
                Text {
                    anchors.centerIn: parent
                    color: Style.whiteFontColor
                    text: styleData.value
                    font.family: "宋体"
                    font.pixelSize: userManagerTable.fontSize
                }
                MouseArea {
                    anchors.fill: parent
                    property int previousX: 0
                    property int previousY: 0
                    onClicked: {


                    }

                    onPressed: {
                        // previousX = mouseX
                        previousY = mouseY
                    }
                    onMouseXChanged: {
                        var moveToX = userManagerTable.flickableItem.contentX - (mouseX - previousX)
                        if(moveToX >= 0 && moveToX <= userManagerTable.flickableItem.contentWidth - userManagerTable.flickableItem.width)
                            userManagerTable.flickableItem.contentX = moveToX
                        previousX = mouseX
                    }

                }
            }
        }
        TableViewColumn {
            role: "NickName";           title: qsTr("工种");        width: 150
            delegate: Rectangle {
                height: userManagerTable.rowHeight
                width: styleData.columnWidth
                color: (styleData.row === userManagerTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                border.color: Style.hbFrameBorderColor
                Text {
                    anchors.centerIn: parent
                    color: Style.whiteFontColor
                    text:  styleData.value
                    font.family: "宋体"
                    font.pixelSize: userManagerTable.fontSize
                }
            }
        }
        TableViewColumn {
            role: "GroupName";          title: qsTr("用户等级");        width: 150
            delegate: Rectangle {
                height: userManagerTable.rowHeight
                width: styleData.columnWidth
                color: (styleData.row === userManagerTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                border.color: Style.hbFrameBorderColor
                Text {
                    anchors.centerIn: parent
                    color: Style.whiteFontColor
                    text: UserGlobalDefine.userGroupNameModel[styleData.value]
                    font.family: "宋体"
                    font.pixelSize: userManagerTable.fontSize
                }
            }
        }
        TableViewColumn {
            role: "CreateTime";          title: qsTr("创建时间");      width: 150
            delegate: Rectangle {
                height: userManagerTable.rowHeight
                width: styleData.columnWidth
                color: (styleData.row === userManagerTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                border.color: Style.hbFrameBorderColor
                Text {
                    anchors.centerIn: parent
                    color: Style.whiteFontColor
                    text:  styleData.value
                    font.family: Style.regular.name
                    font.pixelSize: userManagerTable.fontSize
                }
            }
        }
        TableViewColumn {
            title: qsTr("操作")
            width: Math.round(270 * Style.scaleHint)
            role: "UserHandle";
            delegate: Rectangle {
                color: (styleData.row === userManagerTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                border.color: Style.hbFrameBorderColor
                height: Math.round(40 * Style.scaleHint)
                width: parent.width
                Row {
                    spacing: Math.round(10 * Style.scaleHint)
                    anchors.centerIn: parent

                    HBPrimaryButton {
                        text: qsTr("修改")
                        width: Math.round(80 * Style.scaleHint)
                        height: Math.round(25 * Style.scaleHint)
                        fontSize: userManagerTable.fontSize
                        visible: styleData.value
                        onClicked: {
                            UserModel.getUser(styleData.row)
                            currentScreenIndexChanged(UserGlobalDefine.createNewUser)
                        }
                    }

                    HBPrimaryButton {
                        text: qsTr("人脸录入")
                        width: Math.round(80 * Style.scaleHint)
                        height: Math.round(25 * Style.scaleHint)
                        fontSize: userManagerTable.fontSize
                        visible: styleData.value
                        onClicked: {
                            UserModel.getUser(styleData.row)
                            currentScreenIndexChanged(UserGlobalDefine.seriseID)
                        }
                    }

                    HBPrimaryButton {
                        text: qsTr("删除")
                        width: Math.round(80 * Style.scaleHint)
                        height: Math.round(25 * Style.scaleHint)
                        fontSize: userManagerTable.fontSize
                        onClicked: {
                            UserModel.getUser(styleData.row)
                            UserModel.removeUser(styleData.row)
                            var userID = UserModel.UserName;
                            VideoCapture.deleteFaceRecord(userID)
                        }
                    }
                }
            }
        }
    }

    HBPrimaryButton
    {
        id: addUser
        width: Math.round(120 * Style.scaleHint)
        height: Math.round(30 * Style.scaleHint)
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin:Math.round(10 * Style.scaleHint)
        anchors.rightMargin: Math.round(20 * Style.scaleHint)
        text: qsTr("新增用户")
        fontSize: Math.round(Style.style5 * Style.scaleHint)
        visible: (UserModel.CurrentGroupIndex > 1) ? false : true
        onClicked:
        {
            UserModel.resetUser()
            currentScreenIndexChanged(UserGlobalDefine.createNewUser)
        }
    }

}


