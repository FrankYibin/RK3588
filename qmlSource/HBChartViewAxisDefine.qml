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
import Com.Branson.HBGraphAxisEnum 1.0
Item {
    id: hbGraphAxisDefine

    property string qmltextDepthAxis:                        qsTr("深度")
    property string qmltextVelocityAxis:                     qsTr("速度")
    property string qmltextTensionsAxis:                     qsTr("张力")
    property string qmltextTensionIncrementAxis:             qsTr("张力增量")
    property string qmltextTimeAxis:                         qsTr("时间")

    property var qmlTextArray: [qmltextDepthAxis, qmltextVelocityAxis, qmltextTensionsAxis,
        qmltextTensionIncrementAxis, qmltextTimeAxis]
    property var qmlTextComboxModel: [qmltextDepthAxis, qmltextVelocityAxis, qmltextTensionsAxis,
        qmltextTensionIncrementAxis, qmltextTimeAxis]

    readonly property color depthAxisColor:                 "#ef7c7d"
    readonly property color velocityAxisColor:              "#00afe9"
    readonly property color tensionsAxisColor:              "#00aa7e"
    readonly property color tensionIncrementAxisColor:      "#d31245"
    readonly property color timeAxisColor:                  "#ffffff"
    readonly property var colorArray: [depthAxisColor, velocityAxisColor, tensionsAxisColor,
        tensionIncrementAxisColor, timeAxisColor]

    function getAxisModel()
    {
        return qmlTextComboxModel
    }

    function getAxisColor(index)
    {
        if(index < colorArray.length)
            return colorArray[index]
        else
            return timeAxisColor;
    }

    function getAxisTitle(index)
    {
        if(index < qmlTextArray.length)
            return qmlTextArray[index]
        else
            return qmlTextArray[0]
    }
}

