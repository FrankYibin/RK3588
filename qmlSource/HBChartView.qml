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

    property int currentStartIndex: 0
    property int pointsPerPage: 500
    property int actualPoints: 500
    property int cursorIndex: 0 // 游标初始在显示区间中间

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
        var timePoints = SensorGraphData.getDateTimes();
        var depthPoints = SensorGraphData.getDepths();
        var velocityPoints = SensorGraphData.getVelocitys();
        var tensionPoints = SensorGraphData.getTensions();
        var tensionDeltaPoints = SensorGraphData.getTensionDeltas();
        var axisMinValues = SensorGraphData.getAxisMinParameters();
        var axisMaxValues = SensorGraphData.getAxisMaxParameters();
        // 只显示 currentStartIndex 到 currentStartIndex+pointsPerPage 的数据
        var start = currentStartIndex;
        var end = Math.min(timePoints.length, currentStartIndex + pointsPerPage);
        actualPoints = end - start
        var timeSlice = timePoints.slice(start, end);
        var depthSlice = depthPoints.slice(start, end);
        var velocitySlice = velocityPoints.slice(start, end);
        var tensionSlice = tensionPoints.slice(start, end);
        var tensionDeltaSlice = tensionDeltaPoints.slice(start, end);
        // 更新X轴范围
        timeAxis.min = timeSlice[0];
        timeAxis.max = timeSlice[timeSlice.length - 1];
        depthLeftAxis.min = axisMinValues[0];
        velocityLeftAxis.min = axisMinValues[1];
        tensionsLeftAxis.min = axisMinValues[2];
        tensionIncrementLeftAxis.min = axisMinValues[3];
        depthLeftAxis.max = roundAxisValues(axisMaxValues[0], axisMinValues[0]);
        velocityLeftAxis.max = roundAxisValues(axisMaxValues[1], axisMinValues[1]);
        tensionsLeftAxis.max = roundAxisValues(axisMaxValues[2], axisMinValues[2]);
        tensionIncrementLeftAxis.max = roundAxisValues(axisMaxValues[3], axisMinValues[3]);
        // 清空并添加新数据
        // for(var i = 0; i < timeSlice.length; i++) {
        //     depthLeftAxisPlot.append(timeSlice[i], depthSlice[i]);
        //     velocityLeftAxisPlot.append(timeSlice[i], velocitySlice[i]);
        //     tensionsLeftAxisPlot.append(timeSlice[i], tensionSlice[i]);
        //     tensionIncrementLeftAxisPlot.append(timeSlice[i], tensionDeltaSlice[i]);
        // }
        SensorGraphData.replaceSeriesPoints(HBGraphAxisEnum.DEPTH_IDX, depthLeftAxisPlot, start, end)
        SensorGraphData.replaceSeriesPoints(HBGraphAxisEnum.VELOCITY_IDX, velocityLeftAxisPlot, start, end)
        SensorGraphData.replaceSeriesPoints(HBGraphAxisEnum.TENSIONS_IDX, tensionsLeftAxisPlot, start, end)
        SensorGraphData.replaceSeriesPoints(HBGraphAxisEnum.TENSION_INCREMENT_IDX, tensionIncrementLeftAxisPlot, start, end)
    }

    function clearGraph()
    {
        depthLeftAxisPlot.clear()

        velocityLeftAxisPlot.clear()

        tensionsLeftAxisPlot.clear()

        tensionIncrementLeftAxisPlot.clear()
    }

    function updateProgressSlider() {
        var totalPoints = SensorGraphData.getDateTimes().length
        var visiblePoints = pointsPerPage
        var percent = Math.round(currentStartIndex / (totalPoints - visiblePoints) * 100)
        progressSlider.value = percent
        progressLabel.text =  percent + "%"
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        // border.color: Style.backgroundMiddleColor

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
                //                format: "hh:mm:ss"
                max: new Date()
                min: new Date()
                tickCount: 4
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

        // 游标竖线和圆球
        Item {
            id: cursorItem
            anchors.fill: parent
            property int cursorIndex: weldGraph.cursorIndex
            property real cursorX: graphChartView.plotArea.x
            onCursorIndexChanged:
            {
                if (depthLeftAxisPlot && depthLeftAxisPlot.count > 0 && cursorIndex < depthLeftAxisPlot.count) {
                    var point = depthLeftAxisPlot.at(cursorIndex);
                    var mappedPosition = graphChartView.mapToPosition(point, depthLeftAxisPlot);
                    cursorX = mappedPosition.x;
                } else {
                    cursorX = graphChartView.plotArea.x;
                }
            }

            Rectangle {
                x: cursorItem.cursorX - 1
                width: 2
                y: graphChartView.plotArea.y
                height: graphChartView.plotArea.height
                color: Style.hbButtonBackgroundColor
            }
            Rectangle {
                id: cursorBall
                x: cursorItem.cursorX - Math.round(8 * Style.scaleHint)
                y: graphChartView.plotArea.y - Math.round(16 * Style.scaleHint)
                width: Math.round(16 * Style.scaleHint)
                height: Math.round(16 * Style.scaleHint)
                color: Style.hbButtonBackgroundColor
                border.color: "white"
                border.width: 2
                radius: Math.round(8 * Style.scaleHint)
                visible: true
                MouseArea {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.margins: Math.round(-50 * Style.scaleHint)
                    property real dragStartX: 0
                    onPressed: {
                        dragStartX = mouse.x
                        pointValue.visible = true
                    }
                    onReleased: pointValue.visible = false
                    onPositionChanged: {
                        var plotWidth = graphChartView.plotArea.width;
                        var relX = parent.x + mouse.x - graphChartView.plotArea.x;
                        var newIndex = 0
                        if(actualPoints < pointsPerPage)
                        {
                            newIndex = Math.round(relX / plotWidth * (actualPoints - 1));
                            cursorIndex = Math.max(0, Math.min(actualPoints - 1, newIndex));

                        }
                        else
                        {
                            newIndex = Math.round(relX / plotWidth * (pointsPerPage - 1));
                            cursorIndex = Math.max(0, Math.min(pointsPerPage - 1, newIndex));
                        }
                    }
                }
            }
            Item
            {
                id: pointValue
                width: 150
                height: 100
                x: cursorItem.cursorX
                y: graphChartView.plotArea.y
                visible: false
                Column {
                    anchors.fill: parent
                    anchors.margins: 5
                    spacing: 5

                    Text {
                        text: qsTr("深度") + ":" + depthLeftAxisPlot.at(cursorIndex).y;
                        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                        font.family: "宋体"
                        color: HBAxisDefine.getAxisColor(HBGraphAxisEnum.DEPTH_IDX)
                    }
                    Text {
                        text: qsTr("速度") + ":" + velocityLeftAxisPlot.at(cursorIndex).y
                        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                        font.family: "宋体"
                        color: HBAxisDefine.getAxisColor(HBGraphAxisEnum.VELOCITY_IDX)
                    }
                    Text {
                        text: qsTr("张力") + ":" + tensionsLeftAxisPlot.at(cursorIndex).y
                        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                        font.family: "宋体"
                        color: HBAxisDefine.getAxisColor(HBGraphAxisEnum.TENSIONS_IDX)
                    }
                    Text {
                        text: qsTr("张力增量") + ":" + tensionIncrementLeftAxisPlot.at(cursorIndex).y
                        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                        font.family: "宋体"
                        color: HBAxisDefine.getAxisColor(HBGraphAxisEnum.TENSION_INCREMENT_IDX)
                    }
                    // Text {
                    //     text: "X Axis: " + cursorItem.cursorX
                    //     font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                    //     color: HBAxisDefine.getAxisColor(HBGraphAxisEnum.TENSION_INCREMENT_IDX)
                    // }
                    // Text {
                    //     text: "cursorIndex: " + cursorIndex
                    //     font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                    //     color: HBAxisDefine.getAxisColor(HBGraphAxisEnum.TENSION_INCREMENT_IDX)
                    // }
                }
            }
        }

        MouseArea {
            x: graphChartView.plotArea.x
            y: graphChartView.plotArea.y
            width: graphChartView.plotArea.width
            height: graphChartView.plotArea.height
            property int dragStartX: 0
            property bool dragging: false
            onPressed: {
                dragStartX = mouse.x
                dragging = true
            }

            onReleased: {
                if (!dragging) return;
                var delta = mouse.x - dragStartX;
                var chartWidth = graphChartView.plotArea.width;
                var newIndex = 0;
                if (Math.abs(delta) > 10) {
                    var totalPoints = SensorGraphData.getDateTimes().length;
                    var moveRatio = delta / chartWidth;
                    var movePoints = Math.round(moveRatio * pointsPerPage);
                    if(movePoints > 0) {
                        newIndex = currentStartIndex - movePoints;
                        currentStartIndex = Math.max(0, newIndex);
                    } else {
                        newIndex = currentStartIndex + Math.abs(movePoints)
                        var maxDelta = totalPoints - pointsPerPage
                        if(maxDelta < 0) maxDelta = 0
                        currentStartIndex = Math.min(maxDelta, newIndex)
                    }
                    plotGraph();
                    updateProgressSlider();
                }
                dragging = false;
            }
        }
    }


    Row {
        anchors.top: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        spacing: 10

        Slider {
            id: progressSlider
            width: weldGraph.width - 90
            from: 0
            to: 100
            stepSize: 1

            height: 30

            handle: Rectangle {
                width: 26
                height: 26
                radius: 13
                color: "#a0cf67"
                border.color: "#999999"
                border.width: 1

                x: progressSlider.leftPadding + progressSlider.visualPosition * (progressSlider.availableWidth - width)
                y: progressSlider.topPadding + progressSlider.availableHeight / 2 - height / 2
            }

            onValueChanged: {

                var totalPoints = SensorGraphData.getDateTimes().length
                var visiblePoints = pointsPerPage
                var maxStartIndex = totalPoints - visiblePoints
                if (maxStartIndex < 0) maxStartIndex = 0

                currentStartIndex = Math.round(value / 100 * maxStartIndex)

                plotGraph()
                progressLabel.text = value + "%"
            }
        }

        Label {
            id: progressLabel
            text: "0%"
            font.family: "宋体"
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            color: "#ffffff"
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenter: progressSlider.verticalCenter
        }
    }

}
