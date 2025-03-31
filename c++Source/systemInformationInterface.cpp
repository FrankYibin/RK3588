/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 This file is a source file and it is used to implement the business.

 **********************************************************************************************************/

#include "systemInformationInterface.h"
#include "version.h"

SystemInformationInterface* SystemInformationInterface::m_systemInformationInstance = nullptr;

/**************************************************************************//**
*
* \brief This is the constructor.
*
* \param None.
*
* \return None
*
******************************************************************************/
SystemInformationInterface::SystemInformationInterface(QObject *parent)
    : QObject(parent)
    , m_strModelName("")
    , m_iGeneralAlarm(0)
    , m_strSupervisory("A.B.C.D")
    , m_strActuatorController("A.B.C.D")
    , m_strPowerController("A.B.C.D")
    , m_iPSLifeWelds(0)
    , m_iPSOverloads(0)
    , m_iPSType(0)
    , m_iPSFrequency(0)
    , m_iPSWattage(0)
    , m_iActuatorLifeCycle(0)
    , m_iActuatorType(0)
    , m_strCalibrationDate("")
    , m_iActuatorOverloads(0)
    , m_iStrokeLength(0)
    , m_strNISTCalibrationDate("")
    , m_strMacAddress("")

{
    m_iSystemType = SystemTypeDef::GSX_P1_BASE;
    m_strUIController = QString::number(UIC_VERSION_NUM_MAJOR) + "." + QString::number(UIC_VERSION_NUM_MINOR) + "." \
           + QString::number(UIC_VERSION_NUM_BUILD) + "." + QString::number(UIC_VERSION_NUM_AUTOS);
}

/**************************************************************************//**
*
* \brief This is the SystemInformationInterface sigleton function. To return a singleton object pointer.
*
* \param None.
*
* \return the pointer of SystemInformationInterface Object.
*
******************************************************************************/
SystemInformationInterface *SystemInformationInterface::getInstance()
{
    if(m_systemInformationInstance == nullptr)
    {
        m_systemInformationInstance = new SystemInformationInterface();
    }
    return m_systemInformationInstance;
}

/**************************************************************************//**
*
* \brief This is the SystemInformationInterface destructor.
*
* \param None.
*
* \return None.
*
******************************************************************************/
SystemInformationInterface::~SystemInformationInterface()
{

}

/**************************************************************************//**
*
* \brief To get the system information from server.
*
* \param None.
*
* \return None.
*
******************************************************************************/
void SystemInformationInterface::loadSystemInformation()
{
    QByteArray sendMessage, recvMessage;
    sendMessage.clear();
    recvMessage.clear();
    bool resSend = CommunicationInterface::getInstance()->sendMessage(requestIdentities::GET_SYSTEM_INFORMATION, sendMessage);
    if(true == resSend)
    {
        bool resReceive = CommunicationInterface::getInstance()->receivedMessage(requestIdentities::GET_SYSTEM_INFORMATION, recvMessage);
        if(true == resReceive)
        {
            SYSTEMINFO *tempSystemInfo = (SYSTEMINFO*)recvMessage.data();
            QString tempModelName = QString(QLatin1String(tempSystemInfo->modelName));
            updateModelName(tempModelName);
            updateGerneralAlarm(tempSystemInfo->generalAlarmCounter);
            QString tempSC = QString(QLatin1String(tempSystemInfo->version_SC));
            updateSupervisoryController(tempSC);

            QString tempAC = QString(QLatin1String(tempSystemInfo->version_AC));
            updateActuatorController(tempAC);

            // QString tempPC = QString(QLatin1String(tempSystemInfo->version_PC));
            // updatePowerController(tempPC);

            updatePSLifeWelds(tempSystemInfo->psLifeCounter);
            updatePSOverloads(tempSystemInfo->overloadAlarmCounter);
            updatePSType(tempSystemInfo->psType);
            updatePSFrequency(tempSystemInfo->psFrequency);
            updatePSWattage(tempSystemInfo->psWatt);

            updateActuatorLifeCycle(tempSystemInfo->actuatorlifecounter);
            updateActuatorType(tempSystemInfo->actuatorType);
            updateActuatorOverloads(tempSystemInfo->actuatorOverloads);

            QString tempDatetime = QString(QLatin1String(tempSystemInfo->dateTime));
            updateNISTCalibrationDate(tempDatetime);
            updateStrokeLength(tempSystemInfo->actuatorStrokeLength);
            QString tempMacID = QString(QLatin1String(tempSystemInfo->psMacID));
            updateMACAddress(tempMacID);
        }
        else
        {
            //The message is not received successfully.
#ifdef SYSTEMINFODATA
            qDebug()<<"System Information data is not received";
#endif
        }
    }
    else
    {
        //The message is not sent successfully.
#ifdef SYSTEMINFODATA
        qDebug()<<"System Information command is not sent successfully";
#endif
    }

}

