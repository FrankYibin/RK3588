import QtQuick 2.10
import QtGraphicalEffects 1.14
import Style 1.0
Rectangle{
    id: textButton
    width: 100
    height: 36
    clip: true
    color: textButton.enabled ? normalColor : disenabledColor

    property string text: ""
    property alias  textFont: buttonText.font
    property color  textColor: "white"
    property color  textHoverColor: textColor
    property color  textSelectedColor: textColor
    //three state enabled
    property bool   threeStateEnabled: true
    //two state selected
    property bool isSelected: false
    //for isSelected
    property bool clickedChangeState: true

    property int    textHorizontalAlignment: Text.AlignHCenter
    property int    textVerticalAlignment: Text.AlignVCenter
    property color  normalColor: "#6c757d"
    property color  hoverColor: "#8c8c8c"
    property color  pressedColor: "#2d383f"
    property color  disenabledColor: "#C1D1D8"
    property color  selectedColor: "#4988B8"
    property string source: ""

    property int textLeftMargin: 0

    onThreeStateEnabledChanged: {
        if(threeStateEnabled)
        {
            if(privateProperty.btnState == 4)
            {
                privateProperty.btnState = 1
            }
        }
        else if(privateProperty.btnState == 1 && isSelected)
        {
            privateProperty.btnState = 4
        }
    }

    onIsSelectedChanged: {
        if(!threeStateEnabled)
        {
            if(isSelected)
            {
                privateProperty.btnState = 4
            }
            else
            {
                privateProperty.btnState = 1
            }
        }
    }

    QtObject{
        id: privateProperty
        //0: disabled 1-normal 2-hover 3-pressed 4-selected
        property int btnState: 1
        onBtnStateChanged: {
            if(btnState == 0)
            {
                textButton.color = textButton.disenabledColor
                buttonText.color = textColor
            }
            else if(btnState == 1)
            {
                textButton.color = textButton.normalColor
                buttonText.color = textColor
            }
            else if(btnState == 2)
            {
                textButton.color = textButton.hoverColor
                buttonText.color = textHoverColor
            }
            else if(btnState == 3)
            {
                textButton.color = textButton.pressedColor
            }
            else if(btnState == 4)
            {
                textButton.color = textButton.selectedColor
                buttonText.color = textSelectedColor
            }
        }
    }

    signal clicked()

    onEnabledChanged: {
        textButton.color = textButton.enabled ? normalColor : disenabledColor
    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        property bool isLeave: true
        onClicked: {
            textButton.clicked()

            if(!threeStateEnabled && clickedChangeState)
            {
                isSelected =! isSelected
            }
        }
        onEntered: {
            if(!pressed)
            {
                privateProperty.btnState = 2
            }
            isLeave = false
        }
        onExited: {
            if(!pressed)
            {
                if(threeStateEnabled || !isSelected)
                {
                    privateProperty.btnState = 1
                }
                else
                {
                    privateProperty.btnState = 4
                }
            }
            isLeave = true
        }
        onPressed: {
            privateProperty.btnState = 3
        }
        onReleased: {
            if(!isLeave)
            {
                privateProperty.btnState = 2
            }
            else
            {
                if(threeStateEnabled || !isSelected)
                {
                    privateProperty.btnState = 1
                }
                else
                {
                    privateProperty.btnState = 4
                }
            }
        }
    }

    Row{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 10
        Image{
            id: buttonImage
            width: textButton.source !== "" ? textButton.height - 10 : 0
            height: textButton.source !== "" ? buttonImage.width : 0
            source: textButton.source
        }
        Text{
            id: buttonText
//            anchors.fill: parent
//            anchors.leftMargin: textLeftMargin
            color: textColor
            anchors.verticalCenter: textButton.source !== "" ? buttonImage.verticalCenter : parent.verticalCenter
            font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
            text: textButton.text
            horizontalAlignment: textHorizontalAlignment
            verticalAlignment: textVerticalAlignment
        }
    }
}
