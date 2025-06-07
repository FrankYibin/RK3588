/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 xxxxx

 **********************************************************************************************************/
import QtQuick 2.0
import QtCharts 2.15
import QtQuick.Controls 2.2
import Style 1.0
import HBAxisDefine 1.0
import Com.Branson.HBGraphAxisEnum 1.0
import TensionsGlobalDefine 1.0
Item {
    id: weldGraph
    property bool flagDragDrop: false
    property bool isNormalScreen: true
    property int fontsize: Math.round(Style.style3 * Style.scaleHint)

    readonly property string tensionsLeftPlotName:  "tensionsLeftPlot"
    readonly property string qmltextSecUnit:        "s"

    /**
    *@breif: Rounding of axis values for proper representation
    **/
    function roundAxisValues(axisMaximumVal, axisMinimumVal)
    {
        var ind = 0 ;
        var tmpValues;
        var reminder;
        var retVal = 0 ;

        tmpValues = axisMaximumVal - axisMinimumVal;
        reminder = (tmpValues % 10)

        if(reminder !== 0 )
        {
            retVal = axisMaximumVal + (10 - reminder);
        }
        else
        {
            retVal = axisMaximumVal ;
        }
        return retVal ;
    }

    /**
    *@breif: Plots the graph
    **/
    function plotGraph()
    {
        clearGraph()

        // weldGraphObj.appendSamples(graphChartView.series(collapseDistLeftPlotName), GraphAxisEnum.COLLAPSEDIST_IDX);
        tensionLeftAxisPlot.append(10, 0.5)
        tensionLeftAxisPlot.append(20, 1.0)
        tensionLeftAxisPlot.append(30, 1.5)
        tensionLeftAxisPlot.append(40, 2.0)
        tensionLeftAxisPlot.append(50, 2.5)
        tensionLeftAxisPlot.append(60, 3.0)


        /* Update the Min and Max values */
        // var axisMinValues = weldGraphObj.getAxisMinParameters();
        // var axisMaxValues = weldGraphObj.getAxisMaxParameters();
        var axisMinValues = [0, 0]
        var axisMaxValues = [60, 3.0]
        scaleAxis.min                    = axisMinValues[0];
        tensionLeftAxis.min              = axisMinValues[1];

        scaleAxis.max                    = axisMaxValues[0];
        tensionLeftAxis.max               = axisMaxValues[1];


        /* Rounding of axis values for proper representation */
        scaleAxis.max               = roundAxisValues(scaleAxis.max,            scaleAxis.min);
    }

    function clearGraph()
    {
        tensionLeftAxisPlot.clear()
    }

    Component.onCompleted: {
        plotGraph()

    }

    Rectangle
    {
        anchors.fill: parent
        color: "transparent"
        border.color: Style.hbFrameBorderColor
        ChartView {
            id: graphChartView
            legend.visible: true
            legend.color : Style.hbFrameBorderColor
            legend.font.family: "宋体"
            legend.font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            legend.font.bold: true
            legend.labelColor : "#ffffff"
            anchors.top: parent.top
            anchors.topMargin: Math.round(10  * Style.scaleHint)
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right

            property real myWidth: 2

            backgroundColor: "transparent"
            transformOrigin: Item.Center

            ValueAxis {
                id: scaleAxis
                color: "#ffffff"
                gridVisible: false
                labelsVisible: true
                labelsFont.family: "宋体"
                labelsFont.pixelSize: fontsize
                labelsColor: Style.whiteFontColor
                lineVisible: true
                minorGridVisible: false
                titleText: qsTr("刻度值")
                titleFont.family: "宋体"
                titleFont.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                titleVisible: false
                labelFormat: "%d"
                max: 100
                min: 0
                tickCount: 7
            }

            ValueAxis {
                id: tensionLeftAxis
                color: "#ffffff"
                visible: true
                gridVisible: false
                labelsVisible: true
                labelsFont.family: "宋体"
                labelsFont.pixelSize: fontsize
                labelsColor: Style.whiteFontColor
                lineVisible: true
                minorGridVisible: false
                titleText: ""
                titleFont.family: "宋体"
                titleFont.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                titleVisible: false
                max: 10
                min: 0
                tickCount: 7
                labelFormat: "%.1f"
            }

            LineSeries{
                id: tensionLeftAxisPlot
                width: graphChartView.myWidth
                name: qsTr("张力 Vs 距离")
                axisX: scaleAxis
                axisY: tensionLeftAxis
                color: Style.hbFrameBorderColor
                visible: true
                useOpenGL: false
                pointsVisible: true
            }

        }
        Item{
            width: parent.width
            height: Math.round(30 * Style.scaleHint)
            anchors.top: parent.top
            anchors.left: parent.left
            Text {
                anchors.centerIn: parent
                font.family: "宋体"
                font.pixelSize: Math.round(Math.round(Style.style4 * Style.scaleHint))
                color: Style.whiteFontColor
                text: qsTr("张力与刻度值关系图")
            }
        }
        Item{
            width: parent.width
            height: Math.round(30 * Style.scaleHint)
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            Text {
                anchors.centerIn: parent
                font.family: "宋体"
                font.pixelSize: Math.round(Math.round(Style.style3 * Style.scaleHint))
                color: Style.whiteFontColor
                text: qsTr("刻度值")
            }
        }

        Item{
            width: Math.round(30 * Style.scaleHint)
            height: parent.height
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: -Math.round(5 * Style.scaleHint)
            rotation: -90
            Text {
                anchors.centerIn: parent
                font.family: "宋体"
                font.pixelSize: Math.round(Math.round(Style.style3 * Style.scaleHint))
                color: Style.whiteFontColor
                text: qsTr("张力") + "(" + TensionsGlobalDefine.tensionUnitModel[TensionSetting.TensionUnit] + ")" // 竖排显示
            }
        }


    }


}
