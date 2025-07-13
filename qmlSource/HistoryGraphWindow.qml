import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtCharts 2.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import HBAxisDefine 1.0
Item{
    readonly property int textWidth: 100
    readonly property int comboBoxWidth: 150
    readonly property int buttonWidth: 100
    readonly property int rowSpacing: 20
    readonly property int componentHeight: 30

    Connections{
        target: SensorGraphData
        function onIsDataReady()
        {
            depthChart.plotGraph()
        }
    }

    Component.onCompleted:
    {
        var startStamp = comboBoxStartTimeStamp.text + "T00:00:00"
        var endStamp = comboBoxFinishTimeStamp.text + "T23:59:59"
        SensorGraphData.loadSensorGraphPoint(startStamp, endStamp)
    }

    HBCalendar{
        id: calendarDate
        anchors.centerIn: parent
        width: Math.round(400 * Style.scaleHint)
        height: Math.round(250 * Style.scaleHint)
        z: 5
        visible: false
        onSelectedDateChanged: {
            console.debug("selected Date: ", selectedDate)
        }
    }

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
    HBGroupBox
    {
        id: info
        title: qsTr("信息")
        anchors.top: parent.top
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
        width: parent.width - Math.round(10 * Style.scaleHint)
        height: parent.height / 3 - Math.round(40 * Style.scaleHint)
        backgroundColor: Style.backgroundLightColor
        Grid
        {
            id: argumentLayout
            columns: 2
            rows: 2
            columnSpacing: Math.round(80 * Style.scaleHint)
            rowSpacing: Math.round(10 * Style.scaleHint)
            width: Math.round((textWidth + rowSpacing + comboBoxWidth) * 2 * Style.scaleHint) + argumentLayout.columnSpacing
            height: Math.round((componentHeight * 2) * Style.scaleHint) + argumentLayout.rowSpacing
            anchors.left: parent.left
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter

            Row{
                spacing: Math.round(rowSpacing * Style.scaleHint)
                height: Math.round(componentHeight * Style.scaleHint)
                width: Math.round((textWidth + rowSpacing + comboBoxWidth) * Style.scaleHint)
                Text {
                    id: titleStartTimeStamp
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("开始时间") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBComboBoxCalendar
                {
                    id: comboBoxStartTimeStamp
                    width: Math.round(comboBoxWidth * Style.scaleHint)
                    height: parent.height
                    text: {
                        var now = new Date()
                        var yesterday = new Date(now.getTime() - 24 * 60 * 60 * 1000)
                        return Qt.formatDate(yesterday, "yyyy-MM-dd")
                    }

                    onSignalPopUp:
                    {
                        if(isShow === true)
                            calendarDate.visible = true
                        else
                        {
                            calendarDate.visible = false
                            comboBoxStartTimeStamp.text = Qt.formatDate(calendarDate.selectedDate, "yyyy-MM-dd")
                        }
                    }
                }
            }

            Row{
                spacing: Math.round(rowSpacing * Style.scaleHint)
                height: Math.round(componentHeight * Style.scaleHint)
                width: Math.round((textWidth + rowSpacing + comboBoxWidth) * Style.scaleHint)
                Text {
                    id: titleFinishTimeStamp
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("结束时间") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }

                HBComboBoxCalendar
                {
                    id: comboBoxFinishTimeStamp
                    width: Math.round(comboBoxWidth * Style.scaleHint)
                    height: parent.height
                    text: {
                        var now = new Date()
                        return Qt.formatDate(now, "yyyy-MM-dd")
                    }
                    onSignalPopUp:
                    {
                        if(isShow === true)
                            calendarDate.visible = true
                        else
                        {
                            calendarDate.visible = false
                            comboBoxFinishTimeStamp.text = Qt.formatDate(calendarDate.selectedDate, "yyyy-MM-dd")
                        }
                    }
                }
            }

            Row{
                spacing: Math.round(rowSpacing * Style.scaleHint)
                height: Math.round(componentHeight * Style.scaleHint)
                width: Math.round((buttonWidth + rowSpacing + buttonWidth) * Style.scaleHint)
                HBPrimaryButton
                {
                    id: buttonInquire
                    width: Math.round(buttonWidth * Style.scaleHint)
                    height: Math.round(componentHeight * Style.scaleHint)
                    text: qsTr("查询")
                    onClicked:
                    {
                        var startStamp = comboBoxStartTimeStamp.text + "T00:00:00"
                        var endStamp   = comboBoxFinishTimeStamp.text + "T23:59:59"
                        SensorGraphData.loadSensorGraphPoint(startStamp, endStamp)
                    }
                }

                HBPrimaryButton
                {
                    id: buttonExport
                    width: Math.round(buttonWidth * Style.scaleHint)
                    height: Math.round(componentHeight * Style.scaleHint)
                    text: qsTr("导出")
                    visible: false
                    onClicked:
                    {
                        SensorGraphData.exportData()
                        mainWindow.showDialogScreen(qsTr("导出数据已完成"), Dialog.Ok, function(val){
                            console.debug("Dialog Function Callback")
                        })
                    }
                }
            }
        }
    }

    Item{
        anchors.top: info.bottom
        // anchors.topMargin: Math.round(Style.scaleHint * -10)
        anchors.bottom: parent.bottom
        anchors.right: info.right
        anchors.left: info.left
        HBChartView {
            id: depthChart
            anchors.fill: parent
            isDepthLeftAxisVisible: true
            isVelocityLeftAxisVisible: true
            isTensionsLeftAxisVisible: true
            isTensionIncrementLeftAxisVisible: true
        }
        Item{
            width: parent.width
            height: Math.round(30 * Style.scaleHint)
            anchors.bottom: depthChart.bottom
            anchors.left: depthChart.left
            Text {
                anchors.centerIn: parent
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                color: Style.whiteFontColor
                text: qsTr("时间")
            }
        }
    }
}


