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
// import Com.Branson.UIScreenEnum 1.0
Item
{
    id: tensionsGlobalDefine
    readonly property var tensionUnitModel: ["lb", "kg", "kn"]
    readonly property var tensionAnalogModel: ["0-5V", "0-1.5V", "0-30mV"]
    readonly property var tensionEncoderModel: [qsTr("数字有线"), qsTr("数字无线"), qsTr("模拟有线"), qsTr("模拟无线")]
    readonly property var tensionCableHeadTrendModel: [qsTr("正常"), qsTr("增加"), qsTr("减小")]
}

