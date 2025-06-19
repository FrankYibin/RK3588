import QtQuick 2.10
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

TextField {
    id: customTextField
    height: 30
    width: 140
    text: ""
    font.pixelSize: commonUIManager.labelFont()
    property color textColor: "#141E29"
    property color disabledTextColor: textColor
    property color hintTextColor: "#90A6B3"
    property color backGroundColor: "#FFFFFF"
    property color disenabledBackGroundColor: "#efd8d3"
    property color borderColor: "#464646"

    onEnabledChanged: {
        if(!enabled)
        {
            customTextField.focus = false
        }
    }

    style: TextFieldStyle {
        textColor: !customTextField.enabled||customTextField.readOnly ? customTextField.disabledTextColor : customTextField.textColor
        background: Rectangle{
            anchors.fill: parent
            border.width: 1
            border.color: borderColor
            color: !customTextField.enabled||customTextField.readOnly ? disenabledBackGroundColor : backGroundColor
        }
        placeholderTextColor: hintTextColor
    }
}
