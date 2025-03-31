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
    property string qmltextHMI:        qsTr("UI Controller")
    property color backcolor: "#FFFFFF"
    property alias comboxModel: hmiComboBox.model
    property alias currentText: hmiComboBox.currentText
    function updateLanguage()
    {
        qmltextHMI = languageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_SOFTWARE_UPGRADE_RASPPI, qmltextHMI)
    }
//    function delay()
//    {
//        var sleep = function(time) {
//            var startTime = new Date().getTime() + parseInt(time, 10);
//            while(new Date().getTime() < startTime) {}
//        };
//        sleep(1000)
//    }

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
                    id: textHMI
                    width: Math.round(160 * Style.scaleHint)
                    height: Math.round(32 * Style.scaleHint)
                    text: qmltextHMI
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                }
                BransonComboBox
                {
                    id: hmiComboBox
                    minWidth: Math.round(176 * Style.scaleHint)
                    minHeight: Math.round(32 * Style.scaleHint)
                }
                ProgressBar
                {
                    width: Math.round(180 * Style.scaleHint)
                    height: Math.round(20 * Style.scaleHint)
                    anchors.verticalCenter: hmiComboBox.verticalCenter
                    value: softwareUpgrade.CurrentProgressValue
                }
            }
        }
    }
}
