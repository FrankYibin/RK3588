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
    id:systemInformation

    property string qmltextMenuName:  qsTr("Information")
    property string qmlTextMachineDetails: qsTr("Machine Details")
    property string qmlTextModel: qsTr("Model")
    property string qmlTextModelValue: qsTr("GSX-P1 Base")
    property string qmlTextGeneralAlarm: qsTr("General Alarm")


    property string qmlTextSotwareVersion: qsTr("Software Versions")
    property string qmlTextUIController: qsTr("UI Controller")
    property string qmlTextSupervisory: qsTr("Supervisory")
    property string qmlTextActuatorController: qsTr("Actuator Controller")
    property string qmlTextPowerController: qsTr("Power Controller")

    property string qmlTextSoftwareUpgrade: qsTr("SOFTWARE UPGRADE")

    property string qmlTextPowerSupply: qsTr("Power Supply")
    property string qmlTextLifeTimeWelds: qsTr("Life Time Welds")
    property string qmlTextOverloads: qsTr("Overloads")
    property string qmlTextPsType: qsTr("Type")
    property string qmlTextPSFrequency: qsTr("Frequency")
    property string qmlTextPsWatt: qsTr("Wattage")


    property string qmlTextActuator: qsTr("Actuator")
    property string qmlTextLifeTimeCycle: qsTr("Life Time Cycle")
    property string qmlTextType: qsTr("Type")
    property string qmlTextCalibrationDate: qsTr("Calibration Date")
    property string qmlTextActuatorOverloads: qsTr("Overloads")
    property string qmlTextStrokeLength: qsTr("Stroke Length")

    property string qmlTextConnectivity: qsTr("Connectivity")
    property string qmlTextMacID: qsTr("MAC Address")

    property string qmlTextThirdPart: qsTr("Third Party Software Information")
    property string qmlTextDetailsThirdPart: qsTr("Please refer to the following URL for information about third party software(e.g., open source software) used in this product: ")
    property string qmlTextThirdPartURL: ""

    property string qmlTextNISTcalibration: qsTr("NIST Calibration")
    property string qmlTextNISTcalibrationDate: qsTr("NIST Calibration Date")

    property int actuatorRowNumber: 1


    property var qmlTextArray: [qmlTextMachineDetails, qmlTextModel, qmlTextGeneralAlarm,
        qmlTextSotwareVersion, qmlTextUIController, qmlTextSupervisory, qmlTextActuatorController, qmlTextPowerController,
        qmlTextSoftwareUpgrade,
        qmlTextPowerSupply, qmlTextLifeTimeWelds, qmlTextOverloads, qmlTextPsType, qmlTextPSFrequency, qmlTextPsWatt,
        qmlTextActuator, qmlTextLifeTimeCycle, qmlTextType, qmlTextCalibrationDate, qmlTextStrokeLength,
        qmlTextConnectivity, qmlTextMacID, qmlTextThirdPart, qmlTextDetailsThirdPart, qmlTextNISTcalibration, qmlTextNISTcalibrationDate, qmlTextActuatorOverloads]

    QtObject {
        id: textEnum
        readonly property int machineDetailsIdx: 0
        readonly property int modelIdx: 1
        readonly property int generalAlarmIdx: 2
        readonly property int softwareVersionIdx: 3
        readonly property int uIControllerIdx: 4
        readonly property int supervisoryIdx: 5
        readonly property int actuatorControllerIdx: 6
        readonly property int powerControllerIdx: 7
        readonly property int softwareUpgradeIdx: 8
        readonly property int powerSupplyIdx: 9
        readonly property int lifeTimeWeldIdx: 10
        readonly property int overloadsIdx: 11
        readonly property int psTypeIdx: 12
        readonly property int pSFrequencyIdx: 13
        readonly property int psWattIdx: 14
        readonly property int actuatorIdx: 15
        readonly property int lifeTimeCycleIdx: 16
        readonly property int typeIdx: 17
        readonly property int calibrationDateIdx: 18
        readonly property int strokeLengthIdx: 19
        readonly property int connectivityIdx: 20
        readonly property int macIDIdx: 21
        readonly property int thirdPartIdx: 22
        readonly property int detailsThirdPartIdx: 23
        readonly property int nistCalibrationIdx: 24
        readonly property int nistCalibrationDateIdx: 25
        readonly property int actuatorOverloadsIdx: 26
    }

    function updateLanguage()
    {
        qmlTextArray = languageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_INFO, qmlTextArray)
        qmlTextMachineDetails = qmlTextArray[textEnum.machineDetailsIdx]
        qmlTextModel = qmlTextArray[textEnum.modelIdx]
        qmlTextGeneralAlarm = qmlTextArray[textEnum.generalAlarmIdx]
        qmlTextSotwareVersion = qmlTextArray[textEnum.softwareVersionIdx]
        qmlTextUIController = qmlTextArray[textEnum.uIControllerIdx]
        qmlTextSupervisory = qmlTextArray[textEnum.supervisoryIdx]
        qmlTextActuatorController = qmlTextArray[textEnum.actuatorControllerIdx]
        qmlTextPowerController = qmlTextArray[textEnum.powerControllerIdx]
        qmlTextSoftwareUpgrade = qmlTextArray[textEnum.softwareUpgradeIdx]
        qmlTextPowerSupply = qmlTextArray[textEnum.powerSupplyIdx]
        qmlTextLifeTimeWelds = qmlTextArray[textEnum.lifeTimeWeldIdx]
        qmlTextOverloads = qmlTextArray[textEnum.overloadsIdx]
        qmlTextPsType = qmlTextArray[textEnum.psTypeIdx]
        qmlTextPSFrequency = qmlTextArray[textEnum.pSFrequencyIdx]
        qmlTextPsWatt = qmlTextArray[textEnum.psWattIdx]
        qmlTextActuator = qmlTextArray[textEnum.actuatorIdx]
        qmlTextLifeTimeCycle = qmlTextArray[textEnum.lifeTimeCycleIdx]
        qmlTextType = qmlTextArray[textEnum.typeIdx]
        qmlTextCalibrationDate = qmlTextArray[textEnum.calibrationDateIdx]
        qmlTextActuatorOverloads = qmlTextArray[textEnum.actuatorOverloadsIdx]
        qmlTextStrokeLength = qmlTextArray[textEnum.strokeLengthIdx]
        qmlTextConnectivity = qmlTextArray[textEnum.connectivityIdx]
        qmlTextMacID = qmlTextArray[textEnum.macIDIdx]
        qmlTextThirdPart = qmlTextArray[textEnum.thirdPartIdx]
        qmlTextDetailsThirdPart = qmlTextArray[textEnum.detailsThirdPartIdx]
        qmlTextNISTcalibration = qmlTextArray[textEnum.nistCalibrationIdx]
        qmlTextNISTcalibrationDate = qmlTextArray[textEnum.nistCalibrationDateIdx]
        qmltextMenuName = languageConfig.getLanguageMenuName(UIScreenEnum.SYSTEM_INFO, qmltextMenuName)
        softwareVersionModel.resetSoftwareVersionModel()
        actuatorModel.resetActuatorModel()
        powerSupplyModel.resetPowerSupplyModel()
    }

    function zoomingSize(inSize)
    {
        return Math.round(inSize * Style.scaleHint)
    }


    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted: {
        systemInformationModel.loadSystemInformation()
        softwareVersionModel.resetSoftwareVersionModel()
        actuatorModel.resetActuatorModel()
        reCaculateActuatorModel()
        powerSupplyModel.resetPowerSupplyModel()
        updateLanguage()
        mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.SYSTEM_INFO)
    }



    //software version content model
    ListModel{
        id:softwareVersionModel
        function resetSoftwareVersionModel(){
            softwareVersionModel.clear()
            softwareVersionModel.append({
                                            "protyName": qmlTextUIController,
                                            "protyValue": systemInformationModel.strUIController
                                        })
            softwareVersionModel.append({
                                            "protyName": qmlTextSupervisory,
                                            "protyValue": systemInformationModel.strSupervisoryController
                                        })
            softwareVersionModel.append({
                                            "protyName": qmlTextActuatorController,
                                            "protyValue": systemInformationModel.strActuatorController
                                        })
            softwareVersionModel.append({
                                            "protyName": qmlTextPowerController,
                                            "protyValue": systemInformationModel.strPowerController
                                        })
        }
    }
    //Power supply model
    ListModel{
        id: powerSupplyModel
        function resetPowerSupplyModel()
        {
            powerSupplyModel.clear()
            powerSupplyModel.append({
                                        "protyName": qmlTextLifeTimeWelds,
                                        "protyValue": "" + systemInformationModel.iPSLifeWelds
                                    })
            powerSupplyModel.append({
                                        "protyName": qmlTextOverloads,
                                        "protyValue": "" + systemInformationModel.iPSOverloads
                                    })
            powerSupplyModel.append({
                                        "protyName": qmlTextPsType,
                                        "protyValue": "" + systemInformationModel.iPSType
                                    })
            powerSupplyModel.append({
                                        "protyName": qmlTextPSFrequency,
                                        "protyValue": "" + systemInformationModel.iPSFrequency
                                    })
            powerSupplyModel.append({
                                        "protyName": qmlTextPsWatt,
                                        "protyValue": "" + systemInformationModel.iPSWattage
                                    })

        }
    }
    //actuator model
    ListModel{
        id: actuatorModel
        function resetActuatorModel()
        {
            actuatorModel.clear()
            actuatorModel.append({
                                        "protyName": qmlTextLifeTimeCycle,
                                        "protyValue": "" + systemInformationModel.iActuatorLifeCycle,
                                        "propertyVisible": SystemTypeEnum.ALLTYPE
                                    })
            actuatorModel.append({
                                        "protyName": qmlTextType,
                                        "protyValue": "" + systemInformationModel.iActuatorType,
                                        "propertyVisible":  SystemTypeEnum.ALLTYPE
                                    })
            actuatorModel.append({
                                        "protyName": qmlTextCalibrationDate,
                                        "protyValue": "" + systemInformationModel.strActuatorCalibrationDate,
                                        "propertyVisible": SystemTypeEnum.GSX_E1
                                    })
            actuatorModel.append({
                                        "protyName": qmlTextActuatorOverloads,
                                        "protyValue": "" + systemInformationModel.iActuatorOverloads,
                                        "propertyVisible": SystemTypeEnum.GSX_E1
                                    })
            actuatorModel.append({
                                        "protyName": qmlTextStrokeLength,
                                        "protyValue": "" + systemInformationModel.iStrokeLength,
                                        "propertyVisible":  SystemTypeEnum.GSX_E1 | SystemTypeEnum.GSX_P1_BASE
                                    })
        }

    }

    ListModel{
        id: actuatorShowModel
    }

    function reCaculateActuatorModel()
    {
        actuatorShowModel.clear()
        for(var index = 0; index < actuatorModel.count; index++)
        {
            var isVisible = systemInformationModel.isShownTheItem(actuatorModel.get(index).propertyVisible)
            if(isVisible === true)
            {
                actuatorShowModel.append(actuatorModel.get(index))
            }
        }
        actuatorRowNumber = actuatorShowModel.count / 2;
        if(actuatorShowModel.count % 2 !== 0)
            actuatorRowNumber++
    }





    //Machine Details
    Image{
        id: machineDetailsImg
        width: zoomingSize(800)
        height: zoomingSize(40)
        source: "qrc:/images/informationSecondNav.svg"
        anchors.top: parent.top
        anchors.left: parent.left
        //Machine Details text
        Text{
            id: machineDetails
            anchors.top: parent.top
            anchors.topMargin: zoomingSize(5)
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(23)
            width: zoomingSize(129)
            height: zoomingSize(22)
            font.pixelSize: zoomingSize(Style.style4)
            font.family: Style.semibold.name
            text: qmlTextMachineDetails
            color: Style.blueMachineDetails
        }
        //Machine Details baseline:
        Image{
            id: machineDetailsLine
            fillMode: Image.PreserveAspectFit
            width: zoomingSize(133)
            sourceSize.width: machineDetailsLine.width
            anchors.top: machineDetails.bottom
            anchors.topMargin: zoomingSize(2)
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(21)
            source: "qrc:/images/InformationSelectedTab.svg"
        }
    }

    Flickable{
        id: infoScrollRec
        width: zoomingSize(800)
        height: zoomingSize(373)
        anchors.top: machineDetailsImg.bottom
        anchors.topMargin: zoomingSize(17)
        anchors.left: parent.left
        contentHeight: zoomingSize(840)
        clip: true


        //model item and Gerneral Alarm
        Row{
            id: deviceInfoRow
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(18)
            anchors.right: parent.right
            anchors.rightMargin: zoomingSize(10)
            spacing: zoomingSize(16)
            BransonInfoElement{
                id: device
                protyName: qmlTextModel
                protyValue: systemInformationModel.strModelName
            }
            BransonInfoElement{
                id: generalAlarm
                protyName: qmlTextGeneralAlarm
                protyValue: systemInformationModel.iGerneralAlarm
            }
        }


        //software version text
        Text{
            id: softwareVersionText
            anchors.top: deviceInfoRow.bottom
            anchors.topMargin: zoomingSize(16)
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(29)
            font.pixelSize: zoomingSize(Style.style4)
            font.family: Style.semibold.name
            text: qmlTextSotwareVersion
            color: Style.blackFontColor
        }

       //software line
        Rectangle{
            id: softwareVersionLine
            anchors.top: softwareVersionText.bottom
            anchors.topMargin: zoomingSize(5)
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(18)
            width: zoomingSize(770)
            height: zoomingSize(1)
            color: Style.blackFontColor
        }

        //software version content screen
        Rectangle{
            id: softwareVersionRec
            color: Style.backgroundColor
            anchors.top: softwareVersionText.bottom
            anchors.topMargin: zoomingSize(17)
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(18)
            width: zoomingSize(374 * 2 + 32)
            height: zoomingSize(35 * 2 + 20)
            GridView{
                id: gridViewSoftwareVersion
                interactive: false
                anchors.fill: parent
                cellHeight: parent.height / 2
                cellWidth: parent.width / 2
                model: softwareVersionModel
                delegate: BransonInfoElement{
                    protyName: model.protyName
                    protyValue: model.protyValue
                }
            }
        }


        //software upgrade Button
        BransonPrimaryButton{
            id: softwareUpgrade
            anchors.top: softwareVersionRec.bottom
            anchors.topMargin: zoomingSize(9)
            anchors.left: softwareVersionRec.left
            width: zoomingSize(181)
            height: zoomingSize(30)
            fontSize: zoomingSize(Style.style4)
            text: qmlTextSoftwareUpgrade
            font.family: Style.regular.name
        }

        //Power Supply
        Text{
            id: powerSupplyText
            anchors.top: softwareUpgrade.bottom
            anchors.topMargin: zoomingSize(20)
            anchors.left: softwareVersionText.left
            text: qmlTextPowerSupply
            font.pixelSize: zoomingSize(Style.style4)
            color: Style.blackFontColor
            font.family: Style.semibold.name
        }

        //Power Supply line
        Rectangle{
            id: powerSupplyLine
            anchors.top: powerSupplyText.bottom
            anchors.topMargin: zoomingSize(5)
            anchors.left: softwareVersionLine.left
            width: zoomingSize(770)
            height: zoomingSize(1)
            color: Style.blackFontColor
        }


        //Power supply content screen
        Rectangle{
            id: powerSupplyContent
            color: Style.backgroundColor
            anchors.top: powerSupplyText.bottom
            anchors.topMargin: zoomingSize(17)
            anchors.left: softwareVersionRec.left
            width: zoomingSize(374 * 2 + 32)
            height: zoomingSize(35 * 3 + 30)
            GridView{
                id: powerSupplyGridView
                interactive: false
                anchors.fill: parent
                cellHeight: parent.height / 3
                cellWidth: parent.width / 2
                model: powerSupplyModel
                delegate: BransonInfoElement{
                    protyName: model.protyName
                    protyValue: model.protyValue
                }
            }
        }


        //actuator text
        Text{
            id: actuatorText
            anchors.top: powerSupplyContent.bottom
            anchors.topMargin: zoomingSize(7)
            anchors.left: powerSupplyText.left
            text: qmlTextActuator
            font.pixelSize: zoomingSize(Style.style4)
            color: Style.blackFontColor
            font.family: Style.semibold.name
        }
        //actuator line
        Rectangle{
            id: actuatorLine
            anchors.top: actuatorText.bottom
            anchors.topMargin: zoomingSize(5)
            anchors.left: softwareVersionLine.left
            width: zoomingSize(770)
            height: zoomingSize(1)
            color: Style.blackFontColor
        }

        //actuator content screen
        Rectangle{
            id: actuatorContent
            color: Style.backgroundColor
            anchors.top: actuatorText.bottom
            anchors.topMargin: zoomingSize(17)
            anchors.left: softwareVersionRec.left
            width: zoomingSize(374 * 2 + 32)
            height: zoomingSize(35 * actuatorRowNumber + 10 * actuatorRowNumber)
            GridView{
                id: acturtorGridView
                interactive: false
                anchors.fill: parent
                cellHeight: parent.height / actuatorRowNumber
                cellWidth: parent.width / 2
                model: actuatorShowModel
                delegate: BransonInfoElement{
                    protyName: model.protyName
                    protyValue: model.protyValue
                }
            }
        }


        //NIST Calibration
        Text{
            id: nistCalibration
            anchors.top: actuatorContent.bottom
            anchors.topMargin: zoomingSize(7)
            anchors.left: powerSupplyText.left
            text: qmlTextNISTcalibration
            font.pixelSize: zoomingSize(Style.style4)
            color: Style.blackFontColor
            font.family: Style.semibold.name
            visible: {
                if((systemInformationModel.getSystemType() & SystemTypeEnum.GSX_P1_BASE) > 0)
                    return true
                else
                    return false
            }
        }
        //NIST line
        Rectangle{
            id: nistLine
            anchors.top: nistCalibration.bottom
            anchors.topMargin: zoomingSize(5)
            anchors.left: softwareVersionLine.left
            width: zoomingSize(770)
            height: zoomingSize(1)
            color: Style.blackFontColor
            visible: nistCalibration.visible
        }

        //NIST Calibration Date
        BransonInfoElement{
            id: nistCalibrationDate
            anchors.top: nistLine.bottom
            anchors.topMargin: zoomingSize(17)
            anchors.left: actuatorContent.left
            visible: nistCalibration.visible
            protyName: qmlTextNISTcalibrationDate
            protyValue: systemInformationModel.strNISTCalibrationDate
        }

        //connectivity text
        Text{
            id: connectivityText
            anchors.top: (nistCalibration.visible === true? nistCalibrationDate.bottom : actuatorContent.bottom)
            anchors.topMargin: zoomingSize(7)
            anchors.left: powerSupplyText.left
            text: qmlTextConnectivity
            font.pixelSize: zoomingSize(Style.style4)
            color: Style.blackFontColor
            font.family: Style.semibold.name
        }
        //connectivity line
        Rectangle{
            id: connectivityLine
            anchors.top: connectivityText.bottom
            anchors.topMargin: zoomingSize(5)
            anchors.left: softwareVersionLine.left
            width: zoomingSize(770)
            height: zoomingSize(1)
            color: Style.blackFontColor
        }

        //MAC ID
        BransonInfoElement{
            id: macID
            anchors.top: connectivityText.bottom
            anchors.topMargin: zoomingSize(17)
            anchors.left: actuatorContent.left
            protyName: qmlTextMacID
            protyValue: systemInformationModel.strMACAddress
        }


        //third party
        Text{
            id: thirdPartText
            anchors.top: macID.bottom
            anchors.topMargin: zoomingSize(40)
            anchors.left: connectivityText.left
            text: qmlTextThirdPart
            font.pixelSize: zoomingSize(Style.style4)
            color: Style.blackFontColor
            font.family: Style.semibold.name
        }

        //third party line
        Rectangle{
            id: thirdPartLine
            anchors.top: thirdPartText.bottom
            anchors.topMargin: zoomingSize(5)
            anchors.left: softwareVersionLine.left
            width: zoomingSize(770)
            height: zoomingSize(1)
            color: Style.blackFontColor
        }
         //Third party details
         Text{
             id: thirdPartDetailsText
             anchors.top: thirdPartText.bottom
             anchors.topMargin: zoomingSize(17)
             anchors.left: thirdPartText.left
             wrapMode: Text.WordWrap
             width: zoomingSize(772)
             text: qmlTextDetailsThirdPart + qmlTextThirdPartURL
             font.pixelSize: zoomingSize(Style.style4)
             color: Style.blackFontColor
             font.family: Style.regular.name
         }

    }
}
