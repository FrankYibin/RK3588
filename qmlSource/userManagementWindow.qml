import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    property int qmlscreenIndicator:  UIScreenEnum.HB_USER_MANAGEMENT
    Component.onCompleted:
    {
        userTabModel.resetModel()
    }
    QtObject {
        id: userScreenIndex
        readonly property int currentUser:      0
        readonly property int userManagement:   1
        readonly property int seriseID:         2
        readonly property int createNewUser:    3
        readonly property int superUser:        4
    }

    function updateTabBar(index)
    {
        screenLoader.source = ""
        switch(index)
        {
        case userScreenIndex.currentUser:
            screenLoader.source = "qrc:/qmlSource/UserCurrentWindow.qml"
            break;
        case userScreenIndex.userManagement:
            screenLoader.source = "qrc:/qmlSource/UserTableWindow.qml"
            break;
        case userScreenIndex.seriseID:
            screenLoader.source = "qrc:/qmlSource/UserSystemIDWindow.qml"
            break;
        case userScreenIndex.createNewUser:
            screenLoader.source = "qrc:/qmlSource/UserNewWindow.qml"
            break;
        case userScreenIndex.superUser:
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
            userTabModel.append({"Title":     "当前用户",
                                "Width":      100,
                                "Index":      userScreenIndex.currentUser})
            userTabModel.append({"Title":     "用户信息管理",
                                "Width":      100,
                                "Index":      userScreenIndex.userManagement})
            userTabModel.append({"Title":     "人脸信息采集",
                                "Width":      100,
                                "Index":      userScreenIndex.seriseID})
            userTabModel.append({"Title":     "创建新用户",
                                "Width":      100,
                                "Index":      userScreenIndex.createNewUser})
            userTabModel.append({"Title":     "查看超级用户",
                                "Width":      100,
                                "Index:":     userScreenIndex.superUser})
        }
    }


    TabBar {
        id: userTabBar
        anchors.left: parent.left
        anchors.top: parent.top
        width: parent.width
        height: Math.round(30 * Style.scaleHint)
        spacing: 20
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
        source:  "qrc:/qmlSource/UserCurrentWindow.qml"
    }
}


