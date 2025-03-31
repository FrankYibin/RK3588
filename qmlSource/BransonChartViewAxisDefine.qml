/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 xxxxx

 **********************************************************************************************************/
pragma Singleton //we indicate that this QML Type is a singleton
import QtQuick 2.12
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.GraphAxisEnum 1.0
Item {
    id: graphAxisDefine

    property string qmltextPhaseAxis:           qsTr("Phase")
    property string qmltextEnergyAxis:          qsTr("Energy")
    property string qmltextFreqAxis:            qsTr("Frequency")
    property string qmltextAmpAxis:             qsTr("Amplitude")
    property string qmltextCurrentAxis:         qsTr("Current")
    property string qmltextPowerAxis:           qsTr("Power")
    property string qmltextForceAxis:           qsTr("Force")
    property string qmltextVelocityAxis:        qsTr("Velocity")
    property string qmltextAbsoluteDistAxis:    qsTr("Abs Distance")
    property string qmltextCollapseDistAxis:    qsTr("Col Distance")
    property string qmltextTimeAxis:            qsTr("Time")

    property var qmlTextArray: [qmltextPhaseAxis, qmltextEnergyAxis, qmltextFreqAxis,
        qmltextAmpAxis, qmltextCurrentAxis, qmltextPowerAxis, qmltextForceAxis,
        qmltextVelocityAxis, qmltextAbsoluteDistAxis, qmltextCollapseDistAxis, qmltextTimeAxis]
    property var qmlTextComboxModel: [qmltextPhaseAxis, qmltextEnergyAxis, qmltextFreqAxis,
        qmltextAmpAxis, qmltextCurrentAxis, qmltextPowerAxis, qmltextForceAxis,
        qmltextVelocityAxis, qmltextAbsoluteDistAxis, qmltextCollapseDistAxis]

    readonly property color phaseAxisColor:         "#757577"
    readonly property color energyAxisColor:        "#f79428"
    readonly property color freqAxisColor:          "#99ccff"
    readonly property color ampAxisColor:           "#ef7c7d"
    readonly property color currentAxisColor:       "#00aa7e"
    readonly property color powerAxisColor:         "#b388ff"
    readonly property color forceAxisColor:         "#685120"
    readonly property color velocityAxisColor:      "#917059"
    readonly property color absoluteDistAxisColor:  "#a0cf67"
    readonly property color collapseDistAxisColor:  "#ea80fc"
    readonly property color timeAxisColor:          "#868e96"
    readonly property var colorArray: [phaseAxisColor, energyAxisColor, freqAxisColor,
        ampAxisColor, currentAxisColor, powerAxisColor, forceAxisColor, velocityAxisColor, absoluteDistAxisColor, collapseDistAxisColor, timeAxisColor]

    function updateLanguage()
    {
        qmlTextArray = languageConfig.getLanguageStringList(UIScreenEnum.ANALYTICS_RESULT_GRAPH_AXIS, qmlTextArray)
        qmltextPhaseAxis =          qmlTextArray[GraphAxisEnum.PHASE_IDX]
        qmltextEnergyAxis =         qmlTextArray[GraphAxisEnum.ENERGY_IDX]
        qmltextFreqAxis =           qmlTextArray[GraphAxisEnum.FREQ_IDX]
        qmltextAmpAxis =            qmlTextArray[GraphAxisEnum.AMP_IDX]
        qmltextCurrentAxis =        qmlTextArray[GraphAxisEnum.CURRENT_IDX]
        qmltextPowerAxis =          qmlTextArray[GraphAxisEnum.POWER_IDX]
        qmltextForceAxis =          qmlTextArray[GraphAxisEnum.FORCE_IDX]
        qmltextVelocityAxis =       qmlTextArray[GraphAxisEnum.VELOCITY_IDX]
        qmltextAbsoluteDistAxis =   qmlTextArray[GraphAxisEnum.ABSOLUTEDIST_IDX]
        qmltextCollapseDistAxis =   qmlTextArray[GraphAxisEnum.COLLAPSEDIST_IDX]
        qmltextTimeAxis =           qmlTextArray[GraphAxisEnum.TIME_IDX]
    }

    Component.onCompleted:
    {
        updateLanguage()
    }

    function getAxisModel()
    {
        return qmlTextComboxModel
    }

    function getAxisColor(index)
    {
        if(index < colorArray.length)
            return colorArray[index]
        else
            return "#757577";
    }

    function getAxisTitle(index)
    {
        if(index < qmlTextArray.length)
            return qmlTextArray[index]
        else
            return qmlTextArray[0]
    }
}

