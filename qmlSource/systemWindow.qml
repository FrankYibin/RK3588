/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 xxxxx

 **********************************************************************************************************/


import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.SystemTypeEnum 1.0

Item {

    id: systemWindow

    readonly property int qmlscreenIndicator:  UIScreenEnum.SYSTEM

    property string qmltextMenuName:               qsTr("System")
    property string qmlTextConfiguration:          qsTr("Configuration")
    property string qmlTextData:                   qsTr("Data")
    property string qmlTextInformation:            qsTr("Information")
    property string qmlTextCalibration:            qsTr("Calibration")

    //layout size
    readonly property int elementWidth:            190
    readonly property int elementHeight:           203
    readonly property int elementWidthMargin:      9
    readonly property int elementHeightMargin:     10
    property int rowNumber: 1
    property int columnNumber: 1

    //const
    readonly property int calibrationIndex: 1
    property var qmlTextArray:[qmlTextConfiguration, qmlTextData, qmlTextInformation, qmlTextCalibration]

    QtObject {
        id: textEnum
        readonly property int sysConfigurationIdx: 0
        readonly property int sysDataIdx: 1
        readonly property int sysInformationIdx: 2
        readonly property int sysCalibrationIdx: 3
    }


    function updateLanguage()
    {
        qmlTextArray = languageConfig.getLanguageStringList(UIScreenEnum.SYSTEM, qmlTextArray)
        qmlTextConfiguration = qmlTextArray[textEnum.sysConfigurationIdx]
        qmlTextData = qmlTextArray[textEnum.sysDataIdx]
        qmlTextInformation = qmlTextArray[textEnum.sysInformationIdx]
        qmlTextCalibration = qmlTextArray[textEnum.sysCalibrationIdx]
        qmltextMenuName = languageConfig.getLanguageMenuName(UIScreenEnum.SYSTEM, qmltextMenuName)
        systemViewModel.resetModel()
    }

    function updateItemScreen(itemIndex)
    {
        switch(itemIndex)
        {
        case textEnum.sysConfigurationIdx:
            break
        case textEnum.sysDataIdx:
            break
        case textEnum.sysInformationIdx:
            mainWindow.menuChildOptionSelect(UIScreenEnum.SYSTEM, UIScreenEnum.SYSTEM_INFO)
            break
        default:
            break
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
        systemViewModel.resetModel()
        caculateListModel()
        recalculateRowColumn()
        updateLanguage()
        mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.SYSTEM)
    }

    ListModel{
        id: systemViewModel
        function resetModel()
        {
            systemViewModel.clear()
            systemViewModel.append({ "imageURL":  "qrc:/images/systemConfiguration.svg",
                                     "textName":  qmlTextConfiguration,
                                     "visibleValue": SystemTypeEnum.ALLTYPE
                                   })

            systemViewModel.append({ "imageURL":  "qrc:/images/systemData.svg",
                                     "textName":  qmlTextData,
                                     "visibleValue": SystemTypeEnum.ALLTYPE
                                   })

            systemViewModel.append({ "imageURL":  "qrc:/images/systemInformation.svg",
                                     "textName":  qmlTextInformation,
                                     "visibleValue": SystemTypeEnum.ALLTYPE
                                   })
            systemViewModel.append({ "imageURL":  "qrc:/images/systemCalibration.png",
                                     "textName":  qmlTextCalibration,
                                     "visibleValue": SystemTypeEnum.GSX_E1
                                   })
        }
    }

    ListModel
    {
        id: systemActualModel
    }

    function caculateListModel()
    {
        systemActualModel.clear()
        for(var index = 0; index < systemViewModel.count; index++)
        {
            var isAdd = systemInformationModel.isShownTheItem(systemViewModel.get(index).visibleValue)
            if(isAdd === true)
            {
                systemActualModel.append(systemViewModel.get(index))
            }
        }
    }

    function recalculateRowColumn()
    {
        if(systemActualModel.count > 4)
        {
            columnNumber = 3
            var actualModelCnt = systemActualModel.count
            if(actualModelCnt % 3 ===0)
            {
                rowNumber = actualModelCnt / 3
            }
            else
            {
                rowNumber = actualModelCnt / 3 + 1
            }
        }
        else if(systemActualModel.count === 4)
        {
            columnNumber = 2
            rowNumber = 2
        }
        else
        {
            columnNumber = systemActualModel.count
            rowNumber = 1
        }
    }


    Rectangle{
        id: systemRec
        color: Style.backgroundColor
        anchors.centerIn: parent
        anchors.top: parent.top
        anchors.topMargin: 7
        width: Math.round((elementWidth + elementWidthMargin) * columnNumber * Style.scaleHint)
        height: Math.round((elementHeight + elementHeightMargin) * rowNumber * Style.scaleHint)
        GridView{
            id: gridView
            interactive: false
            anchors.fill: parent
            model: systemActualModel
            cellHeight: parent.height / rowNumber
            cellWidth: parent.width / columnNumber
            delegate: Image{
                width: gridView.cellWidth
                height: gridView.cellHeight
                fillMode: Image.PreserveAspectFit
                source: "qrc:/images/SystemCardBox.svg"
                visible: systemInformationModel.isShownTheItem(model.visibleValue)
                Image {
                    id: cellIcon
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(68 * Style.scaleHint)
                    width: Math.round(40* Style.scaleHint)
                    height: Math.round(40* Style.scaleHint)
                    fillMode: Image.PreserveAspectFit
                    source: model.imageURL
                }
                Text {
                    id: cellText
                    anchors.top: cellIcon.bottom
                    anchors.topMargin: Math.round(12 * Style.scaleHint)
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                    text: model.textName
                    color: Style.blackFontColor
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        updateItemScreen(model.index)
                    }
                }


            }

        }


    }


}
