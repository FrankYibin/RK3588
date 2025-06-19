import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Style 1.0
SpinBox {
    id: customSpinBox
    property int init_MIN: 0
    property int init_MAX: 2147483647
    height: 30
    width: 140
    font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
    horizontalAlignment: Qt.AlignLeft
    minimumValue: init_MIN
    maximumValue: init_MAX
    decimals: 0

    property color textColor: "#141E29"
    property color disabledColor: textColor
    property color backGroundColor: "#EFF5F7"
    property color disenabledBackGroundColor: "#e5d8d3"
    property color borderColor: "#464646"

    onEnabledChanged: {
        if(!enabled)
        {
            customSpinBox.focus = false
        }
    }

    style: SpinBoxStyle{
        textColor: enabled ? customSpinBox.textColor : customSpinBox.disabledColor
        background: Rectangle{
            anchors.fill: parent
            border.width: 1
            border.color: borderColor
            color: customSpinBox.enabled ? backGroundColor : disenabledBackGroundColor
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
