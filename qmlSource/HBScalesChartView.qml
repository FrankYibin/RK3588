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
Item {
    id: weldGraph
    property bool flagDragDrop: false
    property bool isNormalScreen: true
    property int fontsize: Math.round(Style.style1 * Style.scaleHint)
    property double timemax: 1

    readonly property string depthLeftPlotName:             "depthLeftPlot"
    readonly property string velocityLeftPlotName:          "velocityLeftPlot"
    readonly property string tensionsLeftPlotName:          "tensionsLeftPlot"
    readonly property string tensionIncrementPlotName:      "tensionIncrementLeftPlot"
    readonly property string qmltextSecUnit:                "s"

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
        var tensionPoint

        weldGraphObj.appendSamples(graphChartView.series(collapseDistLeftPlotName), GraphAxisEnum.COLLAPSEDIST_IDX);


        /* Update the Min and Max values */
        var axisMinValues = weldGraphObj.getAxisMinParameters();
        var axisMaxValues = weldGraphObj.getAxisMaxParameters();
        timeAxis.min                    = axisMinValues[HBGraphAxisEnum.TIME_IDX];
        depthLeftAxis.min               = axisMinValues[HBGraphAxisEnum.DEPTH_IDX];
        velocityLeftAxis.min            = axisMinValues[HBGraphAxisEnum.VELOCITY_IDX]
        tensionsLeftAxisPlot.min        = axisMinValues[HBGraphAxisEnum.TENSIONS_IDX]
        tensionIncrementLeftAxis.min    = axisMinValues[HBGraphAxisEnum.TENSION_INCREMENT_IDX]

        timeAxis.max                    = axisMaxValues[HBGraphAxisEnum.TIME_IDX];
        depthLeftAxis.max               = axisMaxValues[HBGraphAxisEnum.DEPTH_IDX];
        velocityLeftAxis.max            = axisMaxValues[HBGraphAxisEnum.VELOCITY_IDX];
        tensionsLeftAxisPlot.max        = axisMaxValues[HBGraphAxisEnum.TENSIONS_IDX];
        tensionIncrementLeftAxis.max    = axisMaxValues[HBGraphAxisEnum.TENSION_INCREMENT_IDX];

        /* Rounding of axis values for proper representation */
        // timeAxis.max                    = roundAxisValues(timeAxis.max,                 timeAxis.min);
        depthLeftAxis.max               = roundAxisValues(depthLeftAxis.max,            depthLeftAxis.min);
        velocityLeftAxis.max            = roundAxisValues(velocityLeftAxis.max,         velocityLeftAxis.min);
        tensionsLeftAxisPlot.max        = roundAxisValues(tensionsLeftAxisPlot.max,     tensionsLeftAxisPlot.min);
        tensionIncrementLeftAxis.max    = roundAxisValues(tensionIncrementLeftAxis.max, tensionIncrementLeftAxis.min);
    }

    function clearGraph()
    {
        timeAxis.min = 0;
        timeAxis.max = timemax;

        depthLeftAxisPlot.clear()
    }

    Rectangle {
        id: graphFrame
        anchors.fill: parent
        color: "transparent"
        ScrollView{
            id:cotaingraphChartView
            width: parent.width
            height: parent.height
            clip: true
            ChartView {
                id: graphChartView
                legend.visible: false
                margins.top: Math.round(10  * Style.scaleHint)
                margins.right: 0
                margins.left: 0
                margins.bottom: 0
                // property real deltaX: plotArea.width / (timeAxis.max - timeAxis.min)
                property real myWidth: 1
//                plotAreaColor: "red"
                width: parent.width
                height: parent.height
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
                    titleVisible: true
                    labelFormat: "%d"
                    max: timemax
                    min: 0
                    tickCount: 6
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
                    titleText: qsTr("张力(kg)")
                    titleFont.family: "宋体"
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    max: 10
                    min: 0
                    tickCount: 6
                    labelFormat: "%.1f"
                }

                LineSeries{
                    id: depthLeftAxisPlot
                    width: graphChartView.myWidth
                    name: depthLeftPlotName
                    axisX: timeAxis
                    axisY: depthLeftAxis
                    color: HBAxisDefine.getAxisColor(HBGraphAxisEnum.DEPTH_IDX)
                    visible: isDepthLeftAxisVisible
                    useOpenGL: true
                    pointsVisible: true
                }

            }
        }
    }
}
