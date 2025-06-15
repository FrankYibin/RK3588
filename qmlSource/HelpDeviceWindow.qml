import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import QtWebEngine 1.10
Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_HELP

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

    //import QtQuick 2.0

    Item {
        id: userManual
        WebEngineView {
            id: webVieW
            anchors.fill: parent
            url: ObjUserManual.getUserManualByPDFJS()
        }
    }
}


