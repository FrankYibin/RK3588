/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/
import QtQuick 2.12
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import QtQuick 2.15
import QtGraphicalEffects 1.15
import Style 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
Item {
    id: recipeLabWindow
    readonly property int qmlscreenIndicator:   UIScreenEnum.RECIPES_LAB
    readonly property color shadowColor: "#000000"

    property string qmltextMenuName:        qsTr("Lab")
    property string qmltextRecipeActions:   qsTr("Actions")
    property string qmltextRecipeNew:       qsTr("New")
    property string qmltextRecipeSave:      qsTr("Save")
    property string qmltextRecipeCopy:      qsTr("Copy")
    property string qmltextRecipeValidate:  qsTr("Validate")


    property string qmltextQuickEdit:       qsTr("QUICK EDIT")
    property string qmltextTime:            qsTr("TIME")
    property string qmltextEnergy:          qsTr("ENERGY")
    property string qmltextPeakPower:       qsTr("PEAK POWER")
    property string qmltextAbsoluteDistance:qsTr("ABSOLUTE DISTANCE")
    property string qmltextCollapseDistance:qsTr("COLLAPSE DISTANCE")
    property string qmltextScrubTime:       qsTr("SCRUB TIME")
    property string qmltextWeldAmplitude:   qsTr("WELD AMPLITUDE")
    property string qmltextHoldTime:        qsTr("HOLD TIME")

    property string qmltextWeldProcess:     qsTr("Weld Process")
    property string qmltextWeldMode:        qsTr("Weld Mode")
    property string qmltextParametersA2Z:   qsTr("Parameters A-Z")
    property string qmltextLimit:           qsTr("Limits")
    property string qmltextStackRecipe:     qsTr("Stack Recipe")
    property string qmltextPretrigger:      qsTr("Pretrigger")
    property string qmltextAfterburst:      qsTr("Afterburst")
    property string qmltextSetup:           qsTr("Setup")
    property string qmltextControl:         qsTr("Control")
    property string qmltextSuspectReject:   qsTr("Suspect & Reject")

    property string qmltextRecipeSetting:   qsTr("RECIPE SETTINGS")
    property string qmltextResultView:      qsTr("RESULT VIEW")
    property string qmltextGraphSetting:    qsTr("GRAPH SETTINGS")

    property var qmlTextArray: [qmltextRecipeActions, qmltextRecipeNew, qmltextRecipeSave,
        qmltextRecipeCopy, qmltextRecipeValidate, qmltextQuickEdit, qmltextTime,
        qmltextEnergy, qmltextPeakPower, qmltextAbsoluteDistance, qmltextCollapseDistance,
        qmltextScrubTime, qmltextWeldAmplitude, qmltextHoldTime]

    property var recipeActionsModel: [qmltextRecipeNew, qmltextRecipeSave, qmltextRecipeCopy, qmltextRecipeValidate]


    property string strRecipeNumber: "8"
    property string strRecipeName: "NewRecipe"
    property int imageSize: Math.round(20 * Style.scaleHint)
    property int imageBigSize: Math.round(30 * Style.scaleHint)
    property int currentTabBarIndex: 0
    property int currentWeldMode: RecipeEnum.TIME_IDX

    QtObject {
        id: textEnum
        readonly property int textRecipeActionsIdx:     0
        readonly property int textRecipeNewIdx:         1
        readonly property int textRecipeSaveIdx:        2
        readonly property int textRecipeCopyIdx:        3
        readonly property int textRecipeValidateIdx:    4
        readonly property int textQuickEditIdx:         5
        readonly property int textTimeIdx:              6
        readonly property int textEnergyIdx:            7
        readonly property int textPeakPowerIdx:         8
        readonly property int textAbsoluteDistanceIdx:  9
        readonly property int textCollapseDistanceIdx:  10
        readonly property int textScrubTimeIdx:         11
        readonly property int textWeldAmplitudeIdx:     12
        readonly property int textHoldTimeIdx:          13

    }

    QtObject {
        id: enumTabBarIndex
        readonly property int weldModeIdx:      0
        readonly property int weldProcessIdx:   1
        readonly property int parametersA2ZIdx: 2
        readonly property int limitIdx:         3
        readonly property int stackRecipeIdx:   4
        readonly property int pretriggerIdx:    5
        readonly property int afterburstIdx:    6
        readonly property int setupIdx:         7
        readonly property int controlIdx:       8
        readonly property int suspectRejectIdx: 9
    }

    function updateLanguage()
    {
        qmlTextArray = languageConfig.getLanguageStringList(UIScreenEnum.RECIPES_LAB_SETTING, qmlTextArray)
        qmltextRecipeActions =      qmlTextArray[textEnum.textRecipeActionsIdx]
        qmltextRecipeNew =          qmlTextArray[textEnum.textRecipeSaveIdx]
        qmltextRecipeSave =         qmlTextArray[textEnum.textRecipeCopyIdx]
        qmltextRecipeCopy =         qmlTextArray[textEnum.textRecipeCopyIdx]
        qmltextRecipeValidate =     qmlTextArray[textEnum.textRecipeValidateIdx]
        qmltextQuickEdit =          qmlTextArray[textEnum.textQuickEditIdx]
        qmltextTime =               qmlTextArray[textEnum.textTimeIdx]
        qmltextEnergy =             qmlTextArray[textEnum.textEnergyIdx]
        qmltextPeakPower =          qmlTextArray[textEnum.textPeakPowerIdx]
        qmltextAbsoluteDistance =   qmlTextArray[textEnum.textAbsoluteDistanceIdx]
        qmltextCollapseDistance =   qmlTextArray[textEnum.textCollapseDistanceIdx]
        qmltextScrubTime =          qmlTextArray[textEnum.textScrubTimeIdx]
        qmltextWeldAmplitude =      qmlTextArray[textEnum.textWeldAmplitudeIdx]
        qmltextHoldTime =           qmlTextArray[textEnum.textHoldTimeIdx]
        qmltextMenuName = languageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB, qmltextMenuName)
        qmltextWeldProcess = languageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_WELDPROCESS, qmltextWeldProcess)
        qmltextWeldMode = languageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_WELDMODE, qmltextWeldMode)
        qmltextParametersA2Z = languageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_PARAMETERA2Z, qmltextParametersA2Z)
        qmltextLimit = languageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_LIMITS, qmltextLimit)
        qmltextStackRecipe = languageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_STACKRECIPE, qmltextStackRecipe)
        qmltextPretrigger = languageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_WELDPROCESS_PRETRIGGER, qmltextPretrigger)
        qmltextAfterburst = languageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_WELDPROCESS_AFTERBURST, qmltextAfterburst)
        qmltextSetup = languageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_LIMITS_SETUP, qmltextSetup)
        qmltextControl = languageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_LIMITS_CONTROL, qmltextControl)
        qmltextSuspectReject = languageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_LIMITS_SUSPECT_REJECT, qmltextSuspectReject)
        qmltextRecipeSetting = languageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_SETTING, qmltextRecipeSetting)
        qmltextResultView = languageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_RESULTVIEW, qmltextResultView)
        qmltextGraphSetting = languageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_GRAPHSETTING, qmltextGraphSetting)
        switch(currentTabBarIndex)
        {
        case enumTabBarIndex.weldModeIdx:
        case enumTabBarIndex.parametersA2ZIdx:
        case enumTabBarIndex.stackRecipeIdx:
            recipeTabBarModel.setProperty(0, "Title", qmltextWeldMode)
            recipeTabBarModel.setProperty(1, "Title", qmltextWeldProcess)
            recipeTabBarModel.setProperty(2, "Title", qmltextParametersA2Z)
            recipeTabBarModel.setProperty(3, "Title", qmltextLimit)
            recipeTabBarModel.setProperty(4, "Title", qmltextStackRecipe)
            break
        case enumTabBarIndex.weldProcessIdx:
        case enumTabBarIndex.pretriggerIdx:
        case enumTabBarIndex.afterburstIdx:
            recipeTabBarModel.setProperty(0, "Title", qmltextPretrigger)
            recipeTabBarModel.setProperty(1, "Title", qmltextAfterburst)
            break
        case enumTabBarIndex.limitIdx:
        case enumTabBarIndex.setupIdx:
        case enumTabBarIndex.controlIdx:
        case enumTabBarIndex.suspectRejectIdx:
            recipeTabBarModel.setProperty(0, "Title", qmltextSetup)
            recipeTabBarModel.setProperty(1, "Title", qmltextControl)
            recipeTabBarModel.setProperty(2, "Title", qmltextSuspectReject)
            break;
        }
        var strWeldModeTitle = qmltextTime
        switch(currentWeldMode)
        {
        case RecipeEnum.TIME_IDX:
            strWeldModeTitle    = qmltextTime
            break;
        case RecipeEnum.GROUND_IDX:
            strWeldModeTitle    = qmltextScrubTime
            break;
        case RecipeEnum.ENERGY_IDX:
            strWeldModeTitle    = qmltextEnergy
            break;
        case RecipeEnum.PEAKPOWER_IDX:
            strWeldModeTitle    = qmltextPeakPower
            break;
        default:
            strWeldModeTitle    = qmltextTime
            break;
        }
        recipeParameterModel.setProperty(0, "Title", strWeldModeTitle)
        recipeParameterModel.setProperty(1, "Title", qmltextWeldAmplitude)
        recipeParameterModel.setProperty(2, "Title", qmltextHoldTime)
    }

    function updateWeldModeTabBar()
    {
        recipeTabBarModel.clear()
        recipeTabBarModel.append({"Title":      qmltextWeldMode,
                                  "Width":      Math.round(90 * Style.scaleHint),
                                  "Index":      enumTabBarIndex.weldModeIdx})
        recipeTabBarModel.append({"Title":      qmltextWeldProcess,
                                  "Width":      Math.round(105 * Style.scaleHint),
                                  "Index":      enumTabBarIndex.weldProcessIdx})
        recipeTabBarModel.append({"Title":      qmltextParametersA2Z,
                                  "Width":      Math.round(120 * Style.scaleHint),
                                  "Index":      enumTabBarIndex.parametersA2ZIdx})
        recipeTabBarModel.append({"Title":      qmltextLimit,
                                  "Width":      Math.round(60 * Style.scaleHint),
                                  "Index":      enumTabBarIndex.limitIdx})
        recipeTabBarModel.append({"Title":      qmltextStackRecipe,
                                  "Width":      Math.round(100 * Style.scaleHint),
                                  "Index":      enumTabBarIndex.stackRecipeIdx})

    }

    function updateWeldProcessTabBar()
    {
        recipeTabBarModel.clear()
        recipeTabBarModel.append({"Title":      qmltextPretrigger,
                                     "Width":      Math.round(100 * Style.scaleHint),
                                     "Index":      enumTabBarIndex.pretriggerIdx})
        recipeTabBarModel.append({"Title":      qmltextAfterburst,
                                     "Width":      Math.round(100 * Style.scaleHint),
                                     "Index":      enumTabBarIndex.afterburstIdx})
    }

    function updateLimitsTabBar()
    {
        recipeTabBarModel.clear()
        recipeTabBarModel.append({"Title":      qmltextSetup,
                                     "Width":      Math.round(60 * Style.scaleHint),
                                     "Index":      enumTabBarIndex.setupIdx})
        recipeTabBarModel.append({"Title":      qmltextControl,
                                     "Width":      Math.round(70 * Style.scaleHint),
                                     "Index":      enumTabBarIndex.controlIdx})
        recipeTabBarModel.append({"Title":      qmltextSuspectReject,
                                     "Width":      Math.round(125 * Style.scaleHint),
                                     "Index":      enumTabBarIndex.suspectRejectIdx})

    }

    function updateTabBar(index)
    {
        subRecipeDetails.source = ""
        currentTabBarIndex = index
        switch(index)
        {
        case enumTabBarIndex.weldModeIdx:
            updateWeldModeTabBar()
            subRecipeDetails.source = "qrc:/qmlSource/recipeModeSetting.qml"
            break;
        case enumTabBarIndex.weldProcessIdx:
            mainWindow.setHeaderTitle(qmltextWeldProcess, UIScreenEnum.RECIPES_LAB_WELDPROCESS)
            updateWeldProcessTabBar()
            subRecipeDetails.source = "qrc:/qmlSource/recipePretriggerSetting.qml"
            break;
        case enumTabBarIndex.parametersA2ZIdx:
            subRecipeDetails.source = "qrc:/qmlSource/recipeParametersAZSetting.qml"
            break;
        case enumTabBarIndex.limitIdx:
            mainWindow.setHeaderTitle(qmltextLimit, UIScreenEnum.RECIPES_LAB_LIMITS)
            updateLimitsTabBar()
            break;
        case enumTabBarIndex.stackRecipeIdx:
            break;
        case enumTabBarIndex.pretriggerIdx:
            subRecipeDetails.source = "qrc:/qmlSource/recipePretriggerSetting.qml"
            break;
        case enumTabBarIndex.afterburstIdx:
            subRecipeDetails.source = "qrc:/qmlSource/recipeAfterburstSetting.qml"
            break;
        case enumTabBarIndex.setupIdx:
            break;
        case enumTabBarIndex.controlIdx:
            break;
        case enumTabBarIndex.suspectRejectIdx:
            break;
        default:
            break;
        }
    }

    Connections {
        target: mainWindow
        function onSignalCurrentScreenChanged(index)
        {
            if(index === UIScreenEnum.RECIPES_LAB)
            {
                subRecipeDetails.source = ""
                updateWeldModeTabBar()
                subRecipeDetails.source = "qrc:/qmlSource/recipeModeSetting.qml"
            }
        }
    }

    Connections {
        target: subRecipeDetails.item
        ignoreUnknownSignals: true
        function onSignalCurrentWeldModeIdxChanged(index)
        {
            var strTitle, strValue, strUnit, iDecimals, realMinimum, realMaximum
            currentWeldMode = index
            switch(index)
            {
                case RecipeEnum.TIME_IDX:
                    strTitle    = qmltextTime
                    strValue    = "0.500"
                    strUnit     = "S"
                    iDecimals   = 3
                    realMinimum = 0.00004
                    realMaximum = 5.0006
                    break;
                case RecipeEnum.GROUND_IDX:
                    strTitle    = qmltextScrubTime
                    strValue    = "0.300"
                    strUnit     = "S"
                    iDecimals   = 3
                    realMinimum = 0.00005
                    realMaximum = 5.00006
                    break;
                case RecipeEnum.ENERGY_IDX:
                    strTitle    = qmltextEnergy
                    strValue    = "500"
                    strUnit     = "J"
                    iDecimals   = 0
                    realMinimum = 0
                    realMaximum = 10000
                    break;
                case RecipeEnum.PEAKPOWER_IDX:
                    strTitle    = qmltextPeakPower
                    strValue    = "1000"
                    strUnit     = "W"
                    iDecimals   = 0
                    realMinimum = 0
                    realMaximum = 4000
                    break;
                default:
                    strTitle    = qmltextTime
                    strValue    = "0.500"
                    strUnit     = "S"
                    iDecimals   = 3
                    realMinimum = 0.00004
                    realMaximum = 5.0006
                    break;
            }
            recipeParameterModel.setProperty(0, "Title",    strTitle)
            recipeParameterModel.setProperty(0, "Value",    strValue)
            recipeParameterModel.setProperty(0, "Unit",     strUnit)
            recipeParameterModel.setProperty(0, "Decimals", iDecimals)
            recipeParameterModel.setProperty(0, "Minimum",  realMinimum)
            recipeParameterModel.setProperty(0, "Maximum",  realMaximum)
        }
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted: {
        recipeParameterModel.resetModel()
        updateWeldModeTabBar()
        updateLanguage()
        mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.RECIPES_LAB)
    }

    Rectangle {
        id: recipeNameBackground
        width: parent.width
        anchors.top: parent.top
        height: Math.round(50 * Style.scaleHint)
        color: Style.backgroundColor
        Text {
            id: recipeNum
            anchors.left: parent.left
            anchors.leftMargin: 21
            anchors.verticalCenter: parent.verticalCenter
            color: Style.blackFontColor
            font.family: Style.regular.name
            font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
            text: strRecipeNumber + ":"

        }

        BransonLineEdit {
            id: recipeName
            anchors.left: recipeNum.right
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            text: strRecipeName

        }

        Image {
            id: imageEditIcon
            anchors.left: recipeName.right
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/images/edit.svg"
            height: imageSize
            width: imageSize
            fillMode: Image.PreserveAspectFit
            sourceSize.width: imageEditIcon.width
            sourceSize.height: imageEditIcon.height
            smooth: true
        }

        BransonComboBox {
            id: recipeActions
            anchors.right: parent.right
            anchors.rightMargin: 21
            anchors.verticalCenter: parent.verticalCenter
            model: recipeActionsModel
            isNormal: false
            comboBoxText: qmltextRecipeActions
            onActivated:
            {
                console.debug("index:", index)
            }
            z: 1
        }
    }
    ListModel {
        id: recipeTabBarModel

    }

    Rectangle {
        id: tabBarBackground
        anchors.left: parent.left
        anchors.top: recipeNameBackground.bottom
        width: parent.width
        height: Math.round(47 * Style.scaleHint)
        color: Style.backgroundColor
        TabBar {
            id: recipeTabBar
            anchors.left: parent.left
            anchors.leftMargin: 14
            anchors.verticalCenter: parent.verticalCenter
            width: Math.round(600 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            spacing: 20
            background: Rectangle{
                color: Style.backgroundColor
            }

            Repeater {
                id: tabbtn
                model: recipeTabBarModel
                delegate: BransonTabButton {
                    width: model.Width
                    height: parent.height
                    tabbtnText: model.Title
                    onClicked: {
                        updateTabBar(model.Index)
                    }
                }
            }
        }

        Rectangle {
            id: btnResultView
            anchors.top: parent.top
            height: imageBigSize
            anchors.right: parent.right
            anchors.rightMargin: 10
            width: Math.round(126 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            color: Style.backgroundColor
            Row {
                anchors.right: parent.right
                height: parent.height
                Text {
                    anchors.verticalCenter: imageResultView.verticalCenter
                    color: Style.blueFontColor
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                    text: qmltextResultView
                    font.bold: true
                }
                Image {
                    id: imageResultView
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/images/ViewIcon.svg"
                    height: imageBigSize
                    width: imageBigSize
                    fillMode: Image.PreserveAspectFit
                    sourceSize.width: imageResultView.width
                    sourceSize.height: imageResultView.height
                    smooth: true
                }
            }
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                }
            }
        }
    }

    ListModel {
        id: recipeParameterModel
        function resetModel()
        {
            recipeParameterModel.clear()
            recipeParameterModel.append({"Title":       qmltextTime,
                                         "Value":       "0.500",
                                         "Unit":        "S",
                                         "Minimum":     0.000,
                                         "Maximum":     5.000,
                                         "Decimals":    3,
                                         "Index":       0})
            recipeParameterModel.append({"Title":       qmltextWeldAmplitude,
                                         "Value":       "60",
                                         "Unit":        "%",
                                         "Minimum":     0,
                                         "Maximum":     100,
                                         "Decimals":    0,
                                         "Index":       1})
            recipeParameterModel.append({"Title":       qmltextHoldTime,
                                         "Value":       "0.500",
                                         "Unit":        "S",
                                         "Minimum":     0.000,
                                         "Maximum":     5.000,
                                         "Decimals":    3,
                                         "Index":       2})
        }
    }

    Rectangle {
        id: rectQuickEdit
        anchors.right: parent.right
        anchors.rightMargin: 19
        anchors.top: tabBarBackground.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 11
        width: Math.round(292 * Style.scaleHint)
        border.width: Style.scaleHint === 1.0 ? 1 : 3
        border.color: Style.frameBorderColor
        color: Style.backgroundColor
        Rectangle {
            id: rectQuickEditTitle
            anchors.left: parent.left
            anchors.top: parent.top
            width: parent.width
            height: Math.round(28 * Style.scaleHint)
            color: Style.titleBackgroundColor
            Text {
                anchors.left: parent.left
                anchors.leftMargin: 15
                anchors.verticalCenter: parent.verticalCenter
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                font.bold: true
                color: Style.whiteFontColor
                text: qmltextQuickEdit
            }
        }

        Column {
            anchors.top: rectQuickEditTitle.bottom
            anchors.topMargin: 11
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.leftMargin: 11
            anchors.right: parent.right
            anchors.rightMargin: 11
            spacing: Math.round(10 * Style.scaleHint)
            Repeater {
                id: cardDetailsInfo
                height: parent.height
                anchors.horizontalCenter: parent.horizontalCenter
                model: recipeParameterModel
                delegate: Item {
                    width: Math.round(270 * Style.scaleHint)
                    height: Math.round(83 * Style.scaleHint)
                    DropShadow {
                        source: btnRecipeSetting
                        anchors.fill: btnRecipeSetting
                        horizontalOffset: btnRecipeSettingMouseArea.pressed ? 0 : 1
                        verticalOffset: btnRecipeSettingMouseArea.pressed ? 0 : 1
                        color: shadowColor
                        opacity: 0.2
                        radius: 3
                    }
                    Rectangle {
                        id: btnRecipeSetting
                        anchors.fill: parent
                        border.width: Style.scaleHint === 1.0 ? 1 : 3
                        border.color: Style.activeFrameBorderColor//Style.frameBorderColor
                        color: Style.frameButtonBackgroundColor
                        Column {
                            anchors.left: parent.left
                            anchors.leftMargin: 17
                            anchors.verticalCenter: parent.verticalCenter
                            Text {
                                wrapMode: Text.NoWrap
                                elide: Text.ElideRight
                                text: model.Title
                                font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                                font.bold: true
                                color: Style.blackFontColor
                            }
                            Text {
                                wrapMode: Text.NoWrap
                                elide: Text.ElideRight
                                text: model.Value + " " + model.Unit
                                font.pixelSize: Math.round(Style.style7 * Style.scaleHint)
                                color: Style.blueFontColor
                            }
                        }
                    }
                    MouseArea {
                        id: btnRecipeSettingMouseArea
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            if(model.Index === 1)
                                mainWindow.showSteppingNumpad(model.Title, model.Unit, model.Decimals, model.Minimum, model.Maximum, model.Value)
                            else
                                mainWindow.showPrimaryNumpad(model.Title, model.Unit, model.Decimals, model.Minimum, model.Maximum, model.Value)
                        }
                    }

                }
            }
        }
    }

    Loader {
        id: subRecipeDetails
        anchors.top: tabBarBackground.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 17
        anchors.bottom: parent.bottom
        anchors.right: rectQuickEdit.left
        source: "qrc:/qmlSource/recipeModeSetting.qml"
    }
}
