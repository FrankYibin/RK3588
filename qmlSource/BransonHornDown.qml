import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.VirtualKeyboard 2.15
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import Style 1.0

Item {
    id: window
    width: Math.round(300 * Style.scaleHint)
    height: Math.round(500 * Style.scaleHint)
    visible: true
    property alias id_StatusofHorn: id_StatusofHorn
    property alias canvasAll: canvasAll
    property alias window: window
    property string qmlTextFixture: qsTr("Stroke Len")
    property string qmlTextMP: qsTr("MP")
    property string qmlTextEPC:qsTr("EPC")
    property string qmlTextPPC: qsTr("PPC")
    property string qmlTextWP: qsTr("WP")
    property string qmlTextReady: qsTr("Ready")
    property string qmlTextHome: qsTr("Home")
    property string qmlTextdistanceUnit: " mm"
    property double    dwReadyTextPosition: 46.53
    property double    dwWPTextPosition: 49.53
    property double    dwPPCTextPosition: 51.52
    property double    dwEPCTextPosition: 51.53
    property double    dwMPTextPosition: 53.53
    property double    rangeMinValue: 0.00
    property double    rangeMaxValue: 125.00
    property string    minValue: "0.00"
    property string    maxValue: "125.00"
    property int    allPositionHeight:  Math.round(2 * Style.scaleHint)
    property int    allPositionWidth: id_StatusofHorn.width*1.2
    property color  homeColor: "#6699cc"
    property color  ppcColor: "#cc4d27"
    property color  wpColor: "#311b4b"
    property color  epcColor: "#bf7200"
    property color  mpColor: "#6860a9"
    property color  fontColor :"#000000"
    property color  readyColor: "#60bd00"
    property color  hornColor:"#bbbbbb"
    property color  fixtureColor: "#9fa1a4"
    property string fontfamily:  Style.regular.name
    Canvas
    {

        id:canvasAll
        anchors.fill: parent
        z:20
        smooth: true
        onPaint:
        {
            var context = getContext("2d")
            var i = 1;
            var x1
            var y1
            var x2
            var y2
            for(;i<=10;i++)
            {
                switch(i)
                {
                case 1:
                    x1 = id_StatusofHorn.x + id_ReadyHornPosition_text.x + id_ReadyHornPosition_text.width
                    y1 = id_StatusofHorn.y + id_ReadyHornPosition_text.y + id_ReadyHornPosition_text.height/2
                    x2 = id_StatusofHorn.x + id_ReadyPosition.x
                    y2 = id_StatusofHorn.y + id_ReadyPosition.y + id_ReadyPosition.height/2
                    context.strokeStyle = readyColor
                    break
                case 2:
                    x1 = id_StatusofHorn.x + id_WpHornPosition_text.x + id_WpHornPosition_text.width
                    y1 = id_StatusofHorn.y + id_WpHornPosition_text.y + id_WpHornPosition_text.height/2
                    x2 = id_StatusofHorn.x + id_WPPosition.x
                    y2 = id_StatusofHorn.y + id_WPPosition.y + id_WPPosition.height/2
                    context.strokeStyle = wpColor
                    break;
                case 3:
                    x1 = id_StatusofHorn.x + id_PPCHornPosition_text.x + id_PPCHornPosition_text.width
                    y1 = id_StatusofHorn.y + id_PPCHornPosition_text.y + id_PPCHornPosition_text.height/2
                    x2 = id_StatusofHorn.x + id_PPCPosition.x
                    y2 = id_StatusofHorn.y + id_PPCPosition.y + id_PPCPosition.height/2
                    context.strokeStyle =ppcColor
                    break
                case 4:
                    x1 = id_StatusofHorn.x + id_EPCHornPosition_text.x + id_EPCHornPosition_text.width
                    y1 = id_StatusofHorn.y + id_EPCHornPosition_text.y + id_EPCHornPosition_text.height/2
                    x2 = id_StatusofHorn.x + id_EPCPosition.x
                    y2 = id_StatusofHorn.y + id_EPCPosition.y + id_EPCPosition.height/2
                    context.strokeStyle = epcColor
                    break
                case 5:
                    x1 = id_StatusofHorn.x + id_MPHornPosition_text.x + id_MPHornPosition_text.width
                    y1 = id_StatusofHorn.y + id_MPHornPosition_text.y + id_MPHornPosition_text.height/2
                    x2 = id_StatusofHorn.x + id_MPPosition.x
                    y2 = id_StatusofHorn.y + id_MPPosition.y + id_MPPosition.height/2
                    context.strokeStyle = mpColor
                    break
                case 6:
                    x1 = id_StatusofHorn.x + id_ReadyHornPositionVal.x
                    y1 = id_StatusofHorn.y + id_ReadyHornPositionVal.y + id_ReadyHornPositionVal.height/2
                    x2 = id_StatusofHorn.x + id_ReadyPosition.x + id_ReadyPosition.width
                    y2 = id_StatusofHorn.y + id_ReadyPosition.y + id_ReadyPosition.height/2
                    context.strokeStyle =readyColor
                    break
                case 7:
                    x1 = id_StatusofHorn.x + id_WpHornPositionVal.x
                    y1 = id_StatusofHorn.y + id_WpHornPositionVal.y + id_WpHornPositionVal.height/2
                    x2 = id_StatusofHorn.x + id_WPPosition.x + id_WPPosition.width
                    y2 = id_StatusofHorn.y + id_WPPosition.y + id_WPPosition.height/2
                    context.strokeStyle = wpColor
                    break
                case 8:
                    x1 = id_StatusofHorn.x + id_PPCHornPositionVal.x
                    y1 = id_StatusofHorn.y + id_PPCHornPositionVal.y + id_PPCHornPositionVal.height/2
                    x2 = id_StatusofHorn.x + id_PPCPosition.x + id_PPCPosition.width
                    y2 = id_StatusofHorn.y + id_PPCPosition.y + id_PPCPosition.height/2
                    context.strokeStyle = ppcColor
                    break
                case 9:
                    x1 = id_StatusofHorn.x + id_EPCHornPositionVal.x
                    y1 = id_StatusofHorn.y + id_EPCHornPositionVal.y + id_EPCHornPositionVal.height/2
                    x2 = id_StatusofHorn.x + id_EPCPosition.x + id_EPCPosition.width
                    y2 = id_StatusofHorn.y + id_EPCPosition.y + id_EPCPosition.height/2
                    context.strokeStyle = epcColor
                    break
                case 10:
                    x1 = id_StatusofHorn.x + id_MPHornPositionVal.x
                    y1 = id_StatusofHorn.y + id_MPHornPositionVal.y + id_MPHornPositionVal.height/2
                    x2 = id_StatusofHorn.x + id_MPPosition.x + id_MPPosition.width
                    y2 = id_StatusofHorn.y + id_MPPosition.y + id_MPPosition.height/2
                    context.strokeStyle = mpColor
                    break
                }
                context.beginPath()
                context.lineWidth = 1
                context.moveTo(x1, y1)
                context.lineTo(x2, y2)
                context.stroke()
            }
        }
        /**/
        function resetCanvas()
        {
            var ctx = getContext("2d");
            ctx.reset();
            canvasAll.requestPaint();
        }
    }
    Rectangle
    {
        id:id_StatusofHorn
        x:Math.round(100 * Style.scaleHint)
        y:Math.round(20 * Style.scaleHint)
        color: "#dadada"
        width: Math.round(94 * Style.scaleHint)
        height: Math.round(318 * Style.scaleHint)
        Image {
            id: id_Horn_Pointer
            source: "qrc:/images/buoy.svg"
            anchors.left: id_HomePosition.right
            anchors.verticalCenter: id_HomePosition.verticalCenter
            sourceSize.width:Math.round(39 * Style.scaleHint)
            sourceSize.height:Math.round(30 * Style.scaleHint)
            smooth: true
        }
        Text {
            id: id_Horn_Pointer_text
            text: minValue
            anchors.left: id_Horn_Pointer.right
            anchors.verticalCenter: id_Horn_Pointer.verticalCenter
            font.family: fontfamily
            font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
        }
        Text {
            id: id_HomePosition_text
            text: qmlTextHome
            anchors.right: id_HomePosition.left
            anchors.rightMargin:Math.round(15 * Style.scaleHint)
            color:fontColor
            font.family:fontfamily
            font.pixelSize:  Math.round(Style.style0 * Style.scaleHint)
            anchors.verticalCenter: id_HomePosition.verticalCenter
        }
        Rectangle
        {
            id:id_HomePosition
            color: homeColor
            width:parent.width*(1.25)
            height:allPositionHeight
            anchors.bottom: parent.top
            border.color: homeColor
            anchors.horizontalCenter: parent.horizontalCenter
            border.width: Math.round(2 * Style.scaleHint)
            radius: Math.round(2 * Style.scaleHint)
        }
        Text {
            id: id_ReadyHornPosition_text
            text:qmlTextReady
            anchors.right: id_ReadyPosition.left
            anchors.top: id_ReadyPosition.top
            anchors.topMargin: Math.round(-42 * Style.scaleHint)
            anchors.rightMargin:  Math.round(30 * Style.scaleHint)
            color:fontColor
            font.family: fontfamily
            font.pixelSize:  Math.round(Style.style0 * Style.scaleHint)
        }
        Rectangle
        {
            id:id_ReadyPosition
            color: readyColor
            width:parent.width*(1.25)
            height:allPositionHeight
            anchors.top: id_StatusofHorn.top
            anchors.topMargin: dwReadyTextPosition*parent.height/rangeMaxValue
            border.color: readyColor
            anchors.horizontalCenter: parent.horizontalCenter
            border.width: Math.round(2 * Style.scaleHint)
            radius: Math.round(2 * Style.scaleHint)
        }
        Text {
            id: id_ReadyHornPositionVal
            text: dwReadyTextPosition+qmlTextdistanceUnit
            anchors.left: id_ReadyPosition.right
            anchors.top: id_ReadyPosition.top
            anchors.topMargin: Math.round(-42 * Style.scaleHint)
            anchors.leftMargin:  Math.round(30 * Style.scaleHint)
            color:fontColor
            font.family: fontfamily
            font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
        }
        Text {
            id: id_WpHornPosition_text
            text: qmlTextWP
            anchors.right: id_WPPosition.left
            anchors.rightMargin:  Math.round(30 * Style.scaleHint)
            anchors.top: id_WPPosition.top
            anchors.topMargin: Math.round(-36 * Style.scaleHint)
            color:fontColor
            font.family: fontfamily
            font.pixelSize:  Math.round(Style.style0 * Style.scaleHint)
        }
        Rectangle
        {
            id:id_WPPosition
            color: wpColor
            width:parent.width*(1.25)
            height:allPositionHeight
            anchors.top: id_StatusofHorn.top
            anchors.topMargin: dwWPTextPosition*parent.height/rangeMaxValue
            border.color: wpColor
            anchors.horizontalCenter: parent.horizontalCenter
            border.width: Math.round(2 * Style.scaleHint)
            radius: Math.round(5 * Style.scaleHint)
        }
        Text {
            id: id_WpHornPositionVal
            text: dwWPTextPosition+qmlTextdistanceUnit
            anchors.left: id_WPPosition.right
            anchors.leftMargin:  Math.round(30 * Style.scaleHint)
            anchors.top: id_WPPosition.top
            anchors.topMargin: Math.round(-36* Style.scaleHint)
            color:fontColor
            font.family: fontfamily
            font.pixelSize:  Math.round(Style.style0 * Style.scaleHint)
        }
        Text {
            id: id_PPCHornPosition_text
            text: qmlTextPPC
            anchors.right: id_PPCPosition.left
            anchors.rightMargin:  Math.round(30 * Style.scaleHint)
            anchors.top: id_PPCPosition.top
            anchors.topMargin: Math.round(-29 * Style.scaleHint)
            color:fontColor
            font.family: fontfamily
            font.pixelSize:  Math.round(Style.style0 * Style.scaleHint)
        }
        Rectangle
        {
            id:id_PPCPosition
            color: ppcColor
            width:parent.width*(1.25)
            height:allPositionHeight
            anchors.top: id_StatusofHorn.top
            anchors.topMargin: dwPPCTextPosition*parent.height/rangeMaxValue
            border.color: ppcColor
            anchors.horizontalCenter: parent.horizontalCenter
            border.width: Math.round(2 * Style.scaleHint)
            radius: Math.round(5 * Style.scaleHint)
        }
        Text {
            id: id_PPCHornPositionVal
            text: dwPPCTextPosition+qmlTextdistanceUnit
            anchors.left: id_PPCPosition.right
            anchors.leftMargin:  Math.round(30 * Style.scaleHint)
            anchors.top: id_PPCPosition.top
            anchors.topMargin: Math.round(-29 * Style.scaleHint)
            color:fontColor
            font.family: fontfamily
            font.pixelSize:  Math.round(Style.style0 * Style.scaleHint)
        }
        Text {
            id: id_EPCHornPosition_text
            text: qmlTextEPC
            anchors.right: id_EPCPosition.left
            anchors.rightMargin:  Math.round(30 * Style.scaleHint)
            anchors.top: id_EPCPosition.top
            anchors.topMargin: Math.round(-18 * Style.scaleHint)
            color:fontColor
            font.family: fontfamily
            font.pixelSize:  Math.round(Style.style0 * Style.scaleHint)
        }
        Rectangle
        {
            id:id_EPCPosition
            color: epcColor
            width:parent.width*(1.25)
            height:allPositionHeight
            anchors.top: id_StatusofHorn.top
            anchors.topMargin: dwEPCTextPosition*parent.height/rangeMaxValue
            border.color: epcColor
            anchors.horizontalCenter: parent.horizontalCenter
            border.width: Math.round(2 * Style.scaleHint)
            radius: Math.round(5 * Style.scaleHint)
        }
        Text {
            id: id_EPCHornPositionVal
            text:dwEPCTextPosition+qmlTextdistanceUnit
            anchors.left: id_EPCPosition.right
            anchors.leftMargin:  Math.round(30 * Style.scaleHint)
            anchors.top: id_EPCPosition.top
            anchors.topMargin:  Math.round(-18 * Style.scaleHint)
            color:fontColor
            font.family: fontfamily
            font.pixelSize:  Math.round(Style.style0 * Style.scaleHint)
        }
        Text {
            id: id_MPHornPosition_text
            text: qmlTextMP
            anchors.right: id_MPPosition.left
            anchors.rightMargin: Math.round(30 * Style.scaleHint)
            anchors.top: id_MPPosition.top
            anchors.topMargin: Math.round(-10 * Style.scaleHint)
            color:fontColor
            font.family: fontfamily
            font.pixelSize:  Math.round(Style.style0 * Style.scaleHint)
        }
        Rectangle
        {
            id:id_MPPosition
            color: mpColor
            width:parent.width*(1.25)
            height:allPositionHeight
            anchors.top: id_StatusofHorn.top
            anchors.topMargin: dwMPTextPosition*parent.height/rangeMaxValue
            border.color: mpColor
            anchors.horizontalCenter: parent.horizontalCenter
            border.width: Math.round(2 * Style.scaleHint)
            radius: Math.round(5 * Style.scaleHint)
        }
        Text {
            id: id_MPHornPositionVal
            text: dwMPTextPosition+qmlTextdistanceUnit
            anchors.left: id_MPPosition.right
            anchors.leftMargin: Math.round(30 * Style.scaleHint)
            anchors.top: id_MPPosition.top
            anchors.topMargin: Math.round(-10 * Style.scaleHint)
            color:fontColor
            font.family: fontfamily
            font.pixelSize:  Math.round(Style.style0 * Style.scaleHint)
        }
        Text {
            id: id_FixtureHornPosition_text
            text: qmlTextFixture
            anchors.right: id_FixturePosition.left
            anchors.verticalCenter: id_FixturePosition.verticalCenter
            color:fontColor
            font.family: fontfamily
            font.pixelSize:  Math.round(Style.style0 * Style.scaleHint)
        }
        Rectangle
        {
            id:id_FixturePosition
            color: fixtureColor
            width:parent.width*(1.25)
            height:allPositionHeight
            anchors.top: id_StatusofHorn.bottom
            border.color: fixtureColor
            anchors.horizontalCenter: parent.horizontalCenter
            border.width: Math.round(2 * Style.scaleHint)
            radius: Math.round(5 * Style.scaleHint)
        }
        Text {
            id: id_strokeLength_text
            text:maxValue+qmlTextdistanceUnit
            anchors.left: id_FixturePosition.right
            anchors.verticalCenter: id_FixturePosition.verticalCenter
            color:fontColor
            anchors.leftMargin: Math.round(4 * Style.scaleHint)
            verticalAlignment: Text.AlignVCenter
            font.family: fontfamily
            font.pixelSize:  Math.round(Style.style0 * Style.scaleHint)
        }
    }
}

