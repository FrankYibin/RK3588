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
import AxisDefine 1.0
import Com.Branson.GraphAxisEnum 1.0
Item {
    id: weldGraph
    property bool flagDragDrop: false
    property bool isNormalScreen: true
    property int fontsize: isNormalScreen === true ? Math.round(Style.style1 * Style.scaleHint) : Math.round(Style.style4 * Style.scaleHint)
    property double timemax: 1
//    property string qmltextPhaseAxis:              "Phase(Deg)"
//    property string qmltextEnergyAxis:             "Energy(J)"
//    property string qmltextFreqAxis:               "Freq(Hz)"
//    property string qmltextAmpAxis:                "Amp(%)"
//    property string qmltextCurrentAxis:            "Current(%)"
//    property string qmltextPowerAxis:              "Power(%)"
//    property string qmltextForceAxis:              "Force(N)"
//    property string qmltextVelocityAxis:           "Velocity(mm/s)"
//    property string qmltextAbsoluteDistanceAxis:   "Absolute Distance(mm)"
//    property string qmltextCollapseDistanceAxis:   "Collapse Distance(mm)"
//    property string qmltextTimeAxis:               "Time(s)"

    readonly property string energyLeftPlotName:            "energyLeftPlot"
    readonly property string energyRightPlotName:           "energyRightPlot"
    readonly property string ampLeftPlotName:               "ampLeftPlot"
    readonly property string ampRightPlotName:              "ampRightPlot"
    readonly property string currentLeftPlotName:           "currentLeftPlot"
    readonly property string currentRightPlotName:          "currentRightPlot"
    readonly property string powerLeftPlotName:             "powerLeftPlot"
    readonly property string powerRightPlotName:            "powerRightPlot"
    readonly property string phaseLeftPlotName:             "phaseLeftPlot"
    readonly property string phaseRightPlotName:            "phaseRightPlot"
    readonly property string forceLeftPlotName:             "forceLeftPlot"
    readonly property string forceRightPlotName:            "forceRightPlot"
    readonly property string velocityLeftPlotName:          "velocityLeftPlot"
    readonly property string velocityRightPlotName:         "velocityRightPlot"
    readonly property string absoluteDistLeftPlotName:      "absoluteDistLeftPlot"
    readonly property string absoluteDistRightPlotName:     "absoluteDistRightPlot"
    readonly property string collapseDistLeftPlotName:      "collapseDistLeftPlot"
    readonly property string collapseDistRightPlotName:     "collapseDistRightPlot"
    readonly property string freqLeftPlotName:              "freqLeftPlot"
    readonly property string freqRightPlotName:             "freqRightPlot"
    readonly property string qmltextPhase0Plot:             "phase0Plot"
    readonly property string qmltextSecUnit:                "s"

    /*Whether the axis controls the coordinate display*/
    property bool isPhaseLeftAxisVisible:          true
    property bool isEnergyLeftAxisVisible:         false
    property bool isFreqLeftAxisVisible:           false
    property bool isCurrentLeftAxisVisible:        false
    property bool isForceLeftAxisVisible:          false
    property bool isVelocityLeftAxisVisible:       false
    property bool isAbsoluteDistLeftAxisVisible:   false
    property bool isCollapseDistLeftAxisVisible:   false
    property bool isAmpLeftAxisVisible:            false
    property bool isPowerLeftAxisVisible:          false

    property bool isPhaseRightAxisVisible:         true
    property bool isEnergyRightAxisVisible:        false
    property bool isFreqRightAxisVisible:          false
    property bool isCurrentRightAxisVisible:       false
    property bool isForceRightAxisVisible:         false
    property bool isVelocityRightAxisVisible:      false
    property bool isAbsoluteDistRightAxisVisible:  false
    property bool isCollapseDistRightAxisVisible:  false
    property bool isAmpRightAxisVisible:           false
    property bool isPowerRightAxisVisible:         false

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
        var tmpPoint, timePoint , powerPoint, freqPoint, energyPoint, ampPoint;

        if(isFreqLeftAxisVisible === true)
            weldGraphObj.appendSamples(graphChartView.series(freqLeftPlotName), GraphAxisEnum.FREQ_IDX);
        if(isPowerLeftAxisVisible === true)
            weldGraphObj.appendSamples(graphChartView.series(powerLeftPlotName), GraphAxisEnum.POWER_IDX);
        if(isAmpLeftAxisVisible === true)
            weldGraphObj.appendSamples(graphChartView.series(ampLeftPlotName), GraphAxisEnum.AMP_IDX);
        if(isEnergyLeftAxisVisible === true)
            weldGraphObj.appendSamples(graphChartView.series(energyLeftPlotName), GraphAxisEnum.ENERGY_IDX);
        if(isCurrentLeftAxisVisible === true)
            weldGraphObj.appendSamples(graphChartView.series(currentLeftPlotName), GraphAxisEnum.CURRENT_IDX);
        if(isPhaseLeftAxisVisible === true)
            weldGraphObj.appendSamples(graphChartView.series(phaseLeftPlotName), GraphAxisEnum.PHASE_IDX);
        if(isForceLeftAxisVisible === true)
            weldGraphObj.appendSamples(graphChartView.series(forceLeftPlotName), GraphAxisEnum.FORCE_IDX);
        if(isVelocityLeftAxisVisible === true)
            weldGraphObj.appendSamples(graphChartView.series(velocityLeftPlotName), GraphAxisEnum.VELOCITY_IDX);
        if(isAbsoluteDistLeftAxisVisible === true)
            weldGraphObj.appendSamples(graphChartView.series(absoluteDistLeftPlotName), GraphAxisEnum.ABSOLUTEDIST_IDX);
        if(isCollapseDistLeftAxisVisible === true)
            weldGraphObj.appendSamples(graphChartView.series(collapseDistLeftPlotName), GraphAxisEnum.COLLAPSEDIST_IDX);

        if(isFreqRightAxisVisible === true)
            weldGraphObj.appendSamples(graphChartView.series(freqRightPlotName), GraphAxisEnum.FREQ_IDX);
        if(isPowerRightAxisVisible === true)
            weldGraphObj.appendSamples(graphChartView.series(powerRightPlotName), GraphAxisEnum.POWER_IDX);
        if(isAmpRightAxisVisible === true)
            weldGraphObj.appendSamples(graphChartView.series(ampRightPlotName), GraphAxisEnum.AMP_IDX);
        if(isEnergyRightAxisVisible === true)
            weldGraphObj.appendSamples(graphChartView.series(energyRightPlotName), GraphAxisEnum.ENERGY_IDX);
        if(isCurrentRightAxisVisible === true)
            weldGraphObj.appendSamples(graphChartView.series(currentRightPlotName), GraphAxisEnum.CURRENT_IDX);
        if(isPhaseRightAxisVisible === true)
            weldGraphObj.appendSamples(graphChartView.series(phaseRightPlotName), GraphAxisEnum.PHASE_IDX);
        if(isForceRightAxisVisible === true)
            weldGraphObj.appendSamples(graphChartView.series(forceRightPlotName), GraphAxisEnum.FORCE_IDX);
        if(isVelocityRightAxisVisible === true)
            weldGraphObj.appendSamples(graphChartView.series(velocityRightPlotName), GraphAxisEnum.VELOCITY_IDX);
        if(isAbsoluteDistRightAxisVisible === true)
            weldGraphObj.appendSamples(graphChartView.series(absoluteDistRightPlotName), GraphAxisEnum.ABSOLUTEDIST_IDX);
        if(isCollapseDistRightAxisVisible === true)
            weldGraphObj.appendSamples(graphChartView.series(collapseDistRightPlotName), GraphAxisEnum.COLLAPSEDIST_IDX);

        /* Update the Min and Max values */
        var axisMinValues = weldGraphObj.getAxisMinParameters();
        var axisMaxValues = weldGraphObj.getAxisMaxParameters();
        timeAxis.min                = 0;
        freqLeftAxis.min            = freqRightAxis.min             = axisMinValues[GraphAxisEnum.FREQ_IDX] - 100;
        phaseLeftAxis.min           = phaseRightAxis.min            = -180
        ampLeftAxis.min             = ampRightAxis.min              = 0
        currentLeftAxis.min         = currentRightAxis.min          = 0
        powerLeftAxis.min           = powerRightAxis.min            = Math.max(0, axisMinValues[GraphAxisEnum.POWER_IDX]);
        energyLeftAxis.min          = energyRightAxis.min           = Math.max(0, (axisMinValues[GraphAxisEnum.ENERGY_IDX] - 2));
        forceLeftAxis.min           = forceRightAxis.min            = Math.max(0, (axisMinValues[GraphAxisEnum.FORCE_IDX] - 2));
        velocityLeftAxis.min        = velocityRightAxis.min         = Math.max(0, (axisMinValues[GraphAxisEnum.VELOCITY_IDX] - 2));
        absoluteDistLeftAxis.min    = absoluteDistRightAxis.min     = Math.max(0, (axisMinValues[GraphAxisEnum.ABSOLUTEDIST_IDX] - 2));
        collapseDistLeftAxis.min    = collapseDistRightAxis.min     = axisMinValues[GraphAxisEnum.COLLAPSEDIST_IDX] - 1;

        timeAxis.max                = timemax;
        freqLeftAxis.max            = freqRightAxis.max             = axisMaxValues[GraphAxisEnum.FREQ_IDX] + 100;
        phaseLeftAxis.max           = phaseRightAxis.max            = 180
        ampLeftAxis.max             = ampRightAxis.max              = 120
        currentLeftAxis.max         = currentRightAxis.max          = 120
        powerLeftAxis.max           = powerRightAxis.max            = axisMaxValues[GraphAxisEnum.POWER_IDX] + 1;
        energyLeftAxis.max          = energyRightAxis.max           = axisMaxValues[GraphAxisEnum.ENERGY_IDX] + 1;
        forceLeftAxis.max           = forceRightAxis.max            = axisMaxValues[GraphAxisEnum.FORCE_IDX] + 1;
        velocityLeftAxis.max        = velocityRightAxis.max         = axisMaxValues[GraphAxisEnum.VELOCITY_IDX] + 1;
        absoluteDistLeftAxis.max    = absoluteDistRightAxis.max     = axisMaxValues[GraphAxisEnum.ABSOLUTEDIST_IDX] + 1;
        collapseDistLeftAxis.max    = collapseDistRightAxis.max     = axisMaxValues[GraphAxisEnum.COLLAPSEDIST_IDX] + 1;

        /* Rounding of axis values for proper representation */
        freqLeftAxis.max           = freqRightAxis.max          = roundAxisValues(freqLeftAxis.max, freqLeftAxis.min);
        phaseLeftAxis.max          = phaseRightAxis.max         = roundAxisValues(phaseLeftAxis.max, phaseLeftAxis.min);
        ampLeftAxis.max            = ampRightAxis.max           = roundAxisValues(ampLeftAxis.max, ampLeftAxis.min);
        currentLeftAxis.max        = currentRightAxis.max       = roundAxisValues(currentLeftAxis.max, currentLeftAxis.min);
        powerLeftAxis.max          = powerRightAxis.max         = roundAxisValues(powerLeftAxis.max, powerLeftAxis.min);
        energyLeftAxis.max         = energyRightAxis.max        = roundAxisValues(energyLeftAxis.max, energyLeftAxis.min);
        forceLeftAxis.max          = forceRightAxis.max         = roundAxisValues(forceLeftAxis.max, forceLeftAxis.min);
        velocityLeftAxis.max       = velocityRightAxis.max      = roundAxisValues(velocityLeftAxis.max, velocityLeftAxis.min);
        absoluteDistLeftAxis.max   = absoluteDistRightAxis.max  = roundAxisValues(absoluteDistLeftAxis.max, absoluteDistLeftAxis.min);
        collapseDistLeftAxis.max   = collapseDistRightAxis.max  = roundAxisValues(collapseDistLeftAxis.max, collapseDistLeftAxis.min);

    }

    function clearGraph()
    {
        timeAxis.min = 0;
        timeAxis.max = timemax;
        freqLeftAxisPlot.clear()
        freqRightAxisPlot.clear()
        powerLeftAxisPlot.clear()
        powerRightAxisPlot.clear()
        currentLeftAxisPlot.clear()
        currentRightAxisPlot.clear()
        ampLeftAxisPlot.clear()
        ampRightAxisPlot.clear()
        phaseLeftAxisPlot.clear()
        phaseRightAxisPlot.clear()
        energyLeftAxisPlot.clear()
        energyRightAxisPlot.clear()
        forceLeftAxisPlot.clear()
        forceRightAxisPlot.clear()
        velocityLeftAxisPlot.clear()
        velocityRightAxisPlot.clear()
        collapseDistLeftAxisPlot.clear()
        collapseDistRightAxisPlot.clear()
        absoluteDistLeftAxisPlot.clear()
        absoluteDistRightAxisPlot.clear()
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
                property real deltaX: plotArea.width / (timeAxis.max - timeAxis.min)
                property real myWidth: 1
//                plotAreaColor: "red"
                width: parent.width
                height: parent.height
                transformOrigin: Item.Center
                PinchArea{
                    id:pinchzoom
                    enabled: flagDragDrop
                    anchors.fill: parent
                    pinch.target: graphChartView
                    pinch.maximumScale: 10
                    pinch.minimumScale: 1
                    pinch.dragAxis: Pinch.XAndYAxis
                    MouseArea{
                        id:mousezoom
                        enabled: flagDragDrop
                        anchors.fill: parent
                        drag.target: graphChartView
                        drag.axis:Drag.XAndYAxis
                        onMouseXChanged: {
                            var xfirst  =   graphChartView.width/3
                            var xsecond =   xfirst*2
                            var xthird  =   xfirst*3

                            var yfirst  =   graphChartView.height/3
                            var ysecond =   yfirst*2
                            var ythird  =   yfirst*3
                            if(graphChartView.scale===1)
                            {
                                if((mouseX>0 && mouseX<xfirst)&&(mouseY>0 && mouseY<yfirst))
                                {
                                    graphChartView.transformOrigin=Item.TopLeft
                                }
                                else if((mouseX>0 && mouseX<xfirst)&&(mouseY>yfirst && mouseY<ysecond))
                                {
                                    graphChartView.transformOrigin=Item.Left
                                }
                                else if((mouseX>0 && mouseX<xfirst)&&(mouseY>ysecond && mouseY<ythird))
                                {
                                    graphChartView.transformOrigin=Item.BottomLeft
                                }
                                else if((mouseX>xfirst && mouseX<xsecond)&&(mouseY>0 && mouseY<yfirst))
                                {
                                    graphChartView.transformOrigin=Item.Top
                                }
                                else if((mouseX>xfirst && mouseX<xsecond)&&(mouseY>yfirst && mouseY<ysecond))
                                {
                                    graphChartView.transformOrigin=Item.Center
                                }
                                else if((mouseX>xfirst && mouseX<xsecond)&&(mouseY>ysecond && mouseY<ythird))
                                {
                                    graphChartView.transformOrigin=Item.Bottom
                                }
                                else if((mouseX>xsecond && mouseX<xthird)&&(mouseY>0 && mouseY<yfirst))
                                {
                                    graphChartView.transformOrigin=Item.TopRight
                                }
                                else if((mouseX>xsecond && mouseX<xthird)&&(mouseY>yfirst && mouseY<ysecond))
                                {
                                    graphChartView.transformOrigin=Item.Right
                                }
                                else if((mouseX>xsecond && mouseX<xthird)&&(mouseY>ysecond && mouseY<ythird))
                                {
                                    graphChartView.transformOrigin=Item.BottomRight
                                }
                            }
                        }

                        onDoubleClicked:
                        {
                            if(graphChartView.x!==0 || graphChartView.y!==0)
                            {
                                graphChartView.x = 0
                                graphChartView.y = 0
                                graphChartView.scale=1
                                transformOrigin: Item.Center
                            }
                            else if(graphChartView.x === 0 && graphChartView.y === 0)
                            {
                                if(graphChartView.scale === 1)
                                {
                                    graphChartView.scale = 2
                                }
                                else
                                {
                                    graphChartView.x = 0
                                    graphChartView.y = 0
                                    graphChartView.scale = 1
                                    transformOrigin: Item.Center
                                }
                            }
                        }
                    }
                }

                ValueAxis {
                    id: timeAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.TIME_IDX)
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.TIME_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.TIME_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    titleVisible: true
                    labelFormat: "%.5f"
                    max: timemax
                    min: 0.00000
                    tickCount: 5
                }

                ValueAxis {
                    id: phaseLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.PHASE_IDX)
                    visible: isPhaseLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.PHASE_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.PHASE_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    max: 180
                    min: -180
                    tickCount: 11
                    labelFormat: "%.0f"
                }

                ValueAxis {
                    id: phaseRightAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.PHASE_IDX)
                    visible: isPhaseRightAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.PHASE_IDX)
                    lineVisible:true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.PHASE_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    max: 180
                    min: -180
                    tickCount: 11
                    labelFormat: "%.0f"
                }

                ValueAxis {
                    id: energyLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.ENERGY_IDX)
                    visible: isEnergyLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.ENERGY_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.ENERGY_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    max: 50
                    min: 0
                    tickCount: 11
                    labelFormat: "%.0f"
                }

                ValueAxis {
                    id : energyRightAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.ENERGY_IDX)
                    visible: isEnergyRightAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.ENERGY_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.ENERGY_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    max: 50
                    min: 0
                    tickCount: 11
                    labelFormat: "%.0f"
                }

                ValueAxis {
                    id : freqLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.FREQ_IDX)
                    visible: isFreqLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.FREQ_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.FREQ_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    max: 20450
                    min: 19450
                    tickCount: 11
                    labelFormat: "%.0f"
                }

                ValueAxis {
                    id: freqRightAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.FREQ_IDX)
                    visible: isFreqRightAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.FREQ_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.FORCE_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    max: 20450
                    min: 19450
                    tickCount: 11
                    labelFormat: "%.0f"
                }

                ValueAxis {
                    id: ampLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.AMP_IDX)
                    visible: isAmpLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.AMP_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.AMP_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    labelFormat: "%.0f"
                    max: 120
                    min:0
                    tickCount: 11
                }

                ValueAxis {
                    id: ampRightAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.AMP_IDX)
                    visible: isAmpRightAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.AMP_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.AMP_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    labelFormat: "%.0f"
                    max: 120
                    min:0
                    tickCount: 11
                }

                ValueAxis {
                    id: currentLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.CURRENT_IDX)
                    visible: isCurrentLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.CURRENT_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.CURRENT_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    labelFormat: "%.0f"
                    max: 120
                    min:0
                    tickCount: 11
                }

                ValueAxis {
                    id: currentRightAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.CURRENT_IDX)
                    visible: isCurrentRightAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.CURRENT_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.CURRENT_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    labelFormat: "%.0f"
                    max: 30//120
                    min:0
                    tickCount: 11
                }

                ValueAxis {
                    id: powerLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.POWER_IDX)
                    visible: isPowerLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.POWER_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.POWER_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    labelFormat: "%.0f"
                    max: 10
                    min:0
                    tickCount: 11
                }

                ValueAxis {
                    id: powerRightAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.POWER_IDX)
                    visible: isPowerRightAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.POWER_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.POWER_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    labelFormat: "%.0f"
                    max: 10
                    min:0
                    tickCount: 11
                }

                ValueAxis {
                    id: forceLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.FORCE_IDX)
                    visible: isForceLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.FORCE_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.FORCE_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    labelFormat: "%.0f"
                    max: 120
                    min:0
                    tickCount: 11
                }

                ValueAxis {
                    id: forceRightAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.FORCE_IDX)
                    visible: isForceRightAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.FORCE_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.FORCE_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    labelFormat: "%.0f"
                    max: 120
                    min:0
                    tickCount: 11
                }

                ValueAxis {
                    id: velocityLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.VELOCITY_IDX)
                    visible: isVelocityLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.VELOCITY_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.VELOCITY_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    labelFormat: "%.0f"
                    max: 120
                    min:0
                    tickCount: 11
                }

                ValueAxis {
                    id: velocityRightAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.VELOCITY_IDX)
                    visible: isVelocityRightAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.VELOCITY_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.VELOCITY_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    labelFormat: "%.0f"
                    max: 120
                    min:0
                    tickCount: 11
                }

                ValueAxis {
                    id: absoluteDistLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.ABSOLUTEDIST_IDX)
                    visible: isAbsoluteDistLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.ABSOLUTEDIST_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.ABSOLUTEDIST_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    labelFormat: "%.0f"
                    max: 120
                    min:0
                    tickCount: 11
                }

                ValueAxis {
                    id: absoluteDistRightAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.ABSOLUTEDIST_IDX)
                    visible: isAbsoluteDistRightAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.ABSOLUTEDIST_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.ABSOLUTEDIST_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    labelFormat: "%.0f"
                    max: 120
                    min:0
                    tickCount: 11
                }

                ValueAxis {
                    id: collapseDistLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.COLLAPSEDIST_IDX)
                    visible: isCollapseDistLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.COLLAPSEDIST_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.COLLAPSEDIST_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    labelFormat: "%.0f"
                    max: 5
                    min: -5
                    tickCount: 11
                }

                ValueAxis {
                    id: collapseDistRightAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.COLLAPSEDIST_IDX)
                    visible: isCollapseDistRightAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.COLLAPSEDIST_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.COLLAPSEDIST_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: false
                    labelFormat: "%.0f"
                    max: 5
                    min: -5
                    tickCount: 11
                }

                LineSeries{
                    id: energyLeftAxisPlot
                    width: graphChartView.myWidth
                    name: energyLeftPlotName
                    axisX: timeAxis
                    axisY: energyLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.ENERGY_IDX)
                    visible: isEnergyLeftAxisVisible
                    useOpenGL: true
                    pointsVisible: true
                }

                LineSeries{
                    id: energyRightAxisPlot
                    width: graphChartView.myWidth
                    name: energyRightPlotName
                    axisX: timeAxis
                    axisYRight: energyRightAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.ENERGY_IDX)
                    visible: isEnergyRightAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                LineSeries{
                    id: ampLeftAxisPlot
                    width: graphChartView.myWidth
                    color: AxisDefine.getAxisColor(GraphAxisEnum.AMP_IDX)
                    name: ampLeftPlotName
                    axisX: timeAxis
                    axisY: ampLeftAxis
                    visible: isAmpLeftAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                LineSeries{
                    id: ampRightAxisPlot
                    width: graphChartView.myWidth
                    color: AxisDefine.getAxisColor(GraphAxisEnum.AMP_IDX)
                    name: ampRightPlotName
                    axisX: timeAxis
                    axisYRight: ampRightAxis
                    visible: isAmpRightAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                LineSeries{
                    id: currentLeftAxisPlot
                    width: graphChartView.myWidth
                    color: AxisDefine.getAxisColor(GraphAxisEnum.CURRENT_IDX)
                    name: currentLeftPlotName
                    axisX: timeAxis
                    axisY: currentLeftAxis
                    visible: isCurrentLeftAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                LineSeries{
                    id: currentRightAxisPlot
                    width: graphChartView.myWidth
                    color: AxisDefine.getAxisColor(GraphAxisEnum.CURRENT_IDX)
                    name: currentRightPlotName
                    axisX: timeAxis
                    axisYRight: currentRightAxis
                    visible: isCurrentRightAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                LineSeries{
                    id: powerLeftAxisPlot
                    width: graphChartView.myWidth
                    name: powerLeftPlotName
                    axisX: timeAxis
                    axisY: powerLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.POWER_IDX)
                    visible: isPowerLeftAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                LineSeries{
                    id: powerRightAxisPlot
                    width: graphChartView.myWidth
                    name: powerRightPlotName
                    axisX: timeAxis
                    axisYRight: powerRightAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.POWER_IDX)
                    visible: isPowerRightAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                LineSeries{
                    id: phaseLeftAxisPlot
                    width: graphChartView.myWidth
                    name: phaseLeftPlotName
                    axisX: timeAxis
                    axisY: phaseLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.PHASE_IDX)
                    visible: isPhaseLeftAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                LineSeries{
                    id: phaseRightAxisPlot
                    width: graphChartView.myWidth
                    name: phaseRightPlotName
                    axisX: timeAxis
                    axisYRight: phaseRightAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.PHASE_IDX)
                    visible: isPhaseRightAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                LineSeries{
                    id: forceLeftAxisPlot
                    width: graphChartView.myWidth
                    name: forceLeftPlotName
                    axisX: timeAxis
                    axisY: forceLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.FORCE_IDX)
                    visible: isForceLeftAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                LineSeries{
                    id: forceRightAxisPlot
                    width: graphChartView.myWidth
                    name: forceRightPlotName
                    axisX: timeAxis
                    axisYRight: forceRightAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.FORCE_IDX)
                    visible: isForceRightAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                LineSeries{
                    id: velocityLeftAxisPlot
                    width: graphChartView.myWidth
                    name: velocityLeftPlotName
                    axisX: timeAxis
                    axisY: velocityLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.VELOCITY_IDX)
                    visible: isVelocityLeftAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                LineSeries{
                    id: velocityRightAxisPlot
                    width: graphChartView.myWidth
                    name: velocityRightPlotName
                    axisX: timeAxis
                    axisYRight: velocityRightAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.VELOCITY_IDX)
                    visible: isVelocityRightAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                LineSeries{
                    id: absoluteDistLeftAxisPlot
                    width: graphChartView.myWidth
                    name: absoluteDistLeftPlotName
                    axisX: timeAxis
                    axisY: absoluteDistLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.ABSOLUTEDIST_IDX)
                    visible: isAbsoluteDistLeftAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                LineSeries{
                    id: absoluteDistRightAxisPlot
                    width: graphChartView.myWidth
                    name: absoluteDistRightPlotName
                    axisX: timeAxis
                    axisYRight: absoluteDistRightAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.ABSOLUTEDIST_IDX)
                    visible: isAbsoluteDistRightAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                LineSeries{
                    id: collapseDistLeftAxisPlot
                    width: graphChartView.myWidth
                    name: collapseDistLeftPlotName
                    axisX: timeAxis
                    axisY: collapseDistLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.COLLAPSEDIST_IDX)
                    visible: isCollapseDistLeftAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                LineSeries{
                    id: collapseDistRightAxisPlot
                    width: graphChartView.myWidth
                    name: collapseDistRightPlotName
                    axisX: timeAxis
                    axisYRight: collapseDistRightAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.COLLAPSEDIST_IDX)
                    visible: isCollapseDistRightAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                LineSeries{
                    id: freqLeftAxisPlot
                    width: graphChartView.myWidth
                    name: freqLeftPlotName
                    axisX: timeAxis
                    axisY: freqLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.FREQ_IDX)
                    visible: isFreqLeftAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                LineSeries{
                    id: freqRightAxisPlot
                    width: graphChartView.myWidth
                    name: freqRightPlotName
                    axisX: timeAxis
                    axisYRight: freqRightAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.FREQ_IDX)
                    visible: isFreqRightAxisVisible
                    pointsVisible: true
                    useOpenGL: true
                }

                Rectangle
                {
                    id: chartViewArea
                    x: graphChartView.plotArea.x
                    y: graphChartView.plotArea.y
                    height : graphNavigator.height + graphNavigatorImage.height + graphNavigatorLabel.height
                    width : graphChartView.plotArea.width
                    visible: false
                }

                Rectangle {
                    id: graphSlider
                    property int raiseHeight: Math.round(15 * Style.scaleHint)
                    property string custColor : Style.activeFrameBorderColor
                    property int assetSize:20
                    property real xAxisVal: timeAxis.min
                    property string timeLabel: timeAxis.min
                    property bool timeDecimalValFlag: true
                    y: graphChartView.plotArea.y
                    x: graphChartView.plotArea.x + (xAxisVal - timeAxis.min) * graphChartView.deltaX - width / 2
                    width : graphNavigatorLabel.width
                    height : graphChartView.plotArea.height
                    color: "transparent"
                    Rectangle
                    {
                        id: graphNavigator
                        height: graphChartView.plotArea.height - graphNavigatorImage.height/2
                        width: 2
                        anchors.bottom: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: parent.custColor
                    }

                    Rectangle {
                        id: graphNavigatorImage
                        height: parent.assetSize
                        width : parent.assetSize
                        radius: width / 2
                        color: parent.custColor
                        anchors.bottom: graphNavigator.top
                        anchors.horizontalCenter: parent.horizontalCenter
                        MouseArea {
                            id: graphNavigatorMouseArea
                            property point posInChartArea
                            property int indexClosest1:0
                            anchors.fill: parent
                            cursorShape: Qt.ToolTip
                            hoverEnabled: false
                            onPositionChanged: {
                                /* Drag position of the slider */
                                var point = mapToItem(chartViewArea , mouse.x , mouse.y);
                                var retVal ;
                                var timeVal;
                                var tmpPoint,timePoint,powerPoint,freqPoint, phasePoint, currPoint, energyPoint, ampPoint, forcePoint, velocityPoint, absoluteDistPoint, collapseDistPoint;

                                if(point.x < 0 || point.x > graphChartView.plotArea.width)
                                {
                                    if(point.x < 0)
                                    {
                                        timeVal = timeAxis.min;
                                        graphSlider.xAxisVal = timeAxis.min;
                                    }
                                    else
                                    {
                                        posInChartArea.x = graphChartView.plotArea.width ;
                                        timeVal = timeAxis.max;
                                        graphSlider.xAxisVal = timeAxis.max
                                    }
                                }
                                else
                                {
                                    posInChartArea.x = point.x;
                                    posInChartArea.y = point.y;
                                    timeVal = posInChartArea.x / graphChartView.deltaX + timeAxis.min;
                                    graphSlider.xAxisVal = posInChartArea.x / graphChartView.deltaX + timeAxis.min ;
                                }

                                /* calculating the points in the graph */
                                graphSlider.timeLabel = timeVal.toFixed(5)
                                //retVal = getClosestPoints(timeVal.toFixed(5));
                                if(-1 === retVal)
                                {
                                    tmpPoint = 0;
                                    powerPoint = 0 ;
                                    freqPoint = 0;
                                    phasePoint = 0 ;
                                    currPoint = 0 ;
                                    ampPoint = 0 ;
                                    energyPoint = 0;
                                    forcePoint = 0 ;
                                    velocityPoint = 0 ;
                                    absoluteDistPoint = 0 ;
                                    collapseDistPoint = 0 ;
                                }
                                else
                                {
                                    tmpPoint = powerLeftAxisPlot.at(indexClosest1);
                                    powerPoint = tmpPoint.y;
                                    timePoint = tmpPoint.x;

                                    tmpPoint = freqLeftAxisPlot.at(indexClosest1);
                                    freqPoint = tmpPoint.y;

                                    tmpPoint = ampLeftAxisPlot.at(indexClosest1);
                                    ampPoint = tmpPoint.y;

                                    tmpPoint = currentLeftAxisPlot.at(indexClosest1);
                                    currPoint = tmpPoint.y;

                                    tmpPoint = phaseLeftAxisPlot.at(indexClosest1);
                                    phasePoint = tmpPoint.y;

                                    tmpPoint = energyLeftAxisPlot.at(indexClosest1);
                                    energyPoint = tmpPoint.y ;

                                    tmpPoint = forceLeftAxisPlot.at(indexClosest1);
                                    forcePoint = tmpPoint.y ;

                                    tmpPoint = velocityLeftAxisPlot.at(indexClosest1);
                                    velocityPoint = tmpPoint.y ;

                                    tmpPoint = absoluteDistLeftAxisPlot.at(indexClosest1);
                                    absoluteDistPoint = tmpPoint.y ;

                                    tmpPoint = collapseDistLeftAxisPlot.at(indexClosest1);
                                    collapseDistPoint = tmpPoint.y ;

                                    // checkboxObj.updateParameterVal(ampPoint,currPoint,powerPoint,freqPoint,energyPoint,phasePoint,forcePoint,velocityPoint,absoluteDistPoint,collapseDistPoint)
                                    //                                graphSlider.timeLabel = timePoint.toFixed(5);
                                    // gridview2.contentItem.children[0].paramVal = timePoint.toFixed(5);
                                }
                            }
                        }
                    }
                    Text {
                        id: graphNavigatorLabel
                        anchors.bottom: graphNavigatorImage.top
                        anchors.bottomMargin: 5
                        height: font.pixelSize
                        anchors.horizontalCenter: graphSlider.horizontalCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.family: Style.regular.name
                        font.pixelSize: Math.round(Style.style4  * Style.scaleHint)
                        text: parent.timeLabel + " " +qmltextSecUnit
                        color: parent.custColor
                    }
                }
            }
        }
    }
}
