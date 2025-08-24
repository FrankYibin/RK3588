pragma Singleton //we indicate that this QML Type is a singleton
import QtQuick 2.12
QtObject
{
    id: userScreenIndex
    readonly property int userManagement:   0
    readonly property int currentUser:      1
    readonly property int seriseID:         2
    readonly property int createNewUser:    3
    readonly property int superUser:        4
    readonly property var userGroupNameModel:[qsTr("超级管理员"), qsTr("管理员"), qsTr("操作员")]
}
