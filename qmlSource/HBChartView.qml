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
    property int fontsize: Math.round(Style.style0 * Style.scaleHint)
    property double timemax: 1

    readonly property string depthLeftPlotName:            qsTr("深度") + "(" + DepthGlobalDefine.distanceUnitModel[Depth.DistanceUnit] + ")"
    readonly property string velocityLeftPlotName:         qsTr("速度") + "(" + DepthGlobalDefine.velocityUnitModel[Depth.VelocityUnit] + ")"//qsTr("m/min")
    readonly property string tensionsLeftPlotName:         qsTr("张力") + "(" + TensionsGlobalDefine.tensionUnitModel[TensionSetting.TensionUnit] + ")"
    readonly property string tensionIncrementPlotName:     qsTr("张力增量") + "(" + TensionsGlobalDefine.tensionUnitModel[TensionSetting.TensionUnit] + ")"
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
        var timePoints, depthPoints, velocityPoints, tensionPoints, tensionDeltaPoints;
        timePoints = SensorGraphData.getDateTimes();
        depthPoints = SensorGraphData.getDepths();
        velocityPoints = SensorGraphData.getVelocitys();
        tensionPoints = SensorGraphData.getTensions();
        tensionDeltaPoints = SensorGraphData.getTensionDeltas();


        /* Update the Min and Max values */
        var axisMinValues = SensorGraphData.getAxisMinParameters();
        var axisMaxValues = SensorGraphData.getAxisMaxParameters();

        timeAxis.min = timePoints[0]
        depthLeftAxis.min               = axisMinValues[0];
        velocityLeftAxis.min            = axisMinValues[1]
        tensionsLeftAxis.min            = axisMinValues[2]
        tensionIncrementLeftAxis.min    = axisMinValues[3]

        timeAxis.max = timePoints[timePoints.length - 1]
        depthLeftAxis.max               = axisMaxValues[0];
        velocityLeftAxis.max            = axisMaxValues[1];
        tensionsLeftAxis.max            = axisMaxValues[2];
        tensionIncrementLeftAxis.max    = axisMaxValues[3];

        /* Rounding of axis values for proper representation */
        depthLeftAxis.max               = roundAxisValues(depthLeftAxis.max,            depthLeftAxis.min);
        velocityLeftAxis.max            = roundAxisValues(velocityLeftAxis.max,         velocityLeftAxis.min);
        tensionsLeftAxis.max            = roundAxisValues(tensionsLeftAxis.max,         tensionsLeftAxis.min);
        tensionIncrementLeftAxis.max    = roundAxisValues(tensionIncrementLeftAxis.max, tensionIncrementLeftAxis.min);
        // for(var i = 0; i < timePoints.length; i++)
        // {
        //     depthLeftAxisPlot.append(timePoints[i], depthPoints[i])
        //     velocityLeftAxisPlot.append(timePoints[i], velocityPoints[i])
        //     tensionsLeftAxisPlot.append(timePoints[i], tensionPoints[i])
        //     tensionIncrementLeftAxisPlot.append(timePoints[i], tensionDeltaPoints[i])
        // }
        SensorGraphData.replaceSeriesPoints(HBGraphAxisEnum.DEPTH_IDX,              graphChartView.series(depthLeftPlotName))
        SensorGraphData.replaceSeriesPoints(HBGraphAxisEnum.VELOCITY_IDX,           graphChartView.series(velocityLeftPlotName))
        SensorGraphData.replaceSeriesPoints(HBGraphAxisEnum.TENSIONS_IDX,           graphChartView.series(tensionsLeftPlotName))
        SensorGraphData.replaceSeriesPoints(HBGraphAxisEnum.TENSION_INCREMENT_IDX,  graphChartView.series(tensionIncrementPlotName))
    }

    function clearGraph()
    {
        depthLeftAxisPlot.clear()

        velocityLeftAxisPlot.clear()

        tensionsLeftAxisPlot.clear()

        tensionIncrementLeftAxisPlot.clear()
    }

    Rectangle
    {
        anchors.fill: parent
        color: "transparent"
        border.color: Style.backgroundMiddleColor
        ChartView {
            id: graphChartView
            legend.visible: true
            legend.color : Style.hbFrameBorderColor
            legend.font.family: "宋体"
            legend.font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
            legend.font.bold: true
            legend.labelColor : "#ffffff"
            anchors.fill: parent
            // property real deltaX: plotArea.width / (timeAxis.max - timeAxis.min)
            property real myWidth: 2
            backgroundColor: "transparent"
            transformOrigin: Item.Center

            DateTimeAxis {
                id: timeAxis
                color: HBAxisDefine.getAxisColor(HBGraphAxisEnum.TIME_IDX)
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
                format: "yyyy-MM-dd hh:mm:ss"
                max: new Date()
                min: new Date()
                tickCount: 5
            }

            ValueAxis {
                id: depthLeftAxis
                color: HBAxisDefine.getAxisColor(HBGraphAxisEnum.DEPTH_IDX)
                visible: isDepthLeftAxisVisible
                gridVisible: false
                labelsVisible: true
                labelsFont.family: "宋体"
                labelsFont.pixelSize: fontsize* 0.6
                labelsColor: HBAxisDefine.getAxisColor(HBGraphAxisEnum.DEPTH_IDX)
                lineVisible: true
                minorGridVisible: false
                titleText: HBAxisDefine.getAxisTitle(HBGraphAxisEnum.DEPTH_IDX)
                titleFont.family: "宋体"
                titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                titleVisible: false
                max: 200
                min: 0
                tickCount: 5
                labelFormat: "%.2f"
            }

            ValueAxis {
                id: velocityLeftAxis
                color: HBAxisDefine.getAxisColor(HBGraphAxisEnum.VELOCITY_IDX)
                visible: isVelocityLeftAxisVisible
                gridVisible: false
                labelsVisible: true
                labelsFont.family: "宋体"
                labelsFont.pixelSize: fontsize * 0.6
                labelsColor: HBAxisDefine.getAxisColor(HBGraphAxisEnum.VELOCITY_IDX)
                lineVisible: true
                minorGridVisible: false
                titleText: HBAxisDefine.getAxisTitle(HBGraphAxisEnum.VELOCITY_IDX)
                titleFont.family: "宋体"
                titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                titleVisible: false
                max: 200
                min: 0
                tickCount: 5
                labelFormat: "%.2f"
            }

            ValueAxis {
                id : tensionsLeftAxis
                color: HBAxisDefine.getAxisColor(HBGraphAxisEnum.TENSIONS_IDX)
                visible: isTensionsLeftAxisVisible
                gridVisible: false
                labelsVisible: true
                labelsFont.family: "宋体"
                labelsFont.pixelSize: fontsize * 0.6
                labelsColor: HBAxisDefine.getAxisColor(HBGraphAxisEnum.TENSIONS_IDX)
                lineVisible: true
                minorGridVisible: false
                titleText: HBAxisDefine.getAxisTitle(HBGraphAxisEnum.TENSIONS_IDX)
                titleFont.family: "宋体"
                titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                titleVisible: false
                max: 100
                min: 0
                tickCount: 5
                labelFormat: "%.2f"
            }

            ValueAxis {
                id: tensionIncrementLeftAxis
                color: HBAxisDefine.getAxisColor(HBGraphAxisEnum.TENSION_INCREMENT_IDX)
                visible: isTensionIncrementLeftAxisVisible
                gridVisible: false
                labelsVisible: true
                labelsFont.family: "宋体"
                labelsFont.pixelSize: fontsize  * 0.6
                labelsColor: HBAxisDefine.getAxisColor(HBGraphAxisEnum.TENSION_INCREMENT_IDX)
                lineVisible: true
                minorGridVisible: false
                titleText: HBAxisDefine.getAxisTitle(HBGraphAxisEnum.TENSION_INCREMENT_IDX)
                titleFont.family: "宋体"
                titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                titleVisible: false
                labelFormat: "%.2f"
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
                pointsVisible: false
            }

            LineSeries{
                id: velocityLeftAxisPlot
                width: graphChartView.myWidth
                color: HBAxisDefine.getAxisColor(HBGraphAxisEnum.VELOCITY_IDX)
                name: velocityLeftPlotName
                axisX: timeAxis
                axisY: velocityLeftAxis
                visible: isVelocityLeftAxisVisible
                pointsVisible: false
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
                pointsVisible: false
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
                pointsVisible: false
                useOpenGL: true
            }
        }
    }
}
