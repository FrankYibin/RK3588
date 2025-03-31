/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import Style 1.0
import AxisDefine 1.0
import Com.Branson.GraphAxisEnum 1.0
import Com.Branson.UIScreenEnum 1.0
Item {
    property double timedata: 1
    property string qmltextCycleNumber: qsTr("Cycle Number")

    function leftline(index)
    {
        chartView.isPhaseLeftAxisVisible        = false
        chartView.isEnergyLeftAxisVisible       = false
        chartView.isFreqLeftAxisVisible         = false
        chartView.isCurrentLeftAxisVisible      = false
        chartView.isForceLeftAxisVisible        = false
        chartView.isVelocityLeftAxisVisible     = false
        chartView.isAbsoluteDistLeftAxisVisible = false
        chartView.isCollapseDistLeftAxisVisible = false
        chartView.isAmpLeftAxisVisible          = false
        chartView.isPowerLeftAxisVisible        = false
        switch(index)
        {
        case GraphAxisEnum.PHASE_IDX:
            chartView.isPhaseLeftAxisVisible        = true
            break;
        case GraphAxisEnum.ENERGY_IDX:
            chartView.isEnergyLeftAxisVisible       = true
            break
        case GraphAxisEnum.FREQ_IDX:
            chartView.isFreqLeftAxisVisible         = true
            break
        case GraphAxisEnum.CURRENT_IDX:
            chartView.isCurrentLeftAxisVisible      = true
            break
        case GraphAxisEnum.FORCE_IDX:
            chartView.isForceLeftAxisVisible        = true
            break
        case GraphAxisEnum.VELOCITY_IDX:
            chartView.isVelocityLeftAxisVisible     = true
            break
        case GraphAxisEnum.ABSOLUTEDIST_IDX:
            chartView.isAbsoluteDistLeftAxisVisible = true
            break;
        case GraphAxisEnum.COLLAPSEDIST_IDX:
            chartView.isCollapseDistLeftAxisVisible = true
            break
        case GraphAxisEnum.AMP_IDX:
            chartView.isAmpLeftAxisVisible          = true
            break;
        case GraphAxisEnum.POWER_IDX:
            chartView.isPowerLeftAxisVisible        = true
            break
        default:
            break
        }
        rectright.rectleftcolor = AxisDefine.getAxisColor(index)
    }

    function rightline(index)
    {
        chartView.isPhaseRightAxisVisible        = false
        chartView.isEnergyRightAxisVisible       = false
        chartView.isFreqRightAxisVisible         = false
        chartView.isCurrentRightAxisVisible      = false
        chartView.isForceRightAxisVisible        = false
        chartView.isVelocityRightAxisVisible     = false
        chartView.isAbsoluteDistRightAxisVisible = false
        chartView.isCollapseDistRightAxisVisible = false
        chartView.isAmpRightAxisVisible          = false
        chartView.isPowerRightAxisVisible        = false
        switch(index)
        {
        case GraphAxisEnum.PHASE_IDX:
            chartView.isPhaseRightAxisVisible           = true
            break
        case GraphAxisEnum.ENERGY_IDX:
            chartView.isEnergyRightAxisVisible          = true
            break
        case GraphAxisEnum.FREQ_IDX:
            chartView.isFreqRightAxisVisible            = true
            break
        case GraphAxisEnum.CURRENT_IDX:
            chartView.isCurrentRightAxisVisible         = true
            break
        case GraphAxisEnum.FORCE_IDX:
            chartView.isForceRightAxisVisible           = true
            break;
        case GraphAxisEnum.VELOCITY_IDX:
            chartView.isVelocityRightAxisVisible        = true
            break
        case GraphAxisEnum.ABSOLUTEDIST_IDX:
            chartView.isAbsoluteDistRightAxisVisible    = true
            break;
        case GraphAxisEnum.COLLAPSEDIST_IDX:
            chartView.isCollapseDistRightAxisVisible    = true
            break;
        case GraphAxisEnum.AMP_IDX:
            chartView.isAmpRightAxisVisible             = true
            break;
        case GraphAxisEnum.POWER_IDX:
            chartView.isPowerRightAxisVisible           =true
            break;
        default:
            break;
        }
        rectright.rectrightcolor = AxisDefine.getAxisColor(index)
    }

    function updateLanguage()
    {
        qmltextCycleNumber = languageConfig.getLanguageStringList(UIScreenEnum.ANALYTICS_RESULT_GRAPH_VIEW, qmltextCycleNumber)
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted: {
        weldGraphLoadTimer.start()
        rectright.leftAxisChanged.connect(leftline)
        rectright.rightAxisChanged.connect(rightline)
        updateLanguage()
    }

    Rectangle
    {
        id: graphFrame
        width: Math.round(610 * Style.scaleHint)
        height: parent.height
        anchors.top:parent.top
        anchors.left: parent.left
        border.width: Style.scaleHint === 1.0 ? 1 : 3
        border.color: Style.activeFrameBorderColor
        Rectangle
        {
            id: chartViewHeader
            anchors.top: parent.top
            anchors.left: parent.left
            width: parent.width
            height: Math.round(50 * Style.scaleHint)
            color: "transparent"
            Row
            {
                id: btnArray
                anchors.left: parent.left
                anchors.leftMargin: Math.round(6 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                width: Math.round(92 * Style.scaleHint)
                height: Math.round(45 * Style.scaleHint)
                spacing: Math.round(2 * Style.scaleHint)
                Rectangle
                {
                    id: graphBtn
                    width: parent.width/2
                    height: parent.height
                    border.width: 1
                    border.color: Style.frameBorderColor
                    radius: 2
                    Image {
                        id: graphImage
                        source: "qrc:/images/Graph.svg"
                        width: Math.round(30 * Style.scaleHint)
                        height: Math.round(30 * Style.scaleHint)
                        anchors.centerIn: parent
                        sourceSize.width: graphImage.width
                        sourceSize.height: graphImage.height
                        smooth: true
                    }
                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:
                        {
                            graphBtn.border.color="#6699cc"
                            recordsBtn.border.color="#9fa1a4"
                        }
                    }
                }

                Rectangle
                {
                    id: recordsBtn
                    width: parent.width/2
                    height: parent.height
                    border.width: 1
                    border.color: Style.frameBorderColor
                    radius: 2
                    Image {
                        id: recordsImage
                        source: "qrc:/images/Table.svg"
                        width: Math.round(30 * Style.scaleHint)
                        height: Math.round(30 * Style.scaleHint)
                        anchors.centerIn: parent
                        sourceSize.width: recordsImage.width
                        sourceSize.height: recordsImage.height
                        smooth: true
                    }
                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:
                        {
                            recordsBtn.border.color="#6699cc"
                            graphBtn.border.color="#9fa1a4"
                        }
                    }
                }
            }

            Text {
                id: cyclenumber
                anchors.left: btnArray.right
                anchors.leftMargin: Math.round(12 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                text: qmltextCycleNumber + ":"
                font.pixelSize: Math.round(Style.style4  * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blackFontColor
            }
            Text {
                id: cyclenum
                anchors.left: cyclenumber.right
                anchors.leftMargin: Math.round(2 * Style.scaleHint)
                anchors.verticalCenter: cyclenumber.verticalCenter
                text: qsTr("178")
                font.pixelSize: Math.round(Style.style4  * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blackFontColor
            }

            Image
            {
                id: fullBtn
                width: Math.round(30 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: Math.round(8 * Style.scaleHint)
                source: "qrc:/images/Maximize.svg"
                sourceSize.width: fullBtn.width
                sourceSize.height: fullBtn.height
                smooth: true
            }
            MouseArea
            {
                id: fullBtnClickArea
                width: parent.height
                height: parent.height
                anchors.centerIn: fullBtn
                onClicked:
                {
                    mainWindow.showFullScreenChart()
                }
            }

        }

        BransonChartView
        {
            id: chartView
            width: parent.width
            anchors.left: chartViewHeader.left
            anchors.top: chartViewHeader.bottom
            anchors.bottom: parent.bottom
            timemax: timedata
        }
    }
    BransonChartRightSetting
    {
        id: rectright
        anchors.top: graphFrame.top
        height: parent.height
        anchors.left: graphFrame.right
        anchors.leftMargin: Math.round(2 * Style.scaleHint)
        anchors.right: parent.right
    }

    Timer
    {
        id: weldGraphLoadTimer
        interval: 3000
        repeat: true
        onTriggered:
        {
            chartView.clearGraph()
            weldGraphObj.clearGraph()
            weldGraphObj.generateRandomNumber()
            chartView.plotGraph()
        }
    }

}
