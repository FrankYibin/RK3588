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
import HB.GraphData 1.0
Item {
    id: weldGraph
    property bool flagDragDrop: false
    property bool isNormalScreen: true
    property int fontsize: isNormalScreen === true ? Math.round(Style.style1 * Style.scaleHint) : Math.round(Style.style4 * Style.scaleHint)
    property double timemax: 1

    readonly property string depthLeftPlotName:            qsTr("深度（m）")
    readonly property string velocityLeftPlotName:         qsTr("速度（m/s）")
    readonly property string tensionsLeftPlotName:         qsTr("张力（N）")
    readonly property string tensionIncrementPlotName:     qsTr("张力增量（N）")
    readonly property string qmltextSecUnit:                "s"

    /*Whether the axis controls the coordinate display*/
    property bool isDepthLeftAxisVisible:              false
    property bool isVelocityLeftAxisVisible:           false
    property bool isTensionsLeftAxisVisible:           false
    property bool isTensionIncrementLeftAxisVisible:   false


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
        var depthPoint, velocityPoint , tensionsPoint, tensionIncrementPoint;

        if(isFreqLeftAxisVisible === true)
            SensorGraphData.appendSamples(graphChartView.series(depthLeftPlotName), HBGraphAxisEnum.DEPTH_IDX);
        if(isPowerLeftAxisVisible === true)
            SensorGraphData.appendSamples(graphChartView.series(velocityLeftPlotName), HBGraphAxisEnum.VELOCITY_IDX);
        if(isAmpLeftAxisVisible === true)
            SensorGraphData.appendSamples(graphChartView.series(tensionsLeftPlotName), HBGraphAxisEnum.TENSIONS_IDX);
        if(isEnergyLeftAxisVisible === true)
            SensorGraphData.appendSamples(graphChartView.series(tensionIncrementPlotName), HBGraphAxisEnum.TENSION_INCREMENT_IDX);


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

        velocityLeftAxisPlot.clear()

        tensionsLeftAxisPlot.clear()

        tensionIncrementLeftAxisPlot.clear()
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
                backgroundColor: "transparent"
                legend.visible: true
                legend.color : Style.hbFrameBorderColor
                legend.font.family: "宋体"
                legend.font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                legend.font.bold: true
                legend.labelColor : "#ffffff"
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
                    id: timeAxis
                    color: "#ffffff"
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: "宋体"
                    labelsFont.pixelSize: fontsize
                    labelsColor: HBAxisDefine.getAxisColor(HBGraphAxisEnum.TIME_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: HBAxisDefine.getAxisTitle(HBGraphAxisEnum.TIME_IDX)
                    titleFont.family: "宋体"
                    titleFont.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    titleVisible: false
                    labelFormat: "yyyy-MM-dd hh:mm:ss"
                    max: timemax
                    min: 0
                    tickCount: 9
                }

                ValueAxis {
                    id: depthLeftAxis
                    color: "#ffffff"
                    visible: isDepthLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: "宋体"
                    labelsFont.pixelSize: fontsize* 0.6
                    // labelsColor: HBAxisDefine.getAxisColor(HBGraphAxisEnum.DEPTH_IDX)
                    labelsColor:"#ffffff"
                    lineVisible: true
                    minorGridVisible: false
                    titleText: HBAxisDefine.getAxisTitle(HBGraphAxisEnum.DEPTH_IDX)
                    titleFont.family: "宋体"
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    max: 200
                    min: 0
                    tickCount: 5
                    labelFormat: "%.1f"
                }

                ValueAxis {
                    id: velocityLeftAxis
                    color: HBAxisDefine.getAxisColor(HBGraphAxisEnum.VELOCITY_IDX)
                    visible: isVelocityLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: "宋体"
                    labelsFont.pixelSize: fontsize * 0.6
                    // labelsColor: HBAxisDefine.getAxisColor(HBGraphAxisEnum.VELOCITY_IDX)
                    labelsColor:"#ffffff"
                    lineVisible: true
                    minorGridVisible: false
                    titleText: HBAxisDefine.getAxisTitle(HBGraphAxisEnum.VELOCITY_IDX)
                    titleFont.family: "宋体"
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    max: 200
                    min: 0
                    tickCount: 5
                    labelFormat: "%.1f"
                }

                ValueAxis {
                    id : tensionsLeftAxis
                    color: HBAxisDefine.getAxisColor(HBGraphAxisEnum.TENSIONS_IDX)
                    visible: isTensionsLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: "宋体"
                    labelsFont.pixelSize: fontsize * 0.6
                    // labelsColor: HBAxisDefine.getAxisColor(HBGraphAxisEnum.TENSIONS_IDX)
                    labelsColor:"#ffffff"
                    lineVisible: true
                    minorGridVisible: false
                    titleText: HBAxisDefine.getAxisTitle(HBGraphAxisEnum.TENSIONS_IDX)
                    titleFont.family: "宋体"
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    max: 100
                    min: 0
                    tickCount: 5
                    labelFormat: "%d"
                }

                ValueAxis {
                    id: tensionIncrementLeftAxis
                    color: HBAxisDefine.getAxisColor(HBGraphAxisEnum.TENSION_INCREMENT_IDX)
                    visible: isTensionIncrementLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: "宋体"
                    labelsFont.pixelSize: fontsize  * 0.6
                    // labelsColor: HBAxisDefine.getAxisColor(HBGraphAxisEnum.TENSION_INCREMENT_IDX)
                    labelsColor:"#ffffff"
                    lineVisible: true
                    minorGridVisible: false
                    titleText: HBAxisDefine.getAxisTitle(HBGraphAxisEnum.TENSION_INCREMENT_IDX)
                    titleFont.family: "宋体"
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    labelFormat: "%.3f"
                    max: 5
                    min:0
                    tickCount: 5
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

                LineSeries{
                    id: velocityLeftAxisPlot
                    width: graphChartView.myWidth
                    color: HBAxisDefine.getAxisColor(HBGraphAxisEnum.VELOCITY_IDX)
                    name: velocityLeftPlotName
                    axisX: timeAxis
                    axisY: velocityLeftAxis
                    visible: isVelocityLeftAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                LineSeries{
                    id: tensionsLeftAxisPlot
                    width: graphChartView.myWidth
                    color: HBAxisDefine.getAxisColor(HBGraphAxisEnum.TENSIONS_IDX)
                    name: tensionsLeftPlotName
                    axisX: timeAxis
                    axisY: tensionsLeftAxis
                    visible: isTensionsLeftAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                LineSeries{
                    id: tensionIncrementLeftAxisPlot
                    width: graphChartView.myWidth
                    name: tensionIncrementPlotName
                    axisX: timeAxis
                    axisY: tensionIncrementLeftAxis
                    color: HBAxisDefine.getAxisColor(HBGraphAxisEnum.TENSION_INCREMENT_IDX)
                    visible: isTensionIncrementLeftAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }
            }
        }
    }

}
