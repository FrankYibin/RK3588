import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Style 1.0

SpinBox {
    id: hbSpinBox
    height: Math.round(30 * Style.scaleHint)
    width: Math.round(140 * Style.scaleHint)
    font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
    horizontalAlignment: Qt.AlignLeft
    // minimumValue: commonUIManager.getMinInt()
    // maximumValue: commonUIManager.getMaxInt()
    decimals: 0

    property color textColor: Style.whiteFontColor
    property color disabledColor: textColor
    property color backGroundColor: Style.hbFrameBackgroundColor
    property color disenabledBackGroundColor: "#e5d8d3"
    property color borderColor: Style.hbFrameBorderColor

    onEnabledChanged: {
        if(!enabled)
        {
            hbSpinBox.focus = false
        }
    }

    style: SpinBoxStyle{
        textColor: enabled ? hbSpinBox.textColor : hbSpinBox.disabledColor
        background: Rectangle{
            anchors.fill: parent
            border.width: 1
            border.color: borderColor
            color: hbSpinBox.enabled ? backGroundColor : disenabledBackGroundColor
        }
        incrementControl: Item{
            implicitHeight: 0//customSpinBox.height/2
            implicitWidth: 0//implicitHeight
//            Image{
//                anchors.fill: parent
//                anchors.margins: 5
//                anchors.leftMargin: 3
//                anchors.rightMargin: 3
//                source: "qrc:/images/up.png"
//            }
        }
        decrementControl: Item{
            implicitHeight: 0//customSpinBox.height/2
            implicitWidth: 0//implicitHeight
//            Image{
//                anchors.fill: parent
//                anchors.margins: 5
//                anchors.leftMargin: 3
//                anchors.rightMargin: 3
//                source: "qrc:/images/down.png"
//            }
        }
    }
}