/**************************************************************************//**
*
* \brief To judge if the item should be shown.
*
* \param None.
*
* \return the showing result.
*
******************************************************************************/
bool SystemInformationInterface::isShownTheItem(int itemType)
{
    if(SystemTypeDef::ALLTYPE == itemType)
    {
        return true;
    }
    else if((m_iSystemType & itemType) > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**************************************************************************//**
*
* \brief To return the system type.
*
* \param None.
*
* \return the value of system type.
*
******************************************************************************/
int SystemInformationInterface::getSystemType()
{
    return m_iSystemType;
}

/**************************************************************************//**
*
* \brief To return the model name.
*
* \param None.
*
* \return the string of modelName.
*
******************************************************************************/
QString SystemInformationInterface::getModelName() const
{
    return m_strModelName;
}

/**************************************************************************//**
*
* \brief To set the model name.
*
* \param inModelName is used to assign value to model name.
*
* \return None.
*
******************************************************************************/
void SystemInformationInterface::updateModelName(const QString& strModelName)
{
    if(strModelName != m_strModelName)
    {
        m_strModelName = strModelName;
        emit signalModelNameChanged();
    }
}

/**************************************************************************//**
*
* \brief To get the general alarm.
*
* \param None.
*
* \return the generalAlarm value.
*
******************************************************************************/
int SystemInformationInterface::getGeneralAlarm() const
{
    return m_iGeneralAlarm;
}

/**************************************************************************//**
*
* \brief To set the generalAlarm value.
*
* \param inGerneralAlarm is used to assign value to generalAlarm.
*
* \return None.
*
******************************************************************************/
void SystemInformationInterface::updateGerneralAlarm(const int& iGerneralAlarm)
{
    if(iGerneralAlarm != m_iGeneralAlarm)
    {
        m_iGeneralAlarm = iGerneralAlarm;
        emit signalGeneralAlarmChanged();
    }
}

/**************************************************************************//**
*
* \brief To get the UI controller version.
*
* \param None.
*
* \return the version of UI controller.
*
******************************************************************************/
QString SystemInformationInterface::getUIController() const
{
    return m_strUIController;
}

/**************************************************************************//**
*
* \brief To set the UI Controller version.
*
* \param inUIController is used to assign value to UI Controller.
*
* \return None.
*
******************************************************************************/
void SystemInformationInterface::updateUIController(const QString& strUIController)
{
    if(strUIController != m_strUIController)
    {
        m_strUIController = strUIController;
        emit signalUIControllerChanged();
    }
}

/**************************************************************************//**
*
* \brief To get the Supervisory controller version.
*
* \param None.
*
* \return the version of Supervisory controller.
*
******************************************************************************/
QString SystemInformationInterface::getSupervisoryController() const
{
    return m_strSupervisory;
}

/**************************************************************************//**
*
* \brief To set the Supervisory Controller version.
*
* \param inSupervisoryController is used to assign value to Supervisory Controller.
*
* \return None.
*
******************************************************************************/
void SystemInformationInterface::updateSupervisoryController(const QString& strSupervisoryController)
{
    if(strSupervisoryController != m_strSupervisory)
    {
        m_strSupervisory = strSupervisoryController;
        emit signalSupervisoryControllerChanged();
    }
}

/**************************************************************************//**
*
* \brief To get the Actuator controller version.
*
* \param None.
*
* \return the version of Actuator controller.
*
******************************************************************************/
QString SystemInformationInterface::getActuatorController() const
{
    return m_strActuatorController;
}

/**************************************************************************//**
*
* \brief To set the Actuator Controller version.
*
* \param inActuatorController is used to assign value to Actuator Controller.
*
* \return None.
*
******************************************************************************/
void SystemInformationInterface::updateActuatorController(const QString& strActuatorController)
{
    if(strActuatorController != m_strActuatorController)
    {
        m_strActuatorController = strActuatorController;
        emit signalActuatorControllerChanged();
    }
}

/**************************************************************************//**
*
* \brief To get the Power controller version.
*
* \param None.
*
* \return the version of Power controller.
*
******************************************************************************/
QString SystemInformationInterface::getPowerController() const
{
    return m_strPowerController;
}

/**************************************************************************//**
*
* \brief To set the Power Controller version.
*
* \param inPowerController is used to assign value to Power Controller.
*
* \return None.
*
******************************************************************************/
void SystemInformationInterface::updatePowerController(const QString& strPowerController)
{
    if(strPowerController != m_strPowerController)
    {
        m_strPowerController = strPowerController;
        emit signalPowerControllerChanged();
    }
}

/**************************************************************************//**
*
* \brief To get the power supply life time welds.
*
* \param None.
*
* \return the value of PS life time welds.
*
******************************************************************************/
int SystemInformationInterface::getPSLifeWelds() const
{
    return m_iPSLifeWelds;
}

/**************************************************************************//**
*
* \brief To set the power supply life time welds.
*
* \param inPSLifeWelds is used to assign value to power supply life time welds.
*
* \return None.
*
******************************************************************************/
void SystemInformationInterface::updatePSLifeWelds(const int& iPSLifeWelds)
{
    if(iPSLifeWelds != m_iPSLifeWelds)
    {
        m_iPSLifeWelds = iPSLifeWelds;
        emit signalPSLifeWeldsChanged();
    }
}

/**************************************************************************//**
*
* \brief To get the PS overloads.
*
* \param None.
*
* \return the value of PS overloads.
*
******************************************************************************/
int SystemInformationInterface::getPSOverloads() const
{
    return m_iPSOverloads;
}

/**************************************************************************//**
*
* \brief To set the  PS overloads.
*
* \param inOverloads is used to assign value to  PS overloads.
*
* \return None.
*
******************************************************************************/
void SystemInformationInterface::updatePSOverloads(const int& iOverloads)
{
    if(iOverloads != m_iPSOverloads)
    {
        m_iPSOverloads = iOverloads;
        emit signalPSOverloadsChanged();
    }
}

/**************************************************************************//**
*
* \brief To get the PS type.
*
* \param None.
*
* \return PS type value.
*
******************************************************************************/
int SystemInformationInterface::getPSType() const
{
    return m_iPSType;
}

/**************************************************************************//**
*
* \brief To set the  PS type.
*
* \param inPSType is used to assign value to  PS type.
*
* \return None.
*
******************************************************************************/
void SystemInformationInterface::updatePSType(const int& iPSType)
{
    if(iPSType != m_iPSType)
    {
        m_iPSType = iPSType;
        emit signalPSTypeChanged();
    }
}

/**************************************************************************//**
*
* \brief To get the PS frequency.
*
* \param None.
*
* \return the PS frequency.
*
******************************************************************************/
int SystemInformationInterface::getPSFrequency() const
{
    return m_iPSFrequency;
}

/**************************************************************************//**
*
* \brief To set the  PS frequency.
*
* \param inPSFrequency is used to assign value to  PS frequency.
*
* \return None.
*
******************************************************************************/
void SystemInformationInterface::updatePSFrequency(const int& iPSFrequency)
{
    if(iPSFrequency != m_iPSFrequency)
    {
        m_iPSFrequency = iPSFrequency;
        emit signalPSFrequencyChanged();
    }
}

/**************************************************************************//**
*
* \brief To get the PS wattage.
*
* \param None.
*
* \return the value of PS wattage.
*
******************************************************************************/
int SystemInformationInterface::getPSWattage() const
{
    return m_iPSWattage;
}

/**************************************************************************//**
*
* \brief To set the  PS wattage.
*
* \param psWattage is used to assign value to  PS wattage.
*
* \return None.
*
******************************************************************************/
void SystemInformationInterface::updatePSWattage(const int& iPSWattage)
{
    if(iPSWattage != m_iPSWattage)
    {
        m_iPSWattage = iPSWattage;
        emit signalPSWattageChanged();
    }
}

/**************************************************************************//**
*
* \brief To get the actuator life time cycle.
*
* \param None.
*
* \return the value of actuator life time cycle.
*
******************************************************************************/
int SystemInformationInterface::getActuatorLifeCycle() const
{
    return m_iActuatorLifeCycle;
}

/**************************************************************************//**
*
* \brief To set the actuator life time cycle.
*
* \param inLifeCycle is used to assign value to actuator life time cycle.
*
* \return None.
*
******************************************************************************/
void SystemInformationInterface::updateActuatorLifeCycle(const int& iLifeCycle)
{
    if(iLifeCycle != m_iActuatorLifeCycle)
    {
        m_iActuatorLifeCycle = iLifeCycle;
        emit signalActuatorLifeCycleChanged();
    }
}

/**************************************************************************//**
*
* \brief To get the actuator type.
*
* \param None.
*
* \return the actuator type.
*
******************************************************************************/
int SystemInformationInterface::getActuatorType() const
{
    return m_iActuatorType;
}

/**************************************************************************//**
*
* \brief To set the actuator type.
*
* \param actuatorType is used to assign value to actuator type.
*
* \return None.
*
******************************************************************************/
void SystemInformationInterface::updateActuatorType(const int& iActuatorType)
{
    if(iActuatorType != m_iActuatorType)
    {
        m_iActuatorType = iActuatorType;
        emit signalActuatorTypeChanged();
    }
}

/**************************************************************************//**
*
* \brief To get the actuator calibration date.
*
* \param None.
*
* \return the actuator calibration date.
*
******************************************************************************/
QString SystemInformationInterface::getActuatorCaliDate() const
{
    return m_strCalibrationDate;
}

/**************************************************************************//**
*
* \brief To set the actuator calibration date.
*
* \param actuatorType is used to assign value to actuator calibration date..
*
* \return None.
*
******************************************************************************/
void SystemInformationInterface::updateActuatorCaliDate(const QString& strCalirationDate)
{
    if(m_strCalibrationDate != strCalirationDate)
    {
        m_strCalibrationDate = strCalirationDate;
        emit signalActuatorCaliDateChanged();
    }
}

/**************************************************************************//**
*
* \brief To get the actuator overloads.
*
* \param None.
*
* \return the actuator overloads.
*
******************************************************************************/
int SystemInformationInterface::getActuatorOverloads() const
{
    return m_iActuatorOverloads;
}

/**************************************************************************//**
*
* \brief To set the actuator overloads.
*
* \param iActuatorOverloads is used to assign value to actuator overloads.
*
* \return None.
*
******************************************************************************/
void SystemInformationInterface::updateActuatorOverloads(const int &iActuatorOverloads)
{
    if(m_iActuatorOverloads != iActuatorOverloads)
    {
        m_iActuatorOverloads = iActuatorOverloads;
        emit signalActuatorOverloadsChanged();
    }
}

/**************************************************************************//**
*
* \brief To get the actuator NIST calibartion date.
*
* \param None.
*
* \return the actuator NIST calibartion date.
*
******************************************************************************/
QString SystemInformationInterface::getNISTCalibrationDate() const
{
    return m_strNISTCalibrationDate;
}

/**************************************************************************//**
*
* \brief To set the actuator NIST calibartion date.
*
* \param nistCalibrationDate is used to assign value to NIST calibartion date.
*
* \return None.
*
******************************************************************************/
void SystemInformationInterface::updateNISTCalibrationDate(const QString& strNISTCalibrationDate)
{
    if(strNISTCalibrationDate != m_strNISTCalibrationDate)
    {
        m_strNISTCalibrationDate = strNISTCalibrationDate;
        emit signalNISTCalibrationDateChanged();
    }
}

/**************************************************************************//**
*
* \brief To get the stroken length.
*
* \param None.
*
* \return the stroken length value.
*
******************************************************************************/
int SystemInformationInterface::getStrokeLength() const
{
    return m_iStrokeLength;
}

/**************************************************************************//**
*
* \brief To set the stroken length.
*
* \param strkenLenth is used to assign value to stroken length.
*
* \return None.
*
******************************************************************************/
void SystemInformationInterface::updateStrokeLength(const int& iStrkenLenth)
{
    if(iStrkenLenth != m_iStrokeLength)
    {
        m_iStrokeLength = iStrkenLenth;
        emit signalStrokeLengthChanged();
    }
}

/**************************************************************************//**
*
* \brief To get the MAC ID.
*
* \param None.
*
* \return the MAC ID.
*
******************************************************************************/
QString SystemInformationInterface::getMACAddress() const
{
    return m_strMacAddress;
}

/**************************************************************************//**
*
* \brief To set the MAC ID.
*
* \param macID is used to assign value to MAC ID.
*
* \return None.
*
******************************************************************************/
void SystemInformationInterface::updateMACAddress(const QString& strMacAddress)
{
    if(strMacAddress != m_strMacAddress)
    {
        m_strMacAddress = strMacAddress;
        emit signalMACAddressChanged();
    }
}
