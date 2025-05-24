/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 Main
 If you want to run the code on windows you shall run code with debug mode;
 If you want to run the code on target board RK3588, you shall run code with release mode.
 
 **********************************************************************************************************/

import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick 2.15
import QtQuick.VirtualKeyboard 2.15
import QtQuick.VirtualKeyboard.Settings 2.15
import "./qmlSource"
import Style 1.0
import AxisDefine 1.0
import NumpadDefine 1.0
import AlarmDefine 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.RecipeEnum 1.0
Window{
    id: mainWindow
    visible: true
    width: Screen.width
    height: Screen.height
    title: qsTr("UIController")
//    flags: Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint | Qt.Window
    flags: Qt.FramelessWindowHint | Qt.Window
     visibility: Window.FullScreen

    /*1366 * 768 = 1280 * 800    1920 * 1080    800 * 480  */
    /* If you run the code on RK3588, the showWidth should be 800, showHeight should be 480 */
    property int showWidth: 800
    property int showHeight: 480

    property string qmltextTimeMode:                qsTr("Time")
    property string qmltextEnergyMode:              qsTr("Energy")
    property string qmltextPeakPowerMode:           qsTr("Peak Power")
    property string qmltextGroundDetectMode:        qsTr("Scrub Time")
    property string qmltextAbsoluteDistanceMode:    qsTr("Absolute Distance")
    property string qmltextCollapseDistanceMode:    qsTr("Collapse Distance")
    property var qmlTextArray: [qmltextTimeMode, qmltextEnergyMode, qmltextPeakPowerMode,
                                qmltextGroundDetectMode, qmltextAbsoluteDistanceMode, qmltextCollapseDistanceMode]

    signal signalCurrentLanguageChanged()
    signal signalCurrentScreenChanged(int index)

    function getWeldModeText(modeIdx)
    {
        var qmltextWeldMode = ""
        switch(modeIdx)
        {
        case RecipeEnum.TIME_IDX:
            qmltextWeldMode = qmltextTimeMode
            break;
        case RecipeEnum.ENERGY_IDX:
            qmltextWeldMode = qmltextEnergyMode
            break;
        case RecipeEnum.PEAKPOWER_IDX:
            qmltextWeldMode = qmltextPeakPowerMode
            break;
        case RecipeEnum.GROUND_IDX:
            qmltextWeldMode = qmltextGroundDetectMode
            break;
        case RecipeEnum.ABSDISTANCE_IDX:
            qmltextWeldMode = qmltextAbsoluteDistanceMode
            break;
        case RecipeEnum.COLDISTANCE_IDX:
            qmltextWeldMode = qmltextCollapseDistanceMode
            break;
        default:
            qmltextWeldMode = qmltextTimeMode
            break;
        }
        return qmltextWeldMode
    }

    function showFullScreenChart()
    {
        chartViewFullScreen.visible = true
    }

    function hideFullScreenChart()
    {
        chartViewFullScreen.visible = false
    }

    function showLeftActionMenu()
    {
        leftMenuLoader.item.leftActionAnimation.restart()
    }

    function hideLeftActionMenu()
    {
        leftMenuLoader.item.leftActionAnimationReturn.restart()
    }

    function showRightActionMenu()
    {
        rightMenuLoader.item.rightActionAnimation.restart()
    }

    function hideRightActionMenu()
    {
        rightMenuLoader.item.rightActionAnimationReturn.restart()
    }

    function showMainWindowOpacity()
    {
        enableMainWindowOpacity.start()
    }

    function hideMainWindowOpacity()
    {
        disableMainWindowOpacity.start()
    }

    function showLanguageView()
    {
        languageSelectView.visible = true
    }

    function showFaceLogin()
    {
        inputPanel.active = false
        loginLayout.visible = false
        faceRecognition.visible = true
    }

    function showPasswordLogin()
    {
        faceRecognition.visible = false
        // inputPanel.active = true
        loginLayout.visible = true
    }

    function loginProcess()
    {
        loginLayout.visible = false
        mainWindow.hideMainWindowOpacity()
        profileLayout.visible = true
    }

    function logoutProcess()
    {
        loginLayout.visible = true
        mainWindow.hideMainWindowOpacity()
        clearStackView()
    }


    function clearStackView()
    {
        stackMainView.pop(null)
        stackMainView.clear()
        // headerLoader.item.clearChildrenTitleModel()
    }

    function setHeaderTitle(menuName, menuIndex)
    {
        headerLoader.item.appendChildrenTitleModel(menuName, menuIndex)
    }

    function menuParentOptionSelect(menuIndex)
    {
        clearStackView()
        switch(menuIndex)
        {
        // case UIScreenEnum.RECIPES:
        //     stackMainView.push("qrc:/qmlSource/recipeWindow.qml", {}, StackView.Immediate)
        //     break;
        // case UIScreenEnum.PRODUCTION:
        //     stackMainView.push("qrc:/qmlSource/productionWindow.qml", {}, StackView.Immediate)
        //     break;
        // case UIScreenEnum.ANALYTICS:
        //     stackMainView.push("qrc:/qmlSource/analyticsWindow.qml", {}, StackView.Immediate)
        //     break;
        // case UIScreenEnum.SYSTEM:
        //     stackMainView.push("qrc:/qmlSource/systemWindow.qml", {}, StackView.Immediate)
        //     break;
        // case UIScreenEnum.ACTUATORSETUP:
        //     stackMainView.push("qrc:/qmlSource/BransonHornDown.qml",{}, StackView.Immediate)
        //     break;
        // case UIScreenEnum.DIAGNOSTICS:
        //     break;
        // case UIScreenEnum.IMPORTEXPORT:
        //     break;
        case UIScreenEnum.HB_PROFILE:
            stackMainView.push("qrc:/qmlSource/unitProfileWindow.qml", {}, StackView.Immediate)
            break;
        case UIScreenEnum.HB_DASHBOARD:
            stackMainView.push("qrc:/qmlSource/dashboardWindow.qml", {}, StackView.Immediate)
            break;
        case UIScreenEnum.HB_SETTING:
            stackMainView.push("qrc:/qmlSource/settingWindow.qml", {}, StackView.Immediate)
            break;
        case UIScreenEnum.HB_VELOCITY:
            stackMainView.push("qrc:/qmlSource/testVelocityWindow.qml", {}, StackView.Immediate)
            break;
        default:
            break;
        }
    }

    function menuChildOptionSelect(parentMenuIndex, childMenuIndex)
    {
        switch(childMenuIndex)
        {
        case UIScreenEnum.RECIPES_LAB:
            if(parentMenuIndex === UIScreenEnum.RECIPES)
            {
                stackMainView.push("qrc:/qmlSource/recipeLabWindow.qml", {}, StackView.Immediate)
            }
            break;
        case UIScreenEnum.SYSTEM_INFO:
            if(parentMenuIndex === UIScreenEnum.SYSTEM)
            {
                stackMainView.push("qrc:/qmlSource/systemInformationWindow.qml", {}, StackView.Immediate)
            }
            break;
        case UIScreenEnum.HB_HISTORY_DATA:
            if(parentMenuIndex === UIScreenEnum.HB_SETTING)
            {
                leftNavigateMenu.item.updateChildModel(UIScreenEnum.HB_HISTORY_DATA, "")
                stackMainView.push("qrc:/qmlSource/historyDataWindow.qml", {}, StackView.Immediate)
            }
            break;
        case UIScreenEnum.HB_SYSTEM_CONFIG:
            if(parentMenuIndex === UIScreenEnum.HB_SETTING)
            {
                leftNavigateMenu.item.updateChildModel(UIScreenEnum.HB_SYSTEM_CONFIG, "")
                stackMainView.push("qrc:/qmlSource/systemSettingsWindow.qml", {}, StackView.Immediate)
            }
            break;
        case UIScreenEnum.HB_WELL_PARAMETERS:
            if(parentMenuIndex === UIScreenEnum.HB_SETTING)
            {
                leftNavigateMenu.item.updateChildModel(UIScreenEnum.HB_WELL_PARAMETERS, "")
                stackMainView.push("qrc:/qmlSource/wellParametersWindow.qml", {}, StackView.Immediate)
            }
            break;
        case UIScreenEnum.HB_TENSIONS_SETTING:
            if(parentMenuIndex === UIScreenEnum.HB_SETTING)
            {
                leftNavigateMenu.item.updateChildModel(UIScreenEnum.HB_TENSIONS_SETTING, "")
                stackMainView.push("qrc:/qmlSource/tensionsSettingsWindow.qml", {}, StackView.Immediate)
            }
            break;
        case UIScreenEnum.HB_DEPTH_SETTING:
            if(parentMenuIndex === UIScreenEnum.HB_SETTING)
            {
                leftNavigateMenu.item.updateChildModel(UIScreenEnum.HB_DEPTH_SETTING, "")
                stackMainView.push("qrc:/qmlSource/depthSettingsWindow.qml", {}, StackView.Immediate)
            }
            break;
        case UIScreenEnum.HB_USER_MANAGEMENT:
            if(parentMenuIndex === UIScreenEnum.HB_SETTING)
            {
                leftNavigateMenu.item.updateChildModel(UIScreenEnum.HB_USER_MANAGEMENT, "")
                stackMainView.push("qrc:/qmlSource/userManagementWindow.qml", {}, StackView.Immediate)
            }
            break;
        case UIScreenEnum.HB_HELP:
            if(parentMenuIndex === UIScreenEnum.HB_SETTING)
            {
                leftNavigateMenu.item.updateChildModel(UIScreenEnum.HB_HELP, "")
                stackMainView.push("qrc:/qmlSource/helpInfoWindow.qml", {}, StackView.Immediate)
            }
            break;
        default:
            break;
        }
    }

    function menuOptionLookAt(index)
    {
        var objItem = stackMainView.find(function(item) { return (item.qmlscreenIndicator === index)})
        if(objItem !== null)
        {
            var size = stackMainView.depth
            // while((stackMainView.get(size - 1) !== objItem) && (size > 0))
            // {
            //     stackMainView.pop({immediate: true})
            //     size = stackMainView.depth
            // }
            if((stackMainView.get(size - 1) === objItem) && (size > 0))
            {
                stackMainView.pop({immediate: true})
            }
        }
    }

    function showPrimaryNumpad(strTitle, strUnit, iDecimals, realMinimum, realMaximum, strCurrentValue, targetObj,onConfirmCallback)
    {
        primaryNumpad.headertext = strTitle
        primaryNumpad.suffix = strUnit
        primaryNumpad.decimals = iDecimals
        primaryNumpad.minimumValue = realMinimum
        primaryNumpad.maximumValue = realMaximum
        primaryNumpad.value = strCurrentValue
        primaryNumpad.targetTextField = targetObj
        primaryNumpad.confirmCallback = onConfirmCallback
        primaryNumpad.visible = true
    }

    function showSteppingNumpad(strTitle, strUnit, iDecimals, realMinimum, realMaximum, strCurrentValue)
    {
        steppingNumpad.headertext = strTitle
        steppingNumpad.suffix = strUnit
        steppingNumpad.decimals = iDecimals
        steppingNumpad.minimumValue = realMinimum
        steppingNumpad.maximumValue = realMaximum
        steppingNumpad.value = strCurrentValue
        steppingNumpad.visible = true
    }

    function showDepthCountDown()
    {
        depthCountDown.visible = true
    }

    Connections {
        target: languageConfig
        function onSignalCurrentLanguageChanged()
        {
            mainWindow.hideMainWindowOpacity()
            qmlTextArray = languageConfig.getLanguageStringList(UIScreenEnum.WELDMODE_VALUE_LOWERSTRING, qmlTextArray)
            qmltextTimeMode             = qmlTextArray[textEnum.timeModeIdx]
            qmltextEnergyMode           = qmlTextArray[textEnum.energyModeIdx]
            qmltextPeakPowerMode        = qmlTextArray[textEnum.peakPowerModeIdx]
            qmltextGroundDetectMode     = qmlTextArray[textEnum.groundDetectModeIdx]
            qmltextAbsoluteDistanceMode = qmlTextArray[textEnum.absoluteDistanceModeIdx]
            qmltextCollapseDistanceMode = qmlTextArray[textEnum.collapseDistanceModeIdx]
            NumpadDefine.updateLanguage()
            AxisDefine.updateLanguage()
            AlarmDefine.updateLanguage()
            signalCurrentLanguageChanged()
        }
    }

    QtObject {
        id: textEnum
        readonly property int timeModeIdx:              0
        readonly property int energyModeIdx:            1
        readonly property int peakPowerModeIdx:         2
        readonly property int groundDetectModeIdx:      3
        readonly property int absoluteDistanceModeIdx:  4
        readonly property int collapseDistanceModeIdx:  5
    }

    Rectangle{
        id: background
        anchors.fill: parent
        color: Style.backgroundColor
        Component.onCompleted: {
            if(debug === true)
            {
                if(Screen.width !== showWidth)
                {
                    if(Screen.width > 1279 && Screen.width < 1901) //1366 X 768 or 1280 X 800 10inches
                    {
                        console.debug("1366 X 768 10inches screen resolution:", Screen.width)
                        Style.scaleHint = 1.6
                        mainWindow.showWidth = Screen.width
                        mainWindow.showHeight = Screen.height
                    }
                    else if(Screen.width > 1900)    //1920 X 1080 biggest screen
                    {
                        console.debug("1920 x 1080 biggest screen resolution")
                        // Style.scaleHint = 2.4
                        // mainWindow.showWidth = Screen.width
                        // mainWindow.showHeight = Screen.height
                        Style.scaleHint = 1.6
                    }
                    else                            //800 X 480 7inches
                    {
                        console.debug("800 X 480 7inches screen")
                        Style.scaleHint = 1.0
                    }
                }
            }
            else
            {
                Style.scaleHint = Screen.width / showWidth;
                mainWindow.showWidth = Screen.width
                mainWindow.showHeight = Screen.height
            }
            var str = "Screen resolution:" + Screen.width + "X" + Screen.height
            console.debug(str)
            console.debug("scale: ", Style.scaleHint)
            // leftMenuLoader.source = ""
            // leftMenuLoader.source = "qrc:/qmlSource/leftActionMenu.qml"
            // rightMenuLoader.source = ""
            // rightMenuLoader.source = "qrc:/qmlSource/rightActionMenu.qml"
            leftNavigateMenu.source = ""
            leftNavigateMenu.source = "qrc:/qmlSource/leftNavigateMenu.qml"
        }
    }

    Item{
        id: windowArea
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
        visible: true
        Image {
            source: "qrc:/images/bg1.png"
            anchors.fill: parent
            smooth: true
        }
        // Loader{
        //     id: headerLoader
        //     width: parent.width
        //     anchors.top: parent.top
        //     height: Math.round(50 * Style.scaleHint)
        //     source:  "qrc:/qmlSource/header.qml"
        // }

        // Loader{
        //     id: leftMenuLoader
        //     anchors.left: headerLoader.left
        //     anchors.top: parent.top
        //     width: parent.width
        //     height: parent.height
        //     z: 2
        // }

        // Loader{
        //     id: rightMenuLoader
        //     anchors.right: headerLoader.right
        //     anchors.top: parent.top
        //     width: parent.width
        //     height: parent.height
        //     z: 2
        // }

        Loader{
            id: leftNavigateMenu
            anchors.top: parent.top
            anchors.topMargin: Math.round(20 * Style.scaleHint)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(20 * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin: Math.round(15 * Style.scaleHint)
            width: Math.round(70 * Style.scaleHint)
        }

        StackView{
            id: stackMainView
            anchors.top: parent.top
            anchors.topMargin: Math.round(20 * Style.scaleHint)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(20 * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin: Math.round(100 * Style.scaleHint)
            anchors.right: parent.right
            anchors.rightMargin: Math.round(20 * Style.scaleHint)
        }

        Rectangle
        {
            id: mainWindowOpacity
            anchors.centerIn: parent
            width: mainWindow.showWidth
            height: mainWindow.showHeight
            color: Style.mainWindowOpacityColor
            z: -1
            OpacityAnimator on opacity
            {
                id: enableMainWindowOpacity
                from: 0
                to: 0.5
                duration: 250
                target: mainWindowOpacity
                onRunningChanged: {
                    if(enableMainWindowOpacity.running)
                    {
                        mainWindowOpacity.z = 1
                    }
                }
            }

            OpacityAnimator on opacity
            {
                id: disableMainWindowOpacity
                from: 0.5
                to: 0
                duration: 250
                target: mainWindowOpacity
                onRunningChanged: {
                    if(disableMainWindowOpacity.running)
                    {
                        mainWindowOpacity.z = -1
                    }
                    else
                    {
                        mainWindowOpacity.z = -1
                    }
                }
            }
        }

        NormalScreenAlarmNotificationWindow {
            id: alarmNotificationNormalScreen
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            scaleRate: Math.sqrt(1/6)
            width: parent.width * scaleRate
            height: parent.height * scaleRate
            visible: false

        }
    }

    TranslationView {
        id: languageSelectView
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    /*update*/
    SoftwareUpgradeView {
        id: softwareUpgrading
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    /*KeyBoard*/
    BransonPrimaryNumpad
    {
        id:primaryNumpad
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
        z: 2
    }

    BransonSetupLimitNumpad
    {
        id:setupLimitNumpad
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    BransonSuspectRejectNumpad
    {
        id:suspectRejectNumpad
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    BransonControlLimitNumpad
    {
        id:controlLimitNumpad
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    BransonSteppingNumpad
    {
        id:steppingNumpad
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    FullScreenGraphWindow {
        id: chartViewFullScreen
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    FullScreenAlarmNotificationWindow {
        id: alarmNotificationFullScreen
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    Login
    {
        id: loginLayout
        visible: true
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    LoginFaceRecognition
    {
        id: faceRecognition
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    ProfileWindow
    {
        id: profileLayout
        visible: false
        anchors.centerIn:  parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    InputPanel {
        id: inputPanel
        visible: false
        z: 2
        y: windowArea.y + windowArea.height
        anchors.left: windowArea.left
        anchors.right: windowArea.right
        // active: false
        states:
            State {
                name: "visible"
                when: (inputPanel.active === true) ? true : false
                PropertyChanges {
                    target: inputPanel
                    y: windowArea.y + windowArea.height - inputPanel.height
                    visible: true
                }
            }

        transitions:
            Transition {
                from: ""
                to: "visible"
                reversible: true
                ParallelAnimation {
                    NumberAnimation {
                        properties: "y"
                        duration: 250
                        easing.type: Easing.OutQuart
                    }
                }
            }

        Component.onCompleted: {
//            VirtualKeyboardSettings.locale = sysconfig.getLanguageCode()
            VirtualKeyboardSettings.locale = "en_US"
        }
    }

    HBDepthCountDown {
        id: depthCountDown
        width: showWidth / 2
        height: showHeight / 2
        visible: false
        x: parent.width / 2
        y: parent.height / 2
    }
}
