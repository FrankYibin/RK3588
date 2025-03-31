/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import Style 1.0
import Com.Branson.UpgradeSoftwareEnum 1.0
import Com.Branson.UIScreenEnum 1.0

Item {
    id: softwareUpgradeView
    property string qmltextMenuName:        qsTr("SOFTWARE UPGRADE")
    property string qmltextUpgradeComments: qsTr("To begin, insert USB drive and click READ USB")
    property string qmltextUpgradeToWelder: qsTr("Insert USB to Welder")
    property string qmltextUpgradeToRaspPi: qsTr("Insert USB to HMI")
    property string qmltextReadUSB:         qsTr("READ USB")
    property string qmltextReading:         qsTr("READING")
    property string qmltextUpgrade:         qsTr("UPGRADE")
    property var qmlTextArray: [qmltextUpgradeComments, qmltextUpgradeToWelder, qmltextUpgradeToRaspPi, qmltextReadUSB, qmltextReading, qmltextUpgrade]
    property color backcolor: "#FFFFFF"
    property int currentIndex:  -1

    function updateLanguage()
    {
        qmltextMenuName = languageConfig.getLanguageMenuName(UIScreenEnum.SYSTEM_SOFTWARE_UPGRADE, qmltextMenuName)
        qmlTextArray = languageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_SOFTWARE_UPGRADE, qmlTextArray)
        qmltextUpgradeComments  = qmlTextArray[textEnum.upgradeCommentsIdx]
        qmltextUpgradeToWelder  = qmlTextArray[textEnum.upgradeToWelderIdx]
        qmltextUpgradeToRaspPi  = qmlTextArray[textEnum.upgradeToRaspPiIdx]
        qmltextReadUSB          = qmlTextArray[textEnum.btnReadUSBIdx]
        qmltextReading          = qmlTextArray[textEnum.btnReadingIdx]
        qmltextUpgrade          = qmlTextArray[textEnum.btnUpgradeIdx]
    }

    function updateSoftwareUpgradeModeTabBar()
    {
        softwareUpgradeTabBarModel.clear()
        softwareUpgradeTabBarModel.append({"Title":      qmltextUpgradeToWelder,
                                           "Width":      170,
                                           "Index":      UpgradeSoftwareEnum.WELDER_SOFTWARE_IDX})
        softwareUpgradeTabBarModel.append({"Title":      qmltextUpgradeToRaspPi,
                                           "Width":      170,
                                           "Index":      UpgradeSoftwareEnum.UICONTROLLER_SOFTWARE_IDX})
    }

    function updateTabBar(index)
    {
        subSoftwareUpgradeDetails.source = ""
        currentIndex = index
        switch(index)
        {
        case UpgradeSoftwareEnum.WELDER_SOFTWARE_IDX:
            subSoftwareUpgradeDetails.source = "qrc:/qmlSource/upgradeWelderWindow.qml"
            break;
        case UpgradeSoftwareEnum.UICONTROLLER_SOFTWARE_IDX:
            subSoftwareUpgradeDetails.source = "qrc:/qmlSource/upgradeHMIWindow.qml"
            break;
        default:
            currentIndex = -1
            break;
        }
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
            updateSoftwareUpgradeModeTabBar()
        }
    }

    QtObject {
        id: textEnum
        readonly property int upgradeCommentsIdx:   0
        readonly property int upgradeToWelderIdx:   1
        readonly property int upgradeToRaspPiIdx:   2
        readonly property int btnReadUSBIdx:        3
        readonly property int btnReadingIdx:        4
        readonly property int btnUpgradeIdx:        5
    }

    Component.onCompleted: {
        updateLanguage()
        updateSoftwareUpgradeModeTabBar()
    }
    
    ListModel {
        id: softwareUpgradeTabBarModel
    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: Style.dialogBackgroundColor
        opacity: 0.75
        MouseArea {
            anchors.fill: parent
        }
    }
    Rectangle {
        width: Math.round(640 * Style.scaleHint)
        height: Math.round(315 * Style.scaleHint)
        anchors.centerIn: parent
        Rectangle {
            id: headerTitle
            width: Math.round(640 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            color: Style.titleBackgroundColor
            Text {
                id: title
                text: qmltextMenuName
                color: Style.whiteFontColor
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(9 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
            }
            Image {
                id: imageClose
                anchors.right: parent.right
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                anchors.verticalCenter: title.verticalCenter
                width: Math.round(24 * Style.scaleHint)
                height: Math.round(24 * Style.scaleHint)

                source: "qrc:/images/crossMark.svg"
                sourceSize.width: imageClose.width
                sourceSize.height: imageClose.height
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        softwareUpgradeView.visible=false
                    }
                }
            }
        }
        Text {
            id: comments
            text: qmltextUpgradeComments
            font.family: Style.regular.name
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            color: Style.blackFontColor
            anchors.top: headerTitle.bottom
            anchors.topMargin: 18
            anchors.left: parent.left
            anchors.leftMargin: 25
        }

        Rectangle {
            id: tabBarBackground
            anchors.left: parent.left
            anchors.top: comments.bottom
            width: headerTitle.width
            height: Math.round(47 * Style.scaleHint)
            color: backcolor
            TabBar {
                id: upgradeTabBar
                anchors.left: parent.left
                anchors.leftMargin: 14
                anchors.verticalCenter: parent.verticalCenter
                width: Math.round(600 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                spacing: 20
                background: Rectangle{
                    color: backcolor
                }

                Repeater {
                    id: tabbtn
                    model: softwareUpgradeTabBarModel
                    delegate: BransonTabButton {
                        width: Math.round(model.Width * Style.scaleHint)
                        height: parent.height
                        tabbtnText: model.Title
                        backgroundColor: backcolor
                        unpressedColor: backcolor
                        onClicked: {
                            updateTabBar(model.Index)
                        }
                    }
                }
            }
        }


        BransonPrimaryButton
        {
            id: btnReadUSB
            width: Math.round(124 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            text:  qmltextReadUSB
            anchors.top: tabBarBackground.bottom
            anchors.right: parent.right
            anchors.rightMargin: Math.round(24 * Style.scaleHint)
            onClicked:
            {
                var path = ["UIController"];
                btnReadUSB.text = qmltextReading
                if(softwareUpgrade.retrieveTargetSoftware(currentIndex, path) === true)
                {
                    switch(currentIndex)
                    {
                    case UpgradeSoftwareEnum.UICONTROLLER_SOFTWARE_IDX:
                        subSoftwareUpgradeDetails.item.comboxModel = path;
                        break;
                    case UpgradeSoftwareEnum.WELDER_SOFTWARE_IDX:
                        break;
                    }
                    btnUpgrade.visible = true
                }
                else
                    btnUpgrade.visible = false

                btnReadUSB.text = qmltextReadUSB
            }
        }


        BransonPrimaryButton
        {
            id: btnUpgrade
            visible: false
            width: Math.round(124 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            text: qmltextUpgrade
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(15 * Style.scaleHint)
            anchors.right: parent.right
            anchors.rightMargin: Math.round(24 * Style.scaleHint)
            onClicked:
            {
                softwareUpgrade.runUpgradeProcess(currentIndex)
            }
        }

        Loader
        {
            id: subSoftwareUpgradeDetails
            anchors.top: btnReadUSB.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 25
            anchors.right: parent.right
            anchors.rightMargin: 9
            anchors.bottom: btnUpgrade.top
            source: "qrc:/qmlSource/upgradeWelderWindow.qml"
        }
    }

}
