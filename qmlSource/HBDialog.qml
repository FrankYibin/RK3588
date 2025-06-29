import QtQuick 2.15
import QtQuick.Controls 2.15
import Style 1.0
Dialog {
    id: myDialog
    property alias contentText: contentText.text
    property var confirmCallback: null
    visible: true
    title: "Blue sky dialog"
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel
    contentItem: Rectangle {
        color: Style.hbButtonBackgroundColor
        anchors.fill: parent
        Text {
            id: contentText
            text: "Hello blue sky!"
            color: Style.whiteFontColor
            anchors.centerIn: parent
            font.family: "宋体"
            font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
        }
    }
    contentWidth: parent.width
    contentHeight: parent.height - dialogHeader.height - dialogFooter.height

    header: Rectangle {
        id: dialogHeader
        width: parent.width
        height: 30
        color: Style.hbButtonBackgroundColor
    }

    footer: Rectangle {
        id: dialogFooter
        width: parent.width
        height: Math.round(40 * Style.scaleHint)
        color: Style.hbButtonBackgroundColor
        Row{
            width: (myDialog.standardButtons === Dialog.Ok) ? Math.round(100 * Style.scaleHint) : Math.round( 210 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            anchors.centerIn: parent
            spacing: Math.round(10 * Style.scaleHint)
            HBPrimaryButton
            {
                width: Math.round(100 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                buttonColor: Style.backgroundLightColor
                text: qsTr("取消")
                visible: (myDialog.standardButtons === Dialog.Ok) ? false : true
                onClicked:
                {
                    myDialog.reject()
                }
            }
            HBPrimaryButton
            {
                width: Math.round(100 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                buttonColor: Style.backgroundLightColor
                text: qsTr("确认")
                onClicked:
                {
                    myDialog.accept()
                }
            }
        }
    }
    onAccepted: {
        if (confirmCallback)
        {
            confirmCallback()
        }
    }
}

