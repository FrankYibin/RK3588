/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 The back-end code for the alarm notification
 
 **********************************************************************************************************/

#include "alarmnotification.h"
#include "communicationinterface.h"
#include "alarmindexdef.h"
AlarmNotification* AlarmNotification::m_pAlarmObj = nullptr;
/**************************************************************************//**
*
* \brief Constructor
*        Initialize m_AlarmIndex variable
*        Initialize the alarm notification connection between 
*        the communication interface object and alarm notification object.
*
* \param parent object
*
* \return AlarmNotification instance
*
******************************************************************************/
AlarmNotification::AlarmNotification(QObject *parent) : QObject(parent)
{
    m_AlarmIndex = 0;
    connect(CommunicationInterface::getInstance(), &CommunicationInterface::signalNotifyAlarm, this, &AlarmNotification::slotNotifyAlarm);
}

/**************************************************************************//**
*
* \brief the slot function it will be processed when the alarm is detected.
*        set m_AlarmIndex
*
* \param alarmId is brought by the signal
*
* \return none.
*
******************************************************************************/
void AlarmNotification::slotNotifyAlarm(int alarmId)
{
    setAlarmIndex(alarmId);
}

/**************************************************************************//**
*
* \brief To get AlarmNotification singleton object.
*        The class is designed to the singleton class so the AlarmNotification object can used in the everywhere
*        without any new instantiation.
*        And the AlarmNotification object can be get easily using the this function
*        without any external declaration before using.
*
* \param parent object
*
* \return AlarmNotification singleton object
*
******************************************************************************/
AlarmNotification *AlarmNotification::getInstance(QObject *parent)
{
    if(m_pAlarmObj == nullptr)
    {
        m_pAlarmObj = new AlarmNotification(parent);
    }
    return m_pAlarmObj;
}

/**************************************************************************//**
*
* \brief get the m_AlarmIndex
*
* \param none
*
* \return m_AlarmIndex
*
******************************************************************************/
int AlarmNotification::getAlarmIndex() const
{
    return m_AlarmIndex;
}

/**************************************************************************//**
*
* \brief set the m_AlarmIndex
*
* \param tmpIndex
*
* \return none
*
******************************************************************************/
void AlarmNotification::setAlarmIndex(const int tmpIndex)
{
    if(m_AlarmIndex != tmpIndex)
    {
        m_AlarmIndex = tmpIndex;
        emit signalAlarmIndexChanged();
    }
}

/**************************************************************************//**
*
* \brief It is the interface function can be used both for QML and c++ to reset the any alarm.
*
* \param the specific alarm index
*
* \return if the alarm is reset successfully, it will return true.
*
******************************************************************************/
bool AlarmNotification::resetSpecificAlarm(const int tmpIndex)
{
    bool bResult = false;
    setAlarmIndex(0);
    switch (tmpIndex)
    {
    case AlarmIndexEnum::ALARM_INTERNAL_COMM_ENET:
    case AlarmIndexEnum::ALARM_HW_PROFINET_OR_IP_NOT_ID:
        bResult = CommunicationInterface::getInstance()->resetSocketAlarm();
        break;
    }
    return bResult;
}
