import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtCharts 2.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
//import HB.GraphData 1.0
import HBAxisDefine 1.0
Item{
    readonly property int textWidth: 100
    readonly property int comboBoxWidth: 150
    readonly property int buttonWidth: 100
    readonly property int rowSpacing: 20
    readonly property int componentHeight: 30

    HBCalendar{
        id: calendarDate
        anchors.centerIn: parent
        width: Math.round(400 * Style.scaleHint)
        height: Math.round(250 * Style.scaleHint)
        z: 5
        visible: false
        onSelectedDateChanged: {
            console.debug("3333333333333: ", selectedDate)
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
                    id:comboBoxStartTimeStamp
                    width: Math.round(comboBoxWidth * Style.scaleHint)
                    height: parent.height
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
                    id:comboBoxFinishTimeStamp
                    width: Math.round(comboBoxWidth * Style.scaleHint)
                    height: parent.height
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
                        // controlLimitNumpad.visible = false
                        // weldGraphObj.loadHistoryCurve(depthLeftAxisPlot, "depth");
                        // weldGraphObj.loadHistoryCurve(velocityLeftAxisPlot, "velocity");
                        // weldGraphObj.loadHistoryCurve(tensionsLeftAxisPlot, "tensions");
                        // weldGraphObj.loadHistoryCurve(tensionIncrementLeftAxisPlot, "tension_increment");
//                        weldGraphObj.appendSamples(graphChartView.series(depthLeftPlotName), GraphAxisEnum.DEPTH_IDX);
                        console.log("开始时间: "+ comboBoxStartTimeStamp.text)
                         console.log("结束时间: "+ comboBoxFinishTimeStamp.text)
                    }
                }

                HBPrimaryButton
                {
                    id: buttonExport
                    width: Math.round(buttonWidth * Style.scaleHint)
                    height: Math.round(componentHeight * Style.scaleHint)
                    text: qsTr("导出")
                    onClicked:
                    {
                        // controlLimitNumpad.visible = false
                    }
                }
            }
        }



        Rectangle{
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.rightMargin: Math.round(10 * Style.scaleHint)
            anchors.topMargin:  Math.round(160 * Style.scaleHint)
            Item {
                id: depthChartVeiw
                width: parent.width/2
                HBChartView {
                    id: depthChart
                    width: Math.round(300 * Style.scaleHint)
                    height: Math.round(140 * Style.scaleHint)
                    anchors.centerIn: parent
                    isDepthLeftAxisVisible: true
                }
            }
            Item{
                width: parent.width
                height: Math.round(30 * Style.scaleHint)
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.rightMargin: Math.round(300 * Style.scaleHint)
                anchors.topMargin:  Math.round(170 * Style.scaleHint)
                anchors.left: parent.left
                Text {
                    anchors.centerIn: parent
                    font.family: "宋体"
                    font.pixelSize: Math.round(Math.round(Style.style0 * Style.scaleHint))
                    color: Style.whiteFontColor
                    text: qsTr("时间")

                }
            }

            Item{
                width: Math.round(30 * Style.scaleHint)
                height: parent.height
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: -Math.round(5 * Style.scaleHint)
                anchors.topMargin: Math.round(30*Style.scaleHint)
                rotation: -90
                Text {
                    anchors.centerIn: parent
                    font.family: "宋体"
                    font.pixelSize: Math.round(Math.round(Style.style0 *Style.scaleHint))
                    color: Style.whiteFontColor
                    text: qsTr("深度(m)")

                }
            }
        }

        Rectangle{
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: Math.round(430 * Style.scaleHint)
            anchors.topMargin:  Math.round(160 * Style.scaleHint)
            Item {
                id: velocityVeiw
                width: parent.width/2
                HBChartView {
                    id: velocityChart
                    width: Math.round(300 * Style.scaleHint)
                    height: Math.round(140 * Style.scaleHint)
                    anchors.centerIn: parent
                    isVelocityLeftAxisVisible: true

                }
            }
            Item{
                width: parent.width
                height: Math.round(30 * Style.scaleHint)
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.rightMargin: Math.round(130 * Style.scaleHint)
                anchors.topMargin:  Math.round(170 * Style.scaleHint)
                anchors.left: parent.left
                Text {
                    anchors.centerIn: parent
                    font.family: "宋体"
                    font.pixelSize: Math.round(Math.round(Style.style0 * Style.scaleHint))
                    color: Style.whiteFontColor
                    text: qsTr("时间")

                }
            }

            Item{
                width: Math.round(30 * Style.scaleHint)
                height: parent.height
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: -Math.round(110 * Style.scaleHint)
                anchors.topMargin: Math.round(30*Style.scaleHint)
                rotation: -90
                Text {
                    anchors.centerIn: parent
                    font.family: "宋体"
                    font.pixelSize: Math.round(Math.round(Style.style0 *Style.scaleHint))
                    color: Style.whiteFontColor
                    text: qsTr("速度(m/s)")

                }
            }
        }

        Rectangle{
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: Math.round(10 * Style.scaleHint)
            anchors.topMargin:  Math.round(305 * Style.scaleHint)
            Item {
                id: tensionVeiw
                width: parent.width/2
                HBChartView {
                    id: tensionChart
                    width: Math.round(300 * Style.scaleHint)
                    height: Math.round(140 * Style.scaleHint)
                    anchors.centerIn: parent
                    isTensionsLeftAxisVisible: true

                }
            }
            Item{
                width: parent.width
                height: Math.round(30 * Style.scaleHint)
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.rightMargin: Math.round(310 * Style.scaleHint)
                anchors.topMargin:  Math.round(320 * Style.scaleHint)
                anchors.left: parent.left
                Text {
                    anchors.centerIn: parent
                    font.family: "宋体"
                    font.pixelSize: Math.round(Math.round(Style.style0 * Style.scaleHint))
                    color: Style.whiteFontColor
                    text: qsTr("时间")

                }
            }

            Item{
                width: Math.round(30 * Style.scaleHint)
                height: parent.height
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: -Math.round(10 * Style.scaleHint)
                anchors.topMargin: Math.round(110*Style.scaleHint)
                rotation: -90
                Text {
                    anchors.centerIn: parent
                    font.family: "宋体"
                    font.pixelSize: Math.round(Math.round(Style.style0 *Style.scaleHint))
                    color: Style.whiteFontColor
                    text: qsTr("张力(N)")

                }
            }
        }

        Rectangle{
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: Math.round(430 * Style.scaleHint)
            anchors.topMargin:  Math.round(305 * Style.scaleHint)
            Item {
                id: tensionIncrementVeiw
                width: parent.width/2
                HBChartView {
                    id: tensionIncrementChart
                    width: Math.round(300 * Style.scaleHint)
                    height: Math.round(140 * Style.scaleHint)
                    anchors.centerIn: parent
                    isTensionIncrementLeftAxisVisible: true

                }
            }
            Item{
                width: parent.width
                height: Math.round(30 * Style.scaleHint)
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.rightMargin: Math.round(130 * Style.scaleHint)
                anchors.topMargin:  Math.round(320 * Style.scaleHint)
                anchors.left: parent.left
                Text {
                    anchors.centerIn: parent
                    font.family: "宋体"
                    font.pixelSize: Math.round(Math.round(Style.style0 * Style.scaleHint))
                    color: Style.whiteFontColor
                    text: qsTr("时间")

                }
            }

            Item{
                width: Math.round(30 * Style.scaleHint)
                height: parent.height
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: -Math.round(110 * Style.scaleHint)
                anchors.topMargin: Math.round(110*Style.scaleHint)
                rotation: -90
                Text {
                    anchors.centerIn: parent
                    font.family: "宋体"
                    font.pixelSize: Math.round(Math.round(Style.style0 *Style.scaleHint))
                    color: Style.whiteFontColor
                    text: qsTr("张力增量(m/s)")

                }
            }
        }

    }

}


