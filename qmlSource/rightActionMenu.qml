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
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.LanguageEnum 1.0
Item {
    property alias machineName: machineText.text
    property alias machineTimer: machineTime.text

    readonly property int arcWidth: Math.round((732-359) * Style.scaleHint)
    readonly property int arcRadius: Math.round(732 / 2 * Style.scaleHint)
    readonly property int centerX: Math.round(arcWidth - arcRadius)
    readonly property int centerY: Math.round(height / 2)
    readonly property int imageSize: Math.round(30 * Style.scaleHint)
    readonly property int menuSepratorHeight: (Style.scaleHint === 1.0)? 1 : 2
    property alias rightActionAnimation: rightActionAnimation

    //qsTr can keep the word with English as the default without any messy code on the others Windows OS.
    property string qmltextActionCenter:            qsTr("Action Center")
    readonly property string qmltextActuatorSetup:  qsTr("Actuator Setup")
    readonly property string qmltextDiagnostics:    qsTr("Diagnostics")
    readonly property string qmltextImportExport:   qsTr("Import/ Export")
    property string qmltextLanguage:                qsTr("English")
    readonly property string qmltextLogout:         qsTr("Logout")
    readonly property string qmltextExit:           qsTr("Exit")
    property string qmltextMachine:                 qsTr("Machine: ")
    property var qmlTextArray: [qmltextActionCenter, qmltextActuatorSetup, qmltextDiagnostics, qmltextImportExport, qmltextLogout, qmltextExit, qmltextMachine]

    property var menuName: ""
    property var menuIndex: 0

    id: rightActionCenterItem

    function updateLanguage()
    {
        qmltextLanguage = languageModel.getLanguageName(languageConfig.CurrentLanguage)
        qmlTextArray = languageConfig.getLanguageStringList(UIScreenEnum.RIGHTMENU, qmlTextArray)

        qmltextActionCenter = qmlTextArray[textEnum.actionCenterIdx]
        rightMenuModelData.set(0, {"MenuName": qmlTextArray[textEnum.actuatorSetupIdx]})
        rightMenuModelData.set(1, {"MenuName": qmlTextArray[textEnum.diagnosticsIdx]})
        rightMenuModelData.set(2, {"MenuName": qmlTextArray[textEnum.importExportIdx]})
        systemModelData.set(0, {"MenuName": qmltextLanguage})
        systemModelData.set(1, {"MenuName": qmlTextArray[textEnum.logoutIdx]})
        systemModelData.set(2, {"MenuName": qmlTextArray[textEnum.exitIdx]})
        qmltextMachine = qmlTextArray[textEnum.machineIdx]
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted:
    {
        rightActionAnimationReturn.restart()
        rightMenuModelData.resetModel()
        systemModelData.resetModel()
        updateLanguage()
    }

    QtObject {
        id: textEnum
        readonly property int actionCenterIdx:  0
        readonly property int actuatorSetupIdx: 1
        readonly property int diagnosticsIdx:   2
        readonly property int importExportIdx:  3
        readonly property int logoutIdx:        4
        readonly property int exitIdx:          5
        readonly property int machineIdx:       6
    }

    ListModel {
        id: rightMenuModelData
        function resetModel()
        {
            rightMenuModelData.clear()
            rightMenuModelData.append({"MenuName":   qmltextActuatorSetup,
                                    "MenuIcon":     "qrc:/images/actuatorSetup.svg",
                                    "MenuAction":   "ActuatorSetup.qml",
                                    "MenuColor":    "#ffffff",
                                    "MenuIndex":    UIScreenEnum.ACTUATORSETUP,
                                    "MenuVisible":  true,
                                    "MenuSeparator": true
                                    })
            rightMenuModelData.append({"MenuName":   qmltextDiagnostics,
                                     "MenuIcon":     "qrc:/images/diagnostics.svg",
                                    "MenuAction":   "DiagnosticsView.qml",
                                    "MenuColor":    "#ffffff",
                                    "MenuIndex":    UIScreenEnum.DIAGNOSTICS,
                                    "MenuVisible":  true,
                                    "MenuSeparator": true
                                    })
            rightMenuModelData.append({"MenuName":   qmltextImportExport,
                                     "MenuIcon":     "qrc:/images/importExport.svg",
                                    "MenuAction":   "ImportExportView.qml",
                                    "MenuColor":    "#ffffff",
                                    "MenuIndex":    UIScreenEnum.IMPORTEXPORT,
                                    "MenuVisible":  true,
                                    "MenuSeparator": true
                                    })
        }
    }

    ListModel {
        id: systemModelData
        function resetModel()
        {
            systemModelData.clear()
            systemModelData.append({"MenuName":     qmltextLanguage,
                                   "MenuIcon":      "qrc:/images/Language2.svg",
                                   "MenuAction":    "LanguageView.qml",
                                   "MenuColor":     "#ffffff",
                                   "MenuIndex":     UIScreenEnum.LANGUAGE,
                                   "MenuVisible":   true
                                   })
            systemModelData.append({"MenuName":     qmltextLogout,
                                   "MenuIcon":      "qrc:/images/Logout Icon.svg",
                                   "MenuAction":    "Logout.qml",
                                   "MenuColor":     "#ffffff",
                                   "MenuIndex":     UIScreenEnum.LOGOUT,
                                   "MenuVisible":   true
                                   })
            systemModelData.append({"MenuName":     qmltextExit,
                                   "MenuIcon":      "qrc:/images/Power Off Icon.svg",
                                   "MenuAction":    "Exit.qml",
                                   "MenuColor":     "#ffffff",
                                   "MenuIndex":     UIScreenEnum.EXIT,
                                   "MenuVisible":   true
                                   })
        }
    }


    NumberAnimation on x
    {
        id: rightActionAnimationReturn
        from: width - arcWidth ;
        to: width
        duration: 250
    }

    NumberAnimation on x
    {
        id: rightActionAnimation
        from: width
        to: 0
        duration: 250
    }

    Timer {
        interval: 30000 // each update per half a minute
        repeat: true
        running: true
        onTriggered: {
            machineTimer = Qt.formatDateTime(new Date(), "hh:mm AP")
        }
    }

    Rectangle {
        id: rootRectangle
        color: "transparent"
        anchors.top: parent.top
        anchors.right: parent.right
        width:  arcWidth
        height: parent.height
        z: 3
        //For mobile screen and small screen Canvas element is not required
        Canvas{
            id: canvash
            anchors.right: parent.right
            anchors.top: parent.top
            width: rootRectangle.width
            height: rootRectangle.height
            opacity: 0.8
            onPaint:
            {
                var ctx = getContext("2d")
                ctx.fillStyle = Style.navigationMenuBackgroundColor
                ctx.beginPath()
                ctx.arc(width, centerY, arcRadius, 1.5 * Math.PI, 0.5 * Math.PI, true)
                ctx.fill()
            }
            MouseArea
            {
                anchors.fill: parent
            }
        }

        Item{
            id: menuDetails
            width: parent.width
            height: parent.height
            anchors.right: parent.Right
            anchors.top: parent.top
            Item {
                id: actionCenterButton
                anchors.right: parent.right
                anchors.rightMargin: Math.round(12 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: Math.round(14 * Style.scaleHint)
                height: imageSize
                width: Math.round(180 * Style.scaleHint)
                Rectangle {
                    anchors.fill: parent
                    border.color: "transparent"
                    color: "transparent"
                    Row{
                        id: menuLayout
                        spacing: Math.round(10 * Style.scaleHint)
                        layoutDirection: Qt.RightToLeft
                        Image
                        {
                            id: imageMenu
                            width: imageSize
                            height: imageSize
                            source: "qrc:/images/menu_close_arrow_rightMenu.svg"
                            fillMode: Image.PreserveAspectFit
                            sourceSize.width: imageSize
                            sourceSize.height: imageSize
                            smooth: true
                            mirror: true
                        }

                        Text {
                            text: qmltextActionCenter
                            height: imageSize
                            font.family: Style.regular.name
                            font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                            color: Style.whiteFontColor
                        }
                    }
                    MouseArea
                    {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered:
                        {
                            cursorShape = Qt.PointingHandCursor
                        }
                        onClicked:
                        {
                            rightActionAnimationReturn.restart()
                            mainWindow.hideMainWindowOpacity()
                        }
                    }
                }
            }

            Item {
                id: menuParentList
                anchors.left: parent.left
                anchors.leftMargin: Math.round(113 * Style.scaleHint)
                anchors.top: actionCenterButton.bottom
                anchors.topMargin: Math.round(30 * Style.scaleHint)
                anchors.right: parent.right
                height: Math.round(219 * Style.scaleHint)
                Column
                {
                    id: menuOptionLayout
                    anchors.fill: parent
                    spacing: Math.round(22 * Style.scaleHint)
                    Repeater
                    {
                        model: rightMenuModelData
                        delegate: Item
                        {
                            id: menuOptionDelegate
                            height: imageSize + Math.round(22 * Style.scaleHint)
                            width: parent.width
                            Rectangle{
                                id: menuImageTextLayout
                                height: imageSize
                                width: parent.width
                                color: "transparent"
                                border.color: "transparent"
                                Row
                                {
                                    spacing: Math.round(21 * Style.scaleHint)
                                    Image{
                                        id: menuOptionImage
                                        width: imageSize
                                        height: imageSize
                                        source: model.MenuIcon
                                        fillMode: Image.PreserveAspectFit
                                        sourceSize.width: imageSize
                                        sourceSize.height: imageSize
                                        smooth: true
                                    }
                                    Text{
                                        height: imageSize
                                        color: model.MenuColor
                                        font.family: Style.regular.name
                                        text: model.MenuName
                                        anchors.verticalCenter: menuOptionImage.verticalCenter
                                        verticalAlignment: Text.AlignVCenter
                                        font.pixelSize: Math.round(Style.style7 * Style.scaleHint)
                                    }
                                }

                                MouseArea
                                {
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered:
                                    {
                                        cursorShape = Qt.PointingHandCursor
                                    }
                                    onClicked:
                                    {
                                        rightActionAnimationReturn.restart()
                                        mainWindow.hideMainWindowOpacity()
                                        menuIndex = model.MenuIndex
                                        menuName = model.MenuName
                                        mainWindow.menuParentOptionSelect( menuIndex)

                                    }
                                }
                            }

                            Rectangle{
                                id: lineSeparator
                                width: Math.round(221 * Style.scaleHint)
                                height: menuSepratorHeight
                                anchors.left: menuImageTextLayout.left
                                anchors.top: menuImageTextLayout.bottom
                                anchors.topMargin: Math.round(20 * Style.scaleHint)
                                color: Style.whiteFontColor
                                visible: model.MenuSeparator
                            }
                        }
                    }
                }
            }


            Item {
                id: menuSystemList
                anchors.left: parent.left
                anchors.leftMargin: Math.round(144 * Style.scaleHint)
                anchors.top: menuParentList.bottom
                anchors.right: parent.right
                anchors.bottom: parent.bottom

                Row
                {
                    id: menuSystemLayout
                    anchors.fill: parent
                    spacing: Math.round(39 * Style.scaleHint)
                    Repeater
                    {
                        model: systemModelData
                        delegate: Item
                        {
                            id: systemOptionDelegate
                            height: parent.height
                            width: imageSize
                            Rectangle{
                                id: systemImageTextLayout
                                width: imageSize
                                height: imageSize + imageSize
                                color: "transparent"
                                Image{
                                    id: systemOptionImage
                                    width: imageSize
                                    height: imageSize
                                    source: model.MenuIcon
                                    fillMode: Image.PreserveAspectFit
                                    sourceSize.width: imageSize
                                    sourceSize.height: imageSize
                                    smooth: true
                                }
                                Text{
                                    id: systemOptionText
                                    anchors.top: systemOptionImage.bottom
                                    height: imageSize
                                    color: model.MenuColor
                                    font.family: Style.regular.name
                                    text: model.MenuName
                                    anchors.horizontalCenter: systemOptionImage.horizontalCenter
                                    verticalAlignment: Text.AlignVCenter
                                    font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                                }
                            }
                            MouseArea
                            {
                                id: mouseAreaSystemOption
                                anchors.fill: systemImageTextLayout
                                hoverEnabled: true
                                onEntered:
                                {
                                    cursorShape = Qt.PointingHandCursor
                                }
                                onClicked:
                                {
                                    rightActionAnimationReturn.restart()
                                    if(model.MenuIndex === UIScreenEnum.EXIT)
                                    {
                                        communicationInterface.closeSocket();
                                        Qt.quit()
                                    }
                                    else if(model.MenuIndex === UIScreenEnum.LANGUAGE)
                                    {
                                        mainWindow.hideMainWindowOpacity()
                                        mainWindow.showLanguageView()
                                    }
                                    else if(model.MenuIndex === UIScreenEnum.LOGOUT)
                                    {
                                        mainWindow.logoutProcess()
                                    }
                                }
                            }
                        }
                    }
                }
            }


            Rectangle {
                id: machineInfo
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(6 * Style.scaleHint)
                height: Math.round(imageSize / 2)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(122 * Style.scaleHint)
                color: "transparent"
                border.color: "transparent"
                Text {
                    id: machineTitle
                    anchors.left: parent.left
                    anchors.top: parent.top
                    width: Math.round(60 * Style.scaleHint)
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                    color: Style.whiteFontColor
                    verticalAlignment: Text.AlignVCenter
                    text: qmltextMachine
                }

                Text {
                    id: machineText
                    anchors.left: machineTitle.right
                    anchors.top: parent.top
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }

                Image {
                    id: machineImage
                    anchors.left: machineTitle.right
                    anchors.leftMargin: Math.round(80 * Style.scaleHint)
                    anchors.top: parent.top
                    width: Math.round(imageSize / 2)
                    height: Math.round(imageSize / 2)
                    source: "qrc:/images/systemTimer.svg"
                    fillMode: Image.PreserveAspectFit
                    sourceSize.width: machineImage.width
                    sourceSize.height: machineImage.height
                    smooth: true
                }

                Text {
                    id: machineTime
                    anchors.left: machineImage.right
                    anchors.leftMargin: Math.round(6 * Style.scaleHint)
                    anchors.top: parent.top
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }

        }
    }

    Rectangle {
        id: rightMenuOutsideArea
        width: parent.width/5 + parent.width - arcWidth
        height: parent.height
        opacity: 0
        anchors.left: parent.left
        anchors.top: parent.top
        color: "transparent"
        visible: true
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                rightActionAnimationReturn.restart()
                mainWindow.hideMainWindowOpacity()
            }
        }
    }
}
