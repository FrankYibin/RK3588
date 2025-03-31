/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item {
    property string qmltextActuator:        qsTr("Actuator Controller")
    property string qmltextPower:           qsTr("Power Controller")
    property string qmltextSupervisor:     qsTr("Supervisor Controller")
    property var qmlTextArray: [qmltextActuator, qmltextPower, qmltextSupervisor]
    property string path:   ""
    property color backcolor: "#FFFFFF"

    function updateLanguage()
    {
        qmlTextArray = languageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_SOFTWARE_UPGRADE_WELDER, qmlTextArray)
        qmltextActuator  = qmlTextArray[textEnum.actuatorControllerIdx]
        qmltextPower  = qmlTextArray[textEnum.powerControllerIdx]
        qmltextSupervisor  = qmlTextArray[textEnum.supervisorControllerIdx]
    }

    function delay()
    {
        var sleep = function(time) {
            var startTime = new Date().getTime() + parseInt(time, 10);
            while(new Date().getTime() < startTime) {}
        };
        sleep(1000)
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted: {
        updateLanguage()
    }

    QtObject {
        id: textEnum
        readonly property int actuatorControllerIdx:    0
        readonly property int powerControllerIdx:       1
        readonly property int supervisorControllerIdx:  2
    }

    Rectangle
    {
        width: parent.width
        height: parent.height
        Column
        {
            anchors.fill: parent
            Row
            {
                width: Math.round(640 * Style.scaleHint)
                height: Math.round(39 * Style.scaleHint)
                spacing: Math.round(24 * Style.scaleHint)
                anchors.left: parent.left
                Text {
                    id: firsttext
                    width: Math.round(160 * Style.scaleHint)
                    height: Math.round(32 * Style.scaleHint)
                    text: qmltextActuator
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                }
                BransonComboBox
                {
                    id:firstbox
                    width: Math.round(176 * Style.scaleHint)
                    height: Math.round(32 * Style.scaleHint)
                }
                ProgressBar
                {
                    width: Math.round(180 * Style.scaleHint)
                    height: Math.round(20 * Style.scaleHint)
                    anchors.verticalCenter: firstbox.verticalCenter
                }

            }
            Row
            {
                width: Math.round(640 * Style.scaleHint)
                height: Math.round(39 * Style.scaleHint)
                spacing: Math.round(24 * Style.scaleHint)
                anchors.left: parent.left
                Text {
                    id: secondtext
                    width: Math.round(160 * Style.scaleHint)
                    height: Math.round(32 * Style.scaleHint)
                    text: qmltextPower
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter

                }
                BransonComboBox
                {
                    id:secondbox
                    width:Math.round(176 * Style.scaleHint)
                    height: Math.round(32 * Style.scaleHint)
                }
                ProgressBar
                {
                    width: Math.round(180 * Style.scaleHint)
                    height: Math.round(20 * Style.scaleHint)
                    anchors.verticalCenter: secondbox.verticalCenter
                }
            }
            Row
            {
                width: Math.round(640 * Style.scaleHint)
                height: Math.round(39 * Style.scaleHint)
                spacing: Math.round(24 * Style.scaleHint)
                anchors.left: parent.left
                Text {
                    id: thirdtext
                    width: Math.round(160 * Style.scaleHint)
                    height: Math.round(32 * Style.scaleHint)
                    text: qmltextSupervisor
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                }
                BransonComboBox
                {
                    id:thirdbox
                    width: Math.round(176 * Style.scaleHint)
                    height: Math.round(32 * Style.scaleHint)
                }
                ProgressBar
                {
                    width: Math.round(180 * Style.scaleHint)
                    height: Math.round(20 * Style.scaleHint)
                    anchors.verticalCenter: thirdbox.verticalCenter

                }
            }
        }
    }
}
