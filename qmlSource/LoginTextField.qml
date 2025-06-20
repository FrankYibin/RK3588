import QtQuick 2.10
import QtQuick.Controls 2.5

TextField {
    id: myTextField
    height: 30
    width: 160
    color: "#141E29"
    leftPadding: leftImage.visible ? 50 : borderWidth + 2
    property color backGroundColor: enabled ? "#EFF5F7" : "#C1D1D8"
    property int borderWidth: 1
    property string source: ""
    placeholderTextColor: "#90A6B3"
    Image {
        id: leftImage
        source: myTextField.source
        visible: myTextField.source != ""
        anchors.left: parent.left
        anchors.leftMargin: 12
        width: 22
        height: 22
        anchors.verticalCenter: parent.verticalCenter
    }
    background: Rectangle{
        anchors.fill: parent
        border.width: borderWidth
        border.color: "#464646"
        color: backGroundColor
        radius: 4
    }
}
