import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import UserGlobalDefine 1.0
Item{
    property int qmlscreenIndicator:  UIScreenEnum.HB_USER_MANAGEMENT
    Component.onCompleted:
    {
        userTabModel.resetModel()
    }


    Connections{
        target: screenLoader.item
        function onCurrentScreenIndexChanged(index)
        {
            updateTabBar(index)
        }
    }

    function updateTabBar(index)
    {
        screenLoader.source = ""
        switch(index)
        {
        case UserGlobalDefine.currentUser:
            screenLoader.source = "qrc:/qmlSource/UserCurrentWindow.qml"
            break;
        case UserGlobalDefine.userManagement:
            screenLoader.source = "qrc:/qmlSource/UserTableWindow.qml"
            break;
        case UserGlobalDefine.seriseID:
            screenLoader.source = "qrc:/qmlSource/UserSystemIDWindow.qml"
            break;
        case UserGlobalDefine.createNewUser:
            screenLoader.source = "qrc:/qmlSource/UserNewWindow.qml"
            break;
        case UserGlobalDefine.superUser:
            screenLoader.source = "qrc:/qmlSource/UserSuperWindow.qml"
            break;
        default:
            screenLoader.source = "qrc:/qmlSource/UserCurrentWindow.qml"
            break;
        }
    }

    ListModel {
        id: userTabModel
        function resetModel()
        {
            userTabModel.clear()
            userTabModel.append({"Title":     "用户信息管理",
                                "Width":      100,
                                "Index":      UserGlobalDefine.userManagement,
                                "Visible":    true})
            userTabModel.append({"Title":     "当前用户",
                                "Width":      100,
                                "Index":      UserGlobalDefine.currentUser,
                                "Visible":     false})
            userTabModel.append({"Title":     "人脸信息采集",
                                "Width":      100,
                                "Index":      UserGlobalDefine.seriseID,
                                "Visible":    false})
            userTabModel.append({"Title":     "创建新用户",
                                "Width":      100,
                                "Index":      UserGlobalDefine.createNewUser,
                                "Visible":    false})
            userTabModel.append({"Title":     "查看超级用户",
                                "Width":      100,
                                "Index:":     UserGlobalDefine.superUser,
                                "Visible":    false})
        }
    }


    TabBar {
        id: userTabBar
        anchors.left: parent.left
        anchors.top: parent.top
        width: parent.width
        height: Math.round(30 * Style.scaleHint)
        spacing: 20
        visible: true
        background: Image {
            source: "qrc:/images/bg1.png"
            anchors.fill: parent
            smooth: true
        }

        Repeater {
            id: tabbtn
            model: userTabModel
            delegate: HBTabButton {
                anchors.top: parent.top
                width: Math.round(model.Width * Style.scaleHint)
                height: parent.height
                tabbtnText: model.Title
                visible: model.Visible
                onClicked: {
                    updateTabBar(model.Index)
                }
            }
        }
    }

    Loader{
        id: screenLoader
        width: parent.width
        anchors.top: userTabBar.bottom
        anchors.topMargin: Math.round(20 * Style.scaleHint)
        anchors.bottom: parent.bottom
        source:  "qrc:/qmlSource/UserTableWindow.qml"
    }
}


