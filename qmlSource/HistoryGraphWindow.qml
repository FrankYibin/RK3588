import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtCharts 2.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import HB.GraphData 1.0
Item{
    readonly property int textWidth: 100
    readonly property int comboBoxWidth: 150
    readonly property int buttonWidth: 100
    readonly property int rowSpacing: 20
    readonly property int componentHeight: 30
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
                HBComboBox
                {
                    id:comboBoxStartTimeStamp
                    width: Math.round(comboBoxWidth * Style.scaleHint)
                    height: parent.height
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
                HBComboBox
                {
                    id:comboBoxFinishTimeStamp
                    width: Math.round(comboBoxWidth * Style.scaleHint)
                    height: parent.height
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
                        weldGraphObj.appendSamples(graphChartView.series(depthLeftPlotName), GraphAxisEnum.DEPTH_IDX);
                    }
                }

                HBPrimaryButton
                {
                    id: buttonExport
                    width: Math.round(buttonWidth * Style.scaleHint)
                    height: Math.round(componentHeight * Style.scaleHint)
                    text: qsTr("导出选中")
                    onClicked:
                    {
                        // controlLimitNumpad.visible = false
                    }
                }
            }
        }

    }

    HBCalendar{
        id: calendarDate
        anchors.centerIn: parent
        width: Math.round(400 * Style.scaleHint)
        height: Math.round(250 * Style.scaleHint)
        visible: false
        onSelectedDateChanged: {
            console.debug("3333333333333: ", selectedDate)
        }
    }

}


