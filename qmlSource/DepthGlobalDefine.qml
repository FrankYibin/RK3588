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
QtObject
{
    id: depthGlobalDefine
    readonly property var velocityUnitModel:    ["m/h", "m/min", "ft/h", "ft/min"]
    readonly property var timeUnitModel:        ["h", "min"]
    readonly property var distanceUnitModel:    ["m", "ft"]
}

