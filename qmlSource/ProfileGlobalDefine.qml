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
    id: profileGlobalDefine
    readonly property var wellTypeModel: [qsTr("垂直井段"), qsTr("大斜度井段"), qsTr("水平井段")]
    readonly property var workTypeModel: [qsTr("射孔"), qsTr("测井")]
}

