/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#include <QApplication>
#include "upgradesoftware.h"
#include "definition.h"
#include "upgradesoftwaredef.h"
#include "communicationinterface.h"
SoftwareUpgrading* SoftwareUpgrading::m_ptrInstance = nullptr;
/**************************************************************************//**
*
* \brief  Constructor and initialize m_strTargetFilePath, m_realProgressValue and progress bar showing in qml.
*
*
* \param  parent : QObject*, because the SoftwareUpgrading class is inherited from QObject.
*
* \return none
*
******************************************************************************/
SoftwareUpgrading::SoftwareUpgrading(QObject *parent) : QObject(parent)
{
    m_strTargetFilePath.clear();
    m_realProgressValue = 1.0;
    setCurrentProgressValue(0.0);
}

/**************************************************************************//**
*
* \brief  To get SoftwareUpgrading singleton object.
*         The class is designed to the singleton class so the SoftwareUpgrading object can used in the everywhere
*         without any new instantiation.
*         And the SoftwareUpgrading object can be get easily using the this function
*         without any external declaration before using.
*
*
* \param  none
*
* \return Existing SoftwareUpgrading object
*
******************************************************************************/
SoftwareUpgrading *SoftwareUpgrading::getInstance()
{
    if(m_ptrInstance == nullptr)
    {
        m_ptrInstance = new SoftwareUpgrading(nullptr);
    }
    return m_ptrInstance;
}

/**************************************************************************//**
*
* \brief It is the interface for the external qml recall and is avaliable for the Raspberry Pi only.
*        the existing shell file has been saved as the resource file that means the shell file can be compiled into the execuatable file.
*        The shell file can be read to the memory and run with another independence process. With the shell file running, the software can
*        understand if the new version software is ready in the plugin USB stick.
* \param currentIndex is tab index to indicate the current software upgrading is for the firmware or UI。
*
* \return if there is any issue during the software executable file looking for, it will return false.
*
******************************************************************************/
bool SoftwareUpgrading::retrieveTargetSoftware(int currentIndex, QStringList strFileName)
{
    QStringList scriptCommand;
    QProcess pro;
    scriptCommand.clear();
    bool bResult = false;
#ifdef WIN32
    Q_UNUSED(currentIndex);
    Q_UNUSED(strFileName);
#elif linux
    switch (currentIndex)
    {
    case UpgradeSoftwareEnum::WELDER_SOFTWARE_IDX:
        break;
    case UpgradeSoftwareEnum::UICONTROLLER_SOFTWARE_IDX:
    #ifdef RASPBERRY
        QFile file(applicationFilterUrl);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;
        scriptCommand<<"-c"<<file.readAll();
    #else

    #endif
        if(scriptCommand.isEmpty() == true)
            return bResult;
        pro.start("/bin/sh", scriptCommand);
        pro.waitForFinished();
        QString str = pro.readAllStandardOutput();
        if(str.isEmpty() != true)
        {
            m_strTargetFilePath = str;

            QFileInfo fileInfo(str);
            strFileName.clear();
            strFileName.append(fileInfo.fileName());
            bResult = true;
        }
        else
            bResult = false;

        break;
    }
#endif
    return bResult;
}

/**************************************************************************//**
*
* \brief It is the interface for the external qml recall and is avaliable for the Raspberry Pi only.
*        the existing shell file has been saved as the resource file that means the shell file can be compiled into the execuatable file.
*        The shell file can be read to the memory and run with another independence process. The independence process can be started it with startDetached function
*        so it can completely run by itself regradless of the current process is close.
* \param currentIndex is tab index to indicate the current software upgrading is for the firmware or UI。
*
* \return if there is any issue during the software upgrading, it will return false.
*
******************************************************************************/
bool SoftwareUpgrading::runUpgradeProcess(int currentIndex)
{
    QStringList scriptCommand;
    QProcess pro;
    scriptCommand.clear();
    bool bResult = false;
#ifdef WIN32
    Q_UNUSED(currentIndex);
#elif linux
    switch (currentIndex)
    {
    case UpgradeSoftwareEnum::WELDER_SOFTWARE_IDX:
        break;
    case UpgradeSoftwareEnum::UICONTROLLER_SOFTWARE_IDX:
#ifdef RASPBERRY
        QFile file(applicationUpgradeUrl);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return bResult;
        scriptCommand<<"-c"<<file.readAll();
#else

#endif
        if(scriptCommand.isEmpty() == true)
            return bResult;
        pro.startDetached("/bin/sh", scriptCommand);
        pro.waitForFinished();
        setCurrentProgressValue(1.0);
        bResult = true;
        CommunicationInterface::getInstance()->closeSocket();
        QApplication::quit();
        break;
    }
#endif
    return bResult;
}

/**************************************************************************//**
*
* \brief It is the interface for the m_realProgressValue getting that is avaliable both for c++ and qml
*
* \param none
*
* \return m_realProgressValue
*
******************************************************************************/
float SoftwareUpgrading::getCurrentProgressValue() const
{
    return m_realProgressValue;
}

/**************************************************************************//**
*
* \brief It is the interface for the m_realProgressValue setting that is available both for c++ and qml.
*
* \param realProgressValue
*
* \return none.
*
******************************************************************************/
void SoftwareUpgrading::setCurrentProgressValue(const float &realProgressValue)
{
    if(realProgressValue != m_realProgressValue)
    {
        m_realProgressValue = realProgressValue;
        emit signalCurrentProgressValueChanged();
    }
}

