import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import DepthGlobalDefine 1.0
import TensionsGlobalDefine 1.0
Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_DASHBOARD
    Rectangle{
        id: background
        anchors.fill: parent
        Image {
            source: "qrc:/images/bg1.png"
            anchors.fill: parent
            smooth: true
        }
    }

    Rectangle
    {
        id: pandelSection
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left
        height: parent.height / 2
        gradient: Gradient {
        GradientStop { position: 0.0; color: Style.backgroundLightColor }
        GradientStop { position: 1.0; color: Style.backgroundDeepColor }
        }
    }

    Rectangle
    {
        id: basicSection
        anchors.top: pandelSection.bottom
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.left: pandelSection.left
        anchors.right: pandelSection.right
        anchors.bottom: parent.bottom
        color: Style.backgroundDeepColor
    }

    Row
    {
        id: pandel
        anchors.left: pandelSection.left
        anchors.leftMargin: Math.round(10 * Style.scaleHint)
        anchors.top: pandelSection.top
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.right: pandelSection.right
        anchors.rightMargin: Math.round(10 * Style.scaleHint)
        spacing: Math.round(20 * Style.scaleHint)
        anchors.bottom: pandelSection.bottom

        function valueToAngel(value)
        {
            if(value < 0)
                value = 0
            if(value > 1200)
                value = 1200
            return ((240/ 1200) * value + 60)
        }

        HBPandel
        {
            id: pandelDepth
            angle: pandel.valueToAngel(Number(txtDepth.text))

            HBTextField
            {
                id: txtDepth
                anchors.top: pandelDepth.bottom
                anchors.topMargin: Math.round(20 * Style.scaleHint)
                anchors.horizontalCenter: pandelDepth.horizontalCenter
                width: Math.round(90 * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                onlyForNumpad: true
                font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                validator: RegularExpressionValidator{ regularExpression: /^\d{1,4}(\.\d{1,2})?$/ }
                text:(HBHome.Depth / 100.0).toFixed(2)
                enabled: false

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
                anchors.horizontalCenter: pandelDepth.horizontalCenter
                text: "深度"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                font.family: "宋体"
                color: Style.whiteFontColor
            }
        }

        HBPandel
        {
            id: pandelVelocity
            angle: pandel.valueToAngel(Number(txtVelocity.text))

            HBTextField
            {
                id: txtVelocity
                anchors.top: pandelVelocity.bottom
                anchors.topMargin: Math.round(20 * Style.scaleHint)
                anchors.horizontalCenter: pandelVelocity.horizontalCenter
                width: Math.round(90 * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                onlyForNumpad: true
                font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                validator: RegularExpressionValidator{ regularExpression: /^\d{1,5}(\.\d{1,2})?$/ }
                // text: "1200.00"
//                text: HBHome.Speed
                text:(HBHome.Speed / 100.0).toFixed(2)
                enabled: false
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
                anchors.horizontalCenter: pandelVelocity.horizontalCenter
                text: "速度"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                font.family: "宋体"
                color: Style.whiteFontColor
            }
        }

        HBPandel
        {
            id: pandelTension
            angle: pandel.valueToAngel(Number(txtTension.text))

            HBTextField
            {
                id: txtTension
                anchors.top: parent.bottom
                anchors.topMargin: Math.round(20 * Style.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
                width: Math.round(90 * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                onlyForNumpad: true
                font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                validator: RegularExpressionValidator{ regularExpression: /^\d{1,4}(\.\d{1,2})?$/ }
                //text: "1200.00"
//                text: HBHome.Tension
                text:(HBHome.Tension / 100.0).toFixed(2)
                enabled: false

            }
            Text
            {
                id: unitTension
                text: TensionsGlobalDefine.tensionUnitModel[Tensiometer.TensionUnits]//qsTr("kg")
                anchors.left: txtTension.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.verticalCenter: txtTension.verticalCenter
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.whiteFontColor
            }
            Text
            {
                anchors.top: txtTension.bottom
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
                text: "张力"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                font.family: "宋体"
                color: Style.whiteFontColor
            }
        }
        HBPandel
        {
            id: pandelTensionIncrement
            angle: pandel.valueToAngel(Number(txtTensionIncrement.text))

            HBTextField
            {
                id: txtTensionIncrement
                anchors.top: parent.bottom
                anchors.topMargin: Math.round(20 * Style.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
                width: Math.round(90 * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                onlyForNumpad: true
                font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                validator: RegularExpressionValidator{ regularExpression: /^\d{1,4}(\.\d{1,2})?$/ }
                // text: "1200.00"
//                text: HBHome.TensionIncrement
                 text:(HBHome.TensionIncrement / 100.0).toFixed(2)
                 enabled: false

            }
            Text
            {
                id: unittxtTensionIncrement
                text: TensionsGlobalDefine.tensionUnitModel[Tensiometer.TensionUnits] + "/s" //qsTr("kg/s")
                anchors.left: txtTensionIncrement.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.verticalCenter: txtTensionIncrement.verticalCenter
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.whiteFontColor
            }
            Text
            {
                anchors.top: txtTensionIncrement.bottom
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
                text: "张力增量"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                font.family: "宋体"
                color: Style.whiteFontColor
            }
        }
    }


    Row
    {
        id: sensorInfo
        anchors.left: basicSection.left
        anchors.leftMargin: Math.round(10 * Style.scaleHint)
        anchors.top: basicSection.top
        anchors.topMargin: Math.round(30 * Style.scaleHint)
        anchors.right: basicSection.right
        anchors.rightMargin: Math.round(10 * Style.scaleHint)
        anchors.bottom: basicSection.bottom
        spacing: Math.round(20 * Style.scaleHint)

        property int rowHeight: 25
        property int titleWidth: 100
        property int textWidth: 70
        property int rowSpacing: 5
        property int columnSpacing: 40
        property int txtFontSize: Style.style3
        property int txtFontFieldSize: Style.style4


        Column
        {
            id: leftInfo
            width: Math.round(220 * Style.scaleHint)
            height: parent.height
            spacing: Math.round(sensorInfo.columnSpacing * Style.scaleHint)
            Row
            {
                id: infoPulse
                width: parent.width
                height: Math.round(sensorInfo.rowHeight * Style.scaleHint)
                spacing: Math.round(sensorInfo.rowSpacing * Style.scaleHint)
                Text
                {
                    id: titlePulse
                    width: Math.round(sensorInfo.titleWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("脉冲数：")
                    font.pixelSize: Math.round(sensorInfo.txtFontSize * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                    verticalAlignment: Text.AlignVCenter
                }
                HBTextField {
                    id: textPulse
                    width: Math.round(sensorInfo.textWidth * Style.scaleHint)
                    height: parent.height
                    font.pixelSize: Math.round(sensorInfo.txtFontFieldSize * Style.scaleHint)
                   // text: "100"
                    text: HBHome.Pulse
                    enabled: false
                }
            }

            Row
            {
                id: infoMaxVelocity
                width: parent.width
                height: Math.round(sensorInfo.rowHeight * Style.scaleHint)
                spacing: Math.round(sensorInfo.rowSpacing * Style.scaleHint)
                Text
                {
                    id: titleMaxVelocity
                    width: Math.round(sensorInfo.titleWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("极限速度：")
                    font.pixelSize: Math.round(sensorInfo.txtFontSize * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                    verticalAlignment: Text.AlignVCenter
                }
                HBTextField {
                    id: textMaxVelocity
                    width: Math.round(sensorInfo.textWidth * Style.scaleHint)
                    height: parent.height
                    font.pixelSize: Math.round(sensorInfo.txtFontFieldSize * Style.scaleHint)
                    // text: "99.00"
                    text: HBHome.MaxSpeed
                    enabled: false
                }
                Text
                {
                    id: unitMaxVelocity
                    text: DepthGlobalDefine.velocityUnitModel[Depth.VelocityUnit]//qsTr("m/min")
                    font.pixelSize: Math.round(sensorInfo.txtFontSize * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.whiteFontColor
                }
            }

            Row
            {
                id: infoHarnessTension
                width: parent.width
                height: Math.round(sensorInfo.rowHeight * Style.scaleHint)
                spacing: Math.round(sensorInfo.rowSpacing * Style.scaleHint)
                Text
                {
                    id: titleHarnessTension
                    width: Math.round(sensorInfo.titleWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("揽头张力：")
                    font.pixelSize: Math.round(sensorInfo.txtFontSize * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                    verticalAlignment: Text.AlignVCenter
                }
                HBTextField {
                    id: textHarnessTension
                    width: Math.round(sensorInfo.textWidth * Style.scaleHint)
                    height: parent.height
                    font.pixelSize: Math.round(sensorInfo.txtFontFieldSize * Style.scaleHint)
                    // text: "101.00"
                    text: HBHome.HarnessTension
                    enabled: false
                }
                Text
                {
                    id: unitHarnessTension
                    text: TensionsGlobalDefine.tensionUnitModel[Tensiometer.TensionUnits]//qsTr("kg")
                    font.pixelSize: Math.round(sensorInfo.txtFontSize * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.whiteFontColor
                }
            }
        }

        Column
        {
            id: middleInfo
            width: Math.round(210 * Style.scaleHint)
            height: parent.height
            spacing: Math.round(sensorInfo.columnSpacing * Style.scaleHint)
            Row
            {
                id: infoMaxTension
                width: parent.width
                height: Math.round(sensorInfo.rowHeight * Style.scaleHint)
                spacing: Math.round(sensorInfo.rowSpacing * Style.scaleHint)
                Text
                {
                    id: titleMaxTension
                    width: Math.round(sensorInfo.titleWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("极限张力：")
                    font.pixelSize: Math.round(sensorInfo.txtFontSize * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                    verticalAlignment: Text.AlignVCenter
                }
                HBTextField
                {
                    id: textMaxTension
                    // text: "255.00"
                    text: HBHome.MaxTension
                    width: Math.round(sensorInfo.textWidth * Style.scaleHint)
                    height: parent.height
                    font.pixelSize: Math.round(sensorInfo.txtFontFieldSize * Style.scaleHint)
                    enabled: false
                }
                Text
                {
                    id: unitMaxTension
                    text: TensionsGlobalDefine.tensionUnitModel[Tensiometer.TensionUnits]//qsTr("kg")
                    font.pixelSize: Math.round(sensorInfo.txtFontSize * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.whiteFontColor
                }
            }

            Row
            {
                id: infoMaxTensionIncrement
                width: parent.width
                height: Math.round(sensorInfo.rowHeight * Style.scaleHint)
                spacing: Math.round(sensorInfo.rowSpacing * Style.scaleHint)
                Text
                {
                    id: titleMaxTensionIncrement
                    width: Math.round(sensorInfo.titleWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("极限张力增量：")
                    font.pixelSize: Math.round(sensorInfo.txtFontSize * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                    verticalAlignment: Text.AlignVCenter
                }
                HBTextField
                {
                    id: textMaxTensionIncrement
                    // text: qsTr("10.00")
                    text: HBHome.MaxTensionIncrement
                    width: Math.round(sensorInfo.textWidth * Style.scaleHint)
                    height: parent.height
                    font.pixelSize: Math.round(sensorInfo.txtFontFieldSize * Style.scaleHint)
                    enabled: false
                }
                Text
                {
                    id: unitMaxTensionIncrement
                    text: TensionsGlobalDefine.tensionUnitModel[Tensiometer.TensionUnits] + "/s" //qsTr("kg/s")
                    font.pixelSize: Math.round(sensorInfo.txtFontSize * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.whiteFontColor
                }
            }

            Row
            {
                id: infoMaxParameterStatus
                width: parent.width
                height: Math.round(sensorInfo.rowHeight * Style.scaleHint)
                spacing: Math.round(sensorInfo.rowSpacing * Style.scaleHint)
                Text
                {
                    id: titleSensorWeight
                    width: Math.round(sensorInfo.titleWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("极限参数状态：")
                    font.pixelSize: Math.round(sensorInfo.txtFontSize * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                    verticalAlignment: Text.AlignVCenter
                }
                HBTextField
                {
                    id: textSensorWeight
                    text: qsTr("自动")
                    // text: HBHome.MaxParameterStatus
                    width: Math.round(sensorInfo.textWidth * Style.scaleHint)
                    height: parent.height
                    font.pixelSize: Math.round(sensorInfo.txtFontFieldSize * Style.scaleHint)
                    font.family: "宋体"
                    enabled: false
                }
            }
        }

        Column
        {
            id: rightInfo
            width: Math.round(240 * Style.scaleHint)
            height: parent.height
            spacing: Math.round(sensorInfo.columnSpacing * Style.scaleHint)
            Row
            {
                id: infoTargetDepth
                width: parent.width
                height: Math.round(sensorInfo.rowHeight * Style.scaleHint)
                spacing: Math.round(sensorInfo.rowSpacing * Style.scaleHint)
                Text
                {
                    id: titleTargetDepth
                    width: Math.round(sensorInfo.titleWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("目的深度：")
                    font.pixelSize: Math.round(sensorInfo.txtFontSize * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                    verticalAlignment: Text.AlignVCenter
                }

                HBTextField
                {
                    id: textTargetDepth
                    // text: "1000.00"
                    text: HBHome.TargetDepth
                    width: Math.round(sensorInfo.textWidth * Style.scaleHint)
                    height: parent.height
                    font.pixelSize: Math.round(sensorInfo.txtFontFieldSize * Style.scaleHint)
                    enabled: false
                }
                Text
                {
                    id: unitTargetDepth
                    text: DepthGlobalDefine.distanceUnitModel[Depth.DistanceUnit]//qsTr("m")
                    font.pixelSize: Math.round(sensorInfo.txtFontSize * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.whiteFontColor
                }
            }

            Row
            {
                id: infoK_Value
                width: parent.width
                height: Math.round(sensorInfo.rowHeight * Style.scaleHint)
                spacing: Math.round(sensorInfo.rowSpacing * Style.scaleHint)
                Text
                {
                    id: titleK_Value
                    width: Math.round(sensorInfo.titleWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("K值：")
                    font.pixelSize: Math.round(sensorInfo.txtFontSize * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                    verticalAlignment: Text.AlignVCenter
                }

                HBTextField
                {
                    id: textK_Value
                    // text: "1"
                    text:HBHome.KValue
                    width: Math.round(sensorInfo.textWidth * Style.scaleHint)
                    height: parent.height
                    font.pixelSize: Math.round(sensorInfo.txtFontFieldSize * Style.scaleHint)
                    enabled: false
                }
            }

            Row
            {
                id: infoNetworkStatus
                width: parent.width
                height: Math.round(sensorInfo.rowHeight * Style.scaleHint)
                spacing: Math.round(sensorInfo.rowSpacing * Style.scaleHint)
                Text
                {
                    id: titleNetworkStatus
                    width: Math.round(sensorInfo.titleWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("网络状态：")
                    font.pixelSize: Math.round(sensorInfo.txtFontSize * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                    verticalAlignment: Text.AlignVCenter
                }

                HBTextField
                {
                    id: textTensionUnit
                    text: qsTr("未连接")
                    // text: HBHome.NetworkStatus
                    width: Math.round(sensorInfo.textWidth * Style.scaleHint)
                    height: parent.height
                    font.pixelSize: Math.round(sensorInfo.txtFontFieldSize * Style.scaleHint)
                    font.family: "宋体"
                    enabled: false
                }
            }
        }
    }
}


