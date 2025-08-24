import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import DepthGlobalDefine 1.0
Item{
    id: tensionPanelPopUp
    readonly property int textWidthUnit: 100
    readonly property int componentWidth: 100
    readonly property int actualTextWidth: 150
    readonly property int buttonWidth: 100
    readonly property int rowSpacing: 10
    readonly property int columnSpacing: 10
    readonly property int optionHeight: 30
    readonly property int actualHeight: 100
    readonly property int textFieldWidth: 110

    Rectangle
    {
        id: background
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: parent.height
        color: "#3d7ab3"
        opacity: 1   // 0~1，0为全透明，1为不透明
    }

    Row
    {
        id: panel
        anchors.left: parent.left
        anchors.leftMargin: Math.round(10 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        width: parent.width
        anchors.bottom: parent.bottom
        spacing: Math.round(30 * Style.scaleHint)

        function valueToAngel(negative, value)
        {
            if(negative === true)
                value += 600

            if(value < 0)
                value = 0
            if(value > 1200)
                value = 1200
            return ((240/ 1200) * value + 60)
        }

        HBPandel
        {
            id: pandelTension
            angle: (HBHome.IsTensiometerOnline === false) ?
                       panel.valueToAngel(false, 0) : panel.valueToAngel(false, Number(txtTension.text))
            HBTextField
            {
                id: txtTension
                anchors.top: parent.bottom
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
                width: Math.round(textFieldWidth * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                onlyForNumpad: true
                font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                validator: RegularExpressionValidator{ regularExpression: /^\d{1,4}(\.\d{1,2})?$/ }
                text: (HBHome.IsTensiometerOnline === false) ? "-------" : HBHome.TensionCurrent
                enabled: false
                textColor: {
                    if((HBHome.IsTensiometerOnline === false) || (HBHome.IsTensionAlarm === true))
                        return Style.redFontColor
                    else
                        return Style.whiteFontColor
                }
            }
            Text
            {
                id: unitTension
                text: TensionsGlobalDefine.tensionUnitModel[TensionSetting.TensionUnit]//qsTr("kg")
                anchors.left: txtTension.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.verticalCenter: txtTension.verticalCenter
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.whiteFontColor
            }
            Text
            {
                id: titleTension
                anchors.top: txtTension.bottom
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("张力")
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                font.family: "宋体"
                color: Style.whiteFontColor
            }

            HBTextField
            {
                id: txtDepth
                anchors.top: titleTension.bottom
                anchors.topMargin: Math.round(10 * Style.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
                width: Math.round(textFieldWidth * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                onlyForNumpad: true
                font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                validator: RegularExpressionValidator{ regularExpression: /^\d{1,4}(\.\d{1,2})?$/ }
                text: HBHome.DepthCurrent
                enabled: false
                textColor: {
                    if(HBHome.IsDepthAlarm === true)
                        return Style.redFontColor
                    else
                        return Style.whiteFontColor
                }

            }
            Text
            {
                id: unitWellDepth
                text: DepthGlobalDefine.distanceUnitModel[Depth.DistanceUnit]//qsTr("m")
                anchors.left: txtDepth.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.verticalCenter: txtDepth.verticalCenter
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.whiteFontColor
            }
            Text
            {
                anchors.top: txtDepth.bottom
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
                text: "深度"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                font.family: "宋体"
                color: Style.whiteFontColor
            }
        }

        HBPandel
        {
            id: pandelTensionDelta
            negative: true
            angle: (HBHome.IsTensiometerOnline === false) ?
                       panel.valueToAngel(true, 0) : panel.valueToAngel(true, Number(txtTensionIncrement.text))
            HBTextField
            {
                id: txtTensionIncrement
                anchors.top: parent.bottom
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
                width: Math.round(textFieldWidth * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                onlyForNumpad: true
                font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                validator: RegularExpressionValidator{ regularExpression: /^\d{1,4}(\.\d{1,2})?$/ }
                text: (HBHome.IsTensiometerOnline === false)? "-------" : HBHome.TensionCurrentDelta
                enabled: false
                textColor: {
                    if((HBHome.IsTensiometerOnline === false) || (HBHome.IsTensionDeltaAlarm === true))
                        return Style.redFontColor
                    else
                        return Style.whiteFontColor
                }
            }
            Text
            {
                id: unittxtTensionIncrement
                text: TensionsGlobalDefine.tensionUnitModel[TensionSetting.TensionUnit] + "/s" //qsTr("kg/s")
                anchors.left: txtTensionIncrement.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.verticalCenter: txtTensionIncrement.verticalCenter
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.whiteFontColor
            }
            Text
            {
                id: titleTensionIncrement
                anchors.top: txtTensionIncrement.bottom
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("张力增量")
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                font.family: "宋体"
                color: Style.whiteFontColor
            }

            HBTextField
            {
                id: txtVelocity
                anchors.top: titleTensionIncrement.bottom
                anchors.topMargin: Math.round(10 * Style.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
                width: Math.round(textFieldWidth * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                onlyForNumpad: true
                font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                validator: RegularExpressionValidator{ regularExpression: /^\d{1,5}(\.\d{1,2})?$/ }
                text: HBHome.VelocityCurrent
                enabled: false
                textColor: {
                    if(HBHome.IsVelocityAlarm === true)
                        return Style.redFontColor
                    else
                        return Style.whiteFontColor
                }
            }
            Text
            {
                id: unitVelocity
                text: DepthGlobalDefine.velocityUnitModel[Depth.VelocityUnit]//qsTr("m/min")
                anchors.left: txtVelocity.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.verticalCenter: txtVelocity.verticalCenter
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.whiteFontColor
            }
            Text
            {
                anchors.top: txtVelocity.bottom
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
                text: "速度"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                font.family: "宋体"
                color: Style.whiteFontColor
            }

        }
    }

    // 拖动区域
    MouseArea {
        id: dragArea
        anchors.fill: parent
        drag.target: tensionPanelPopUp
        drag.axis: Drag.XAndYAxis
    }
//    Text {
//        id: positionDisplay
//        anchors.top: parent.top
//        anchors.right: parent.right
//        anchors.topMargin: 10
//        anchors.rightMargin: 10
//        text: "x: " + tensionPanelPopUp.x.toFixed(0) + ", y: " + tensionPanelPopUp.y.toFixed(0)
//        color: "white"
//        font.pixelSize: 14
//        visible: true
//        z: 999
//    }

    HBPrimaryButton
    {
        id: btnClose
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(10 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(10 * Style.scaleHint)
        width: Math.round(100 * Style.scaleHint)
        height: Math.round(30 * Style.scaleHint)
        text: qsTr("返回")
        fontSize: Math.round(Style.style5 * Style.scaleHint)
        scale: 1/1.7
        onClicked:
        {
           tensionPanelPopUp.visible = false
        }
    }
}


